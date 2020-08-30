#ifndef ___INCGUARD_PKHANDYCAFE_
#define ___INCGUARD_PKHANDYCAFE_

// TODO: prevent hc from hiding other windows

#pragma comment(lib, "Version.lib")

//#define PKHC_DISABLE_SUPPORT_NEW // Define flag for disabling features related to the widely used new version of HandyCafe (v4.1.16)
#define PKHC_DISABLE_SPOOF // Disables the spoof lockscreen feature because it doesn't work (I lost the patchtable and the feature isn't really that useful)

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <stdio.h>

#ifndef PKHC_DISABLE_SPOOF
#include <thread>
#endif
#include "hash.h"

#include "patchtable_3321.h"

#ifndef PKHC_DISABLE_SUPPORT_NEW
#include "patchtable_4116.h"
#else
#include "patchtable_4116_dummy.h"
#endif

#define _PKHC_OPCODE_NOP 0x90 // Opcode for the NOP instruction
#define _PKHC_SL_VK_PATCH VK_INSERT // Key to listen for executing the spoof lockscreen event

enum class FeatureMethod : bool
{
    DISABLE = false,
    ENABLE  = true
};

enum class HandyCafeVersion : unsigned char
{
    NONE,
    UNSUPPORTED,
    DISABLED,
    V3_3_21,
    V4_1_16
};

typedef unsigned char* ptr_t;            // Pointer type
typedef void(*FeatureFn)(FeatureMethod); // Feature method function pointer

#define WND_CLASSNAME "handycafee"
#define WND_TITLE "HandyCafe Client"
#define WND_WIDTH 366
#define WND_HEIGHT 344

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
        HWND frm_Main = nullptr;

        HWND btn_Attach = nullptr;
        HWND btn_Check = nullptr;
        HWND btn_About = nullptr;

        HWND btn_Feature_NoLockscreen_Enable = nullptr;
        HWND btn_Feature_NoLockscreen_Disable = nullptr;

        HWND btn_Feature_NoProcClear_Enable = nullptr;
        HWND btn_Feature_NoProcClear_Disable = nullptr;

        HWND btn_Feature_NoBrowserLogin_Enable = nullptr;
        HWND btn_Feature_NoBrowserLogin_Disable = nullptr;

        HWND btn_Feature_NoRemoteShutdown_Enable = nullptr;
        HWND btn_Feature_NoRemoteShutdown_Disable = nullptr;

        HWND btn_Feature_ExitHC = nullptr;

        HWND btn_Feature_NoForegroundQuery_Enable = nullptr;
        HWND btn_Feature_NoForegroundQuery_Disable = nullptr;

        HWND btn_Feature_SpoofLockscreen_Enable = nullptr;
        HWND btn_Feature_SpoofLockscreen_Disable = nullptr;

        HWND btn_Feature_NoAuthentication_Enable = nullptr;
        HWND btn_Feature_NoAuthentication_Disable = nullptr;
    }

    #define PK_CTRL_ID(name, value) constexpr WORD name = value
    namespace id
    {
        PK_CTRL_ID(btn_Attach, 1);
        PK_CTRL_ID(btn_Check, 2);

        PK_CTRL_ID(btn_Feature_NoLockscreen_Enable, 3);
        PK_CTRL_ID(btn_Feature_NoLockscreen_Disable, 4);

        PK_CTRL_ID(btn_Feature_NoProcClear_Enable, 5);
        PK_CTRL_ID(btn_Feature_NoProcClear_Disable, 6);

        PK_CTRL_ID(btn_Feature_NoBrowserLogin_Enable, 7);
        PK_CTRL_ID(btn_Feature_NoBrowserLogin_Disable, 8);

        PK_CTRL_ID(btn_Feature_NoRemoteShutdown_Enable, 9);
        PK_CTRL_ID(btn_Feature_NoRemoteShutdown_Disable, 10);

        PK_CTRL_ID(btn_Feature_ExitHC, 11);

        PK_CTRL_ID(btn_About, 12);

        PK_CTRL_ID(btn_Feature_NoForegroundQuery_Enable, 13);
        PK_CTRL_ID(btn_Feature_NoForegroundQuery_Disable, 14);

        PK_CTRL_ID(btn_Feature_SpoofLockscreen_Enable, 15);
        PK_CTRL_ID(btn_Feature_SpoofLockscreen_Disable, 16);

        PK_CTRL_ID(btn_Feature_NoAuthentication_Enable, 17);
        PK_CTRL_ID(btn_Feature_NoAuthentication_Disable, 18);
    }
