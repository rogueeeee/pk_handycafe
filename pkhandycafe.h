#ifndef ___INCGUARD_PKHANDYCAFE_
#define ___INCGUARD_PKHANDYCAFE_

//#define PKHC_DISABLE_SUPPORT_NEW // Define flag for disabling features related to the widely used new version of HandyCafe (v4.1.16)
#undef UNICODE // band aid fix for mingw issues

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <stdio.h>
#include "hash.h"

#include "patchtable_3321.h"

#ifndef PKHC_DISABLE_SUPPORT_NEW
#include "patchtable_4116.h"
#else
#include "patchtable_4116_dummy.h"
#endif

#define _PKHC_OPCODE_NOP 0x90 // Opcode for the NOP instruction
typedef unsigned char* ptr_t;     // Pointer type

enum FeatureMethod : bool
{
    PKHC_DISABLE = false,
    PKHC_ENABLE  = true
};

enum HandyCafeVersion : unsigned char
{
    HC_VER_NONE,
    HC_VER_UNSUPPORTED,
    HC_VER_3_3_21,
    HC_VER_4_1_16
};

const char* hcasm_to_text[] =
{
    "Invalid",
    "Disabled",
    "Enabled"
};

typedef void(*FeatureFn)(FeatureMethod);

#define WND_CLASSNAME "handycafee"
#define WND_TITLE "HandyCafe Client"
#define WND_WIDTH 360
#define WND_HEIGHT 326

#ifndef PKHC_DISABLE_SUPPORT_NEW
    #define PKHC_ISNEW_SUPPORTED "Yes"
#else
    #define PKHC_ISNEW_SUPPORTED "No"
#endif

#define PKHC_BUILD_TXT "pkhc // " __DATE__ " " __TIME__ " | PT 4.1.16 Support: " PKHC_ISNEW_SUPPORTED

// Prototypes
LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Namespace of UI
namespace ui
{
    namespace handle
    {
        HWND frm_Main   = nullptr;

        HWND btn_Attach = nullptr;
        HWND btn_Check  = nullptr;
        HWND btn_About  = nullptr;

        HWND btn_Feature_NoLockscreen_Enable       = nullptr;
        HWND btn_Feature_NoLockscreen_Disable      = nullptr;

        HWND btn_Feature_NoProcClear_Enable        = nullptr;
        HWND btn_Feature_NoProcClear_Disable       = nullptr;

        HWND btn_Feature_NoBrowserLogin_Enable     = nullptr;
        HWND btn_Feature_NoBrowserLogin_Disable    = nullptr;

        HWND btn_Feature_NoRemoteShutdown_Enable   = nullptr;
        HWND btn_Feature_NoRemoteShutdown_Disable  = nullptr;

        HWND btn_Feature_ExitHC                    = nullptr;

        HWND btn_Feature_NoForegroundQuery_Enable  = nullptr;
        HWND btn_Feature_NoForegroundQuery_Disable = nullptr;

        HWND btn_Feature_SpoofLockscreen_Enable    = nullptr;
        HWND btn_Feature_SpoofLockscreen_Disable   = nullptr;
    }

    #define PK_CTRL_ID(name, value) const HMENU name = reinterpret_cast<HMENU>(value)
    namespace id
    {
        PK_CTRL_ID(btn_Attach, 1);
        PK_CTRL_ID(btn_Check,  2);

        PK_CTRL_ID(btn_Feature_NoLockscreen_Enable,  3);
        PK_CTRL_ID(btn_Feature_NoLockscreen_Disable, 4);

        PK_CTRL_ID(btn_Feature_NoProcClear_Enable,  5);
        PK_CTRL_ID(btn_Feature_NoProcClear_Disable, 6);

        PK_CTRL_ID(btn_Feature_NoBrowserLogin_Enable,  7);
        PK_CTRL_ID(btn_Feature_NoBrowserLogin_Disable, 8);

        PK_CTRL_ID(btn_Feature_NoRemoteShutdown_Enable,   9);
        PK_CTRL_ID(btn_Feature_NoRemoteShutdown_Disable, 10);

        PK_CTRL_ID(btn_Feature_ExitHC, 11);

        PK_CTRL_ID(btn_About, 12);

        PK_CTRL_ID(btn_Feature_NoForegroundQuery_Enable,  13);
        PK_CTRL_ID(btn_Feature_NoForegroundQuery_Disable, 14);

        PK_CTRL_ID(btn_Feature_SpoofLockscreen_Enable,  15);
        PK_CTRL_ID(btn_Feature_SpoofLockscreen_Disable, 16);
    }
    #undef PK_CTRL_ID

    namespace status
    {
        char str[51] = "Ready...";
        unsigned long long len = sizeof("Ready...");

        void set(const char* text)
        {
            len = 0;
            do
            {
                str[len++] = *text;
            } while (*text++);

            InvalidateRect(ui::handle::frm_Main, NULL, true);
        }
    }
}

// Namespace for values related to handycafe
namespace handycafe
{
    constexpr FNV64  name      = utils::hashfnv("hndclient.exe");
    constexpr size_t namelen   = sizeof("hndclient.exe") - 1;
    DWORD            pid       = 0;           // Proccess ID
    HANDLE           handle    = nullptr;     // Handle to the handy cafe process
    ptr_t            base      = nullptr;     // Base address of the process main module
    HandyCafeVersion ver       = HC_VER_NONE; // Handy cafe version

    // Handy cafe version
    unsigned char ver_a  = 0,
                  ver_b  = 0,
                  ver_c  = 0;

    // For UI text
    namespace infostr
    {
        char procid[] = "ID: 0000000000";
        char handle[] = "HANDLE: 0x00000000";
        char base[]   = "BASE: 0x00000000";
        char ver[32]  = "VERSION: 00.00.00 (Unsupported)";

        size_t ver_len = sizeof(ver);
    }

    void ReDrawText()
    {
        sprintf(handycafe::infostr::procid, "ID: %0*d", 10, pid);
        sprintf(handycafe::infostr::handle, "HANDLE: 0x%08x", handle);
        sprintf(handycafe::infostr::base,   "BASE: 0x%08x", base);

        // Set flag for version
        bool isNewerVer = false;
        const char* ver_flag = nullptr;
        if (             (ver_a == 3 && ver_b == 3 && ver_c == 21)   // 3.3.21
        || (isNewerVer = (ver_a == 4 && ver_b == 1 && ver_c == 16) ) // 4.1.16
        ) {
            #ifndef PKHC_DISABLE_SUPPORT_NEW
            ver_flag = "(Supported)";
            #else
            ver_flag = isNewerVer ? "(Disabled)" : "(Supported)";
            #endif
        }
        else
        {
            ver_flag = "(Unsupported)";
        }

        sprintf(handycafe::infostr::ver, "VERSION: %02u.%02u.%02u %s", ver_a, ver_b, ver_c, ver_flag);
        handycafe::infostr::ver_len = strlen(handycafe::infostr::ver);

        InvalidateRect(ui::handle::frm_Main, NULL, true);
    }
}

// Namespace for pkhc's features
namespace features
{
    namespace v3321
    {
        void NoLockscreen(FeatureMethod fm);
        void NoProcClear(FeatureMethod fm);
        void NoBrowserOnLogin(FeatureMethod fm);
        void NoRemoteShutdown(FeatureMethod fm);
        void ExitHC(FeatureMethod fm);
        void NoForegroundQuery(FeatureMethod fm);
        void SpoofLockscreen(FeatureMethod fm);
    }
}

// Namespace for pkhc
namespace pkhc
{
    // Function prototypes for the main definitions of pkhc related features
    void Initialize();
    void CheckAssembly();

    // Uncategorized Feature functions
    void FeatureFn_default(FeatureMethod fm)
    {
        ui::status::set("Initialization required");
    }

    void FeatureFn_notsupported(FeatureMethod fm)
    {
        ui::status::set("Feature not supported");
    }