#undef PK_CTRL_ID

    namespace status
    {
        char str[51] = "Ready...";
        int  len     = sizeof("Ready...");

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
    constexpr FNV64  name    = utils::hashfnv("hndclient.exe");
    constexpr size_t namelen = 14;

    DWORD            pid     = 0;                      // Proccess ID
    HANDLE           handle  = nullptr;                // Handle to the handy cafe process
    ptr_t            base    = nullptr;                // Base address of the process main module
    HandyCafeVersion ver     = HandyCafeVersion::NONE; // Handy cafe version

    // Handy cafe version
    unsigned int ver_a = 0,
                 ver_b = 0,
                 ver_c = 0;

    // For UI text
    namespace infostr
    {
        char procid[] = "ID: 0000000000";
        char handle[] = "HANDLE: 0x00000000";
        char base[]   = "BASE: 0x00000000";
        char ver[32]  = "VERSION: 00.00.00";

        size_t ver_len = sizeof(ver);
    }

    void ReDrawText()
    {
        _snprintf_s(handycafe::infostr::procid , sizeof(infostr::procid) - 1, "ID: %0*d", 10, pid);
        _snprintf_s(handycafe::infostr::handle, sizeof(infostr::handle) - 1, "HANDLE: 0x%08p", handle);
        _snprintf_s(handycafe::infostr::base, sizeof(infostr::base) - 1, "BASE: 0x%08p", base);

        // Set flag for version
        bool isNewerVer = false;
        const char* ver_flag = nullptr;

        switch (handycafe::ver)
        {
            case HandyCafeVersion::NONE:
                ver_flag = "";
                break;
            case HandyCafeVersion::DISABLED:
                ver_flag = "(Disabled)";
                break;
            case HandyCafeVersion::UNSUPPORTED:
                ver_flag = "(Unsupported)";
                break;
            default:
                ver_flag = "(Supported)";
                break;
        }

        handycafe::infostr::ver_len = _snprintf_s(handycafe::infostr::ver, sizeof(infostr::ver) - 1, "VERSION: %02u.%02u.%02u %s", ver_a, ver_b, ver_c, ver_flag);

        InvalidateRect(ui::handle::frm_Main, NULL, true);
    }

    namespace lockscreen
    {
        constexpr FNV64  wndTitle    = utils::hashfnv("HandyCafe Client");
        constexpr size_t wndTitleLen = 16;

        constexpr FNV64  wndClass    = utils::hashfnv("TfrmWait");
        constexpr size_t wndClassLen = 8;
    }

}

// Namespace for pkhc
namespace pkhc
{
#ifndef PKHC_DISABLE_SPOOF
    bool bSpoofLockscreenThreadKeep = true;
    bool bSpoofLockscreenPatched = false; // Boolean to track if spoof lockscreen is active
#endif

    // Function prototypes for the main definitions of pkhc related features
    void Initialize();
    void CheckAssembly();

    // Uncategorized Feature functions
    void FeatureFn_Default(FeatureMethod fm)
    {
        ui::status::set("Initialization required");
    }

    void FeatureFn_NotSupported(FeatureMethod fm)
    {
        ui::status::set("Feature not supported");
    }

    // Function pointer to proper feature function
    FeatureFn FeatureFn_NoLockscreen      = FeatureFn_Default;
    FeatureFn FeatureFn_NoProcClear       = FeatureFn_Default;
    FeatureFn FeatureFn_NoBrowserLogin    = FeatureFn_Default;
    FeatureFn FeatureFn_NoRemoteShutdown  = FeatureFn_Default;
    FeatureFn FeatureFn_ExitHC            = FeatureFn_Default;
    FeatureFn FeatureFn_NoForegroundQuery = FeatureFn_Default;
    FeatureFn FeatureFn_SpoofLockscreen   = FeatureFn_Default;
    FeatureFn FeatureFn_NoAuthentication  = FeatureFn_Default;
}

// Namespace for pkhc's features
namespace features
{
    void NoLockscreen(FeatureMethod fm);
    void NoProcClear(FeatureMethod fm);
    void NoBrowserOnLogin(FeatureMethod fm);
    void NoRemoteShutdown(FeatureMethod fm);
    void ExitHC(FeatureMethod fm);
    void NoForegroundQuery(FeatureMethod fm);
    #ifndef PKHC_DISABLE_SPOOF
    void SpoofLockscreen(FeatureMethod fm);
    #endif
    void NoAuthentication(FeatureMethod fm);

    // Namespace for v3.3.21 specific functions
    namespace v3321
    {
    }

    // Namespace for v4.1.16 specific functions
    namespace v4116
    {
    }

}

namespace utils
{
    bool Patch(patchtable_t* pt);
    bool Restore(patchtable_t* pt);
    const char* GetASMStatus(patchtable_t* pt, HCASMSTATUS* out_status);
}

#endif//___INCGUARD_PKHANDYCAFE_