    // Function pointer to proper feature function
    FeatureFn FeatureFn_nolockscreen      = FeatureFn_default;
    FeatureFn FeatureFn_noprocclear       = FeatureFn_default;
    FeatureFn FeatureFn_nobrowseronlogin  = FeatureFn_default;
    FeatureFn FeatureFn_noremoteshutdown  = FeatureFn_default;
    FeatureFn FeatureFn_exithc            = FeatureFn_default;
    FeatureFn FeatureFn_noforegroundquery = FeatureFn_default;
    FeatureFn FeatureFn_spooflockscreen   = FeatureFn_default;
}

namespace utils
{
    // Patches a section of memory
    bool patch(patchtable_t* pt)
    {
        if (!pt)
            return false;

        do
        {
            DWORD oldProtect = 0; // Stores the old protection flag of the memory section
            unsigned char  singlebyte = _PKHC_OPCODE_NOP; // Used if allocation for the NOP patching is unecessary
            unsigned char* bytearray  = nullptr; // Pointer to the bytearray

            // New byte array patching
            if (pt->byte_new)
            {
                bytearray = (unsigned char*)(pt->byte_new);
            }
            // NOP patching
            else
            {
                bytearray = pt->size > 1 ? new unsigned char[pt->size] : &singlebyte; // Only allocate when necessary
                memset(bytearray, _PKHC_OPCODE_NOP, pt->size); // Fill the array with the NOP instruction
            }

            // Unlock, patch, then restore the memory section
            if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
            ||  !WriteProcessMemory(handycafe::handle, handycafe::base + pt->offset, bytearray, pt->size, NULL)
            ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
            ) {
                if (!pt->byte_new)
                    delete[] bytearray;

                return false;
            }

            // Free the memory
            if (!pt->byte_new)
                delete[] bytearray;

        } while (pt = pt->next); // Load the next patch table

        return true;
    }

    bool restore(patchtable_t* pt)
    {
        if (!pt)
            return false;

        do
        {
            DWORD oldProtect = 0; // Stores the old protection flag of the memory section
    
            // Patch and restore the original bytes
            if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
            ||  !WriteProcessMemory(handycafe::handle, handycafe::base + pt->offset, pt->byte_old, pt->size, NULL)
            ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
            ) {
                return false;
            }

        } while (pt = pt->next); // Load the next patchtable

        return true;
    }

    // Compares a section of memory to the provided bytecode for difference
    const char* GetASMStatus(patchtable_t* pt, HCASMSTATUS* out_status = nullptr)
    {
        // helper function for comparing bytes
        static bool(*comparebytes)(unsigned char* a, pkhc_byte_t b, pkhc_size_t size) = [] (unsigned char* a, pkhc_byte_t b, pkhc_size_t size) -> bool
        {
            for (int idx = 0; idx < size; idx++)
            {
                if (a[idx] != (b != nullptr ? static_cast<unsigned char>(b[idx]) : _PKHC_OPCODE_NOP))
                    return false;
            }

            return true;
        };

        DWORD          oldProtect = 0; // Stores the old protection flag of the memory section
        unsigned char  singlebyte = 0x0; // Used if allocation is unecessary
        unsigned char* readbuffer = pt->size > 1 ? new unsigned char[pt->size] : &singlebyte; // Points to the byte array for comparison
        HCASMSTATUS    asmstat    = HC_ASM_INVALID; // Status of the assembly
    
        if (!readbuffer)
            return nullptr;
    
        // Unlocks the memory, reads it into a buffer, then restores its original protection flag
        if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
        ||  !ReadProcessMemory(handycafe::handle, handycafe::base + pt->offset, readbuffer, pt->size, NULL)
        ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
        ) {
            delete[] readbuffer;
            return nullptr;
        }
    
        // Check for patch bytes
        if (comparebytes(readbuffer, pt->byte_new, pt->size))
            asmstat = HC_ASM_PATCHED;
        // Check if bytes are unmodified
        else if (comparebytes(readbuffer, pt->byte_old, pt->size))
            asmstat = HC_ASM_ORIGIN;
        // If neither, by default the byte array is invalid.
    
        // Return the asm status through the out_status pointer if available
        if (out_status)
            *out_status = asmstat;

        // Delete the buffer
        delete[] readbuffer;

        // Return the status
        return hcasm_to_text[asmstat];
    }
}

#endif//___INCGUARD_PKHANDYCAFE_