#include "pkhandycafe.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Window class for the main ui
    WNDCLASSEXA wndclass =
    {
        sizeof(WNDCLASSEXA),
        (CS_HREDRAW | CS_VREDRAW),
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(nullptr, IDC_ARROW),
        reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
        NULL,
        WND_CLASSNAME,
        NULL
    };

    // Register the window class
    if (!RegisterClassExA(&wndclass))
    {
        MessageBoxA(NULL, "Failed to register class! Exiting", WND_TITLE, 0);
        return 1;
    }

    // Create the main UI
    ui::handle::frm_Main = CreateWindowExA(
        0, WND_CLASSNAME, WND_TITLE, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
        WND_WIDTH, WND_HEIGHT,
        NULL, NULL, hInstance, NULL);

    // Show and paint the window
    ShowWindow(ui::handle::frm_Main, nCmdShow);
    UpdateWindow(ui::handle::frm_Main);

    // Message handling
    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

// Window procedure callback for the main UI
LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            ui::handle::btn_Attach                            = CreateWindowExA(0, "button", "Attach",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 5,               84,  50,  20, hWnd, ui::id::btn_Attach,                            NULL, NULL);
            ui::handle::btn_Check                             = CreateWindowExA(0, "button", "Check Assembly", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 58,              84,  120, 20, hWnd, ui::id::btn_Check,                             NULL, NULL);
            ui::handle::btn_About                             = CreateWindowExA(0, "button", "?",              WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 40,  84,  20,  20, hWnd, ui::id::btn_About,                             NULL, NULL);
            
            // No lockscreen feature            
            ui::handle::btn_Feature_NoLockscreen_Enable       = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 108, 60,  20, hWnd, ui::id::btn_Feature_NoLockscreen_Enable,       NULL, NULL);
            ui::handle::btn_Feature_NoLockscreen_Disable      = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  108, 60,  20, hWnd, ui::id::btn_Feature_NoLockscreen_Disable,      NULL, NULL);
            
            // No Process clearing feature             
            ui::handle::btn_Feature_NoProcClear_Enable        = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 130, 60,  20, hWnd, ui::id::btn_Feature_NoProcClear_Enable,        NULL, NULL);
            ui::handle::btn_Feature_NoProcClear_Disable       = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  130, 60,  20, hWnd, ui::id::btn_Feature_NoProcClear_Disable,       NULL, NULL);
            
            // No browser when logging in
            ui::handle::btn_Feature_NoBrowserLogin_Enable     = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 152, 60,  20, hWnd, ui::id::btn_Feature_NoBrowserLogin_Enable,     NULL, NULL);
            ui::handle::btn_Feature_NoBrowserLogin_Disable    = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  152, 60,  20, hWnd, ui::id::btn_Feature_NoBrowserLogin_Disable,    NULL, NULL);
            
            // No remote shutdown
            ui::handle::btn_Feature_NoRemoteShutdown_Enable   = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 174, 60,  20, hWnd, ui::id::btn_Feature_NoRemoteShutdown_Enable,   NULL, NULL);
            ui::handle::btn_Feature_NoRemoteShutdown_Disable  = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  174, 60,  20, hWnd, ui::id::btn_Feature_NoRemoteShutdown_Disable,  NULL, NULL);
            
            // Exit handycafe             
            ui::handle::btn_Feature_ExitHC                    = CreateWindowExA(0, "button", "Activate",       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 196, 125, 20, hWnd, ui::id::btn_Feature_ExitHC,                    NULL, NULL);
            
            // No foreground query
            ui::handle::btn_Feature_NoForegroundQuery_Enable  = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 219, 60,  20, hWnd, ui::id::btn_Feature_NoForegroundQuery_Enable,  NULL, NULL);
            ui::handle::btn_Feature_NoForegroundQuery_Disable = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  219, 60,  20, hWnd, ui::id::btn_Feature_NoForegroundQuery_Disable, NULL, NULL);

            // Spoof lockscreen
            ui::handle::btn_Feature_SpoofLockscreen_Enable    = CreateWindowExA(0, "button", "Enable",         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 242, 60,  20, hWnd, ui::id::btn_Feature_SpoofLockscreen_Enable,  NULL, NULL);
            ui::handle::btn_Feature_SpoofLockscreen_Disable   = CreateWindowExA(0, "button", "Disable",        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80,  242, 60,  20, hWnd, ui::id::btn_Feature_SpoofLockscreen_Disable, NULL, NULL);

            break;
        }

        case WM_COMMAND:
        {
            HMENU ctrl_id = reinterpret_cast<HMENU>(LOWORD(wParam));

            FeatureMethod flag = PKHC_DISABLE;

            if (ctrl_id == ui::id::btn_Attach)
                pkhc::Initialize();
            else if (ctrl_id == ui::id::btn_Check)
                pkhc::CheckAssembly();
            else if (ctrl_id == ui::id::btn_About)
            {
                if (MessageBoxA(ui::handle::frm_Main,
                "Runtime patching and modification tool for handyCafe\r\n\r\n"
                "https://github.com/rogueeeee/pk_handycafe\r\n"
                "\r\n"
                "Would you like to open the repository link of this software?",
                "pk for HandyCafe", MB_YESNO) == IDYES)
                {
                    ShellExecuteA(NULL, "open", "https://github.com/rogueeeee/pk_handycafe", NULL, NULL, SW_SHOWNORMAL);
                }
            }
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoLockscreen_Enable) ) || ctrl_id == ui::id::btn_Feature_NoLockscreen_Disable)
                pkhc::FeatureFn_nolockscreen(flag);
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoProcClear_Enable) ) || ctrl_id == ui::id::btn_Feature_NoProcClear_Disable)
                pkhc::FeatureFn_noprocclear(flag);
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoBrowserLogin_Enable) ) || ctrl_id == ui::id::btn_Feature_NoBrowserLogin_Disable)
                pkhc::FeatureFn_nobrowseronlogin(flag);
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoRemoteShutdown_Enable) ) || ctrl_id == ui::id::btn_Feature_NoRemoteShutdown_Disable)
                pkhc::FeatureFn_noremoteshutdown(flag);
            else if (ctrl_id == ui::id::btn_Feature_ExitHC)
                pkhc::FeatureFn_exithc(PKHC_ENABLE);
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoForegroundQuery_Enable) ) || ctrl_id == ui::id::btn_Feature_NoForegroundQuery_Disable)
                pkhc::FeatureFn_noforegroundquery(flag);
            else if ( ( flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_SpoofLockscreen_Enable) ) || ctrl_id == ui::id::btn_Feature_SpoofLockscreen_Disable)
                pkhc::FeatureFn_spooflockscreen(flag);

            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            TextOutA(hdc, 2, 0, PKHC_BUILD_TXT, sizeof(PKHC_BUILD_TXT)); // Build text

            constexpr int infotxt_offset = 0;
            TextOutA(hdc, infotxt_offset + 56, 17, handycafe::infostr::procid, sizeof(handycafe::infostr::procid));
            TextOutA(hdc, infotxt_offset + 15, 32, handycafe::infostr::handle, sizeof(handycafe::infostr::handle));
            TextOutA(hdc, infotxt_offset + 34, 47, handycafe::infostr::base, sizeof(handycafe::infostr::base));
            TextOutA(hdc, infotxt_offset + 10, 62, handycafe::infostr::ver, handycafe::infostr::ver_len);
            
            TextOutA(hdc, 2, WND_HEIGHT - 50, ui::status::str, ui::status::len); // Status text

            TextOutA(hdc, 10, 110, "No logout lockscreen:", 21);
            TextOutA(hdc, 10, 132, "No Process clear:", 17);
            TextOutA(hdc, 10, 154, "No Browser on login:", 20);
            TextOutA(hdc, 10, 176, "No Remote shutdown:", 19);
            TextOutA(hdc, 10, 198, "Exit handycafe:", 15);
            TextOutA(hdc, 10, 220, "No foreground query:", 20);
            TextOutA(hdc, 10, 242, "Spoof Lockscreen:", 17);

            EndPaint(hWnd, &ps);
            break;
        }

        case WM_DESTROY:
        {
            if (handycafe::handle)
                CloseHandle(handycafe::handle);

            PostQuitMessage(0);
            break;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

namespace features
{
    namespace v3321
    {
        void NoLockscreen(FeatureMethod fm)
        {
            ui::status::set(fm ? "Patching lockscreen..." : "Restoring lockscreen...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::NoLockScreen) :
                   utils::restore(&patchtable_3321::NoLockScreen)
            )
            ) {
                ui::status::set(fm ? "Patching lockscreen failed..." : "Restoring lockscreen failed...");
                return;
            }

            ui::status::set(fm ? "No lockscreen enabled" : "No lockscreen disabled");
        }

        void NoProcClear(FeatureMethod fm)
        {
            ui::status::set(fm ? "Patching proc clear..." : "Restoring proc clear...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::NoProcClear) :
                   utils::restore(&patchtable_3321::NoProcClear)
            )
            ) {
                ui::status::set(fm ? "Patching proc clear failed..." : "Restoring proc clear failed...");
                return;
            }

            ui::status::set(fm ? "No proc clear enabled" : "No proc clear disabled");
        }

        void NoBrowserOnLogin(FeatureMethod fm)
        {
            ui::status::set(fm ? "Patching browser on login..." : "Restoring browser on login...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::NoBrowserOnLogin) :
                   utils::restore(&patchtable_3321::NoBrowserOnLogin)
            )
            ) {
                ui::status::set(fm ? "Patching proc clear failed..." : "Restoring proc clear failed...");
                return;
            }

            ui::status::set(fm ? "No browser on login enabled" : "No browser on login disabled");
        }

        void NoRemoteShutdown(FeatureMethod fm)
        {
            ui::status::set(fm ? "Patching remote shutdown..." : "Restoring remote shutdown...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::NoRemoteShutdown) :
                   utils::restore(&patchtable_3321::NoRemoteShutdown)
            )
            ) {
                ui::status::set(fm ? "Patching remote shutdown failed..." : "Restoring remote shutdown failed...");
                return;
            }

            ui::status::set(fm ? "No remote shutdown enabled" : "No remote shutdown disabled");
        }

        void ExitHC(FeatureMethod fm)
        {
            ui::status::set("Executing exit thread...");

            HANDLE hCRT = CreateRemoteThread(handycafe::handle, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(handycafe::base + patchtable_3321::ExitHC_v::offset), nullptr, NULL, nullptr);
            if (!hCRT)
            {
                ui::status::set("Failed to create exit thread");
                return;
            }

            WaitForSingleObject(hCRT, INFINITE);
            CloseHandle(hCRT);

            ui::status::set("Exit thread created!");
        }

        void NoForegroundQuery(FeatureMethod fm)
        {
            ui::status::set(fm ? "Patching foreground query..." : "Restoring foreground query...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::NoForegroundQuery) :
                   utils::restore(&patchtable_3321::NoForegroundQuery)
            )
            ) {
                ui::status::set(fm ? "Patching foreground query failed..." : "Restoring foreground query failed...");
                return;
            }

            ui::status::set(fm ? "No foreground query enabled" : "No foreground query disabled");
        }

        void SpoofLockscreen(FeatureMethod fm)
        {
            ui::status::set(fm ? "Enabling lockscreen spoof..." : "Disabling lockscreen spoof...");
            if ( !(fm ?
                   utils::patch(&patchtable_3321::SpoofLockscreen) :
                   utils::restore(&patchtable_3321::SpoofLockscreen)
            )
            ) {
                ui::status::set(fm ? "Enabling lockscreen spoof failed..." : "Disabling lockscreen spoof failed...");
                return;
            }

            ui::status::set(fm ? "Lockscreen spoof enabled" : "Lockscreen spoof disabled");
        }
    }
}

namespace pkhc
{
    // Initialize pkhc. Handles the creation of open handles, obtaining addresses, parsing version, etc...
    void Initialize()
    {
        // Reset procedure: info values
        ui::status::set("Reset...");
        handycafe::base = nullptr;
        handycafe::pid  = 0;
        handycafe::ver  = HC_VER_NONE;
        handycafe::ver_a = handycafe::ver_b = handycafe::ver_c = 0;

        // Reset procedure: features
        pkhc::FeatureFn_nolockscreen      = FeatureFn_default;
        pkhc::FeatureFn_noprocclear       = FeatureFn_default;
        pkhc::FeatureFn_nobrowseronlogin  = FeatureFn_default;
        pkhc::FeatureFn_noremoteshutdown  = FeatureFn_default;
        pkhc::FeatureFn_noforegroundquery = FeatureFn_default;
        pkhc::FeatureFn_exithc            = FeatureFn_default;
        pkhc::FeatureFn_spooflockscreen   = FeatureFn_default;

        // Reset procedure: handle
        CloseHandle(handycafe::handle);
        handycafe::handle = nullptr; 
        handycafe::ReDrawText();

        // Init
        HANDLE            hTool32   = nullptr; // Handle to cth32
        DWORD             _pid      = 0;       // Temp pid
        HANDLE            _handle   = nullptr; // temp handle pointer
        ptr_t             _base     = nullptr; // Temp base address pointer
        VS_FIXEDFILEINFO* verInfo   = nullptr; // File version info

        // Scope for process search
        {
            ui::status::set("Finding process...");

            PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
            DWORD pkPID = GetCurrentProcessId();

            if (!pkPID)
            {
                ui::status::set("Cant obtain PID of pkhc");
                return;
            }

            hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (!hTool32)
            {
                ui::status::set("Process snap failed");
                return;
            }

            while (Process32Next(hTool32, &pe32))
            {
                if (pkPID != pe32.th32ProcessID && utils::hashfnv_partial(pe32.szExeFile, handycafe::namelen) == handycafe::name)
                {
                    _pid = pe32.th32ProcessID;
                    break;
                }
            }

            CloseHandle(hTool32);
        }

        if (!_pid)
        {
            ui::status::set("Process not found");
            return;
        }

        // Scope for module search
        {
            ui::status::set("Finding module...");

            MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
            hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pid);

            if (!hTool32)
            {
                ui::status::set("Module snap failed");
                return;
            }

            while (Module32Next(hTool32, &me32))
            {
                if (utils::hashfnv_partial(me32.szModule, handycafe::namelen) == handycafe::name)
                {
                    _base = me32.modBaseAddr;
                    break;
                }
            }

            CloseHandle(hTool32);
        }

        if (!_base)
        {
            ui::status::set("Module not found");
            return;
        }

        ui::status::set("Opening process...");
        _handle = OpenProcess(PROCESS_ALL_ACCESS, false, _pid);

        if (!_handle)
        {
            ui::status::set("Open process failed");
            return;
        }

        // Scope for version parsing        
        {
            char              path[256] = { 0 };
            DWORD             hVer      = 0;
            UINT              size      = 0;
            LPBYTE            lpBuffer  = nullptr;
            DWORD             verSize   = 0;
            LPSTR             verData   = nullptr;

            ui::status::set("Obtaining path...");
            if (!GetModuleFileNameExA(_handle, nullptr, path, 256))
            {
                ui::status::set("Failed to obtain path!");
                return;
            }

            ui::status::set("Checking file version size...");
            if ((verSize = GetFileVersionInfoSizeA(path, &hVer)) == 0)
            {
                ui::status::set("File version size check failed!");
                return;
            }

            ui::status::set("Allocating for file version...");
            if ((verData = new char[verSize]) == nullptr)
            {
                ui::status::set("File version allocation failed!");
                return;
            }

            ui::status::set("Obtaining file version info...");
            if (!GetFileVersionInfoA( path, hVer, verSize, verData))
            {
                ui::status::set("Failed to obtain file version info!");
                return;
            }

            ui::status::set("Querying file version info...");
            if (!VerQueryValueA(verData,"\\",(VOID FAR* FAR*)&lpBuffer,&size))
            {
                ui::status::set("Failed to query file version info!");
                return;
            }

            if (size == 0)
            {
                ui::status::set("File version size invalid...");
                return;
            }

            verInfo = reinterpret_cast<VS_FIXEDFILEINFO*>(lpBuffer);
            if (verInfo->dwSignature != 0xfeef04bd)
            {
                ui::status::set("Invalid file version signature..");
                return;
            }
        }

        // Assign values parsed
        handycafe::ver_a  = (verInfo->dwProductVersionMS) >> 16 & 0xffff;
        handycafe::ver_b  = verInfo->dwProductVersionMS & 0xffff;
        handycafe::ver_c  = (((verInfo->dwProductVersionLS) >> 16 & 0xffff) * 10) + verInfo->dwProductVersionLS & 0xffff;
        handycafe::handle = _handle;
        handycafe::pid    = _pid;
        handycafe::base   = _base;

        ui::status::set("Deallocating file ver buffer...");
        delete[] reinterpret_cast<LPBYTE>(verInfo);

        ui::status::set("Setting up features...");

        bool isNewerVer = false;
        if (             (handycafe::ver_a == 3 && handycafe::ver_b == 3 && handycafe::ver_c == 21)   // 3.3.21
        || (isNewerVer = (handycafe::ver_a == 4 && handycafe::ver_b == 1 && handycafe::ver_c == 16) ) // 4.1.16
        ) {
            // Version is supported
            if (isNewerVer)
            {
                // Version 4.1.16
                handycafe::ver = HC_VER_4_1_16;
                
                #ifndef PKHC_DISABLE_SUPPORT_NEW
                #elif
                pkhc::FeatureFn_nolockscreen      = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_noprocclear       = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_nobrowseronlogin  = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_noremoteshutdown  = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_exithc            = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_noforegroundquery = pkhc::FeatureFn_notsupported;
                pkhc::FeatureFn_spooflockscreen   = pkhc::FeatureFn_notsupported;
                #endif
            }
            else
            {
                // Version 3.3.21
                handycafe::ver = HC_VER_3_3_21;
                pkhc::FeatureFn_nolockscreen      = features::v3321::NoLockscreen;
                pkhc::FeatureFn_noprocclear       = features::v3321::NoProcClear;
                pkhc::FeatureFn_nobrowseronlogin  = features::v3321::NoBrowserOnLogin;
                pkhc::FeatureFn_noremoteshutdown  = features::v3321::NoRemoteShutdown;
                pkhc::FeatureFn_exithc            = features::v3321::ExitHC;
                pkhc::FeatureFn_noforegroundquery = features::v3321::NoForegroundQuery;
                pkhc::FeatureFn_spooflockscreen   = features::v3321::SpoofLockscreen;
            }
        }
        else
        {
            // Version is unsupported
            handycafe::ver = HC_VER_UNSUPPORTED;
            pkhc::FeatureFn_nolockscreen      = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_noprocclear       = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_nobrowseronlogin  = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_noremoteshutdown  = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_exithc            = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_noforegroundquery = pkhc::FeatureFn_notsupported;
            pkhc::FeatureFn_spooflockscreen   = pkhc::FeatureFn_notsupported;
        }


        handycafe::ReDrawText();
        ui::status::set("Attached!");
    }

    // Checking and verifying HandyCafe's assembly
    void CheckAssembly()
    {
        if (!handycafe::handle)
        {
            ui::status::set("Initialization required");
            return;
        }

        if (handycafe::ver == HC_VER_NONE || handycafe::ver == HC_VER_UNSUPPORTED)
        {
            ui::status::set("Invalid version");
            return;
        }

        char msgbuffer[128] = { '\0' };

        sprintf(msgbuffer, 
                "No lockscreen: %s\r\n"
                "No Process clear: %s\r\n"
                "No browser on login: %s\r\n"
                "No remote shutdown: %s\r\n"
                "No foreground query:%s\r\n",
                utils::GetASMStatus(handycafe::ver == HC_VER_3_3_21 ? &patchtable_3321::NoLockScreen      : &patchtable_4116::NoLockScreen),
                utils::GetASMStatus(handycafe::ver == HC_VER_3_3_21 ? &patchtable_3321::NoProcClear       : &patchtable_4116::NoProcClear),
                utils::GetASMStatus(handycafe::ver == HC_VER_3_3_21 ? &patchtable_3321::NoBrowserOnLogin  : &patchtable_4116::NoBrowserOnLogin),
                utils::GetASMStatus(handycafe::ver == HC_VER_3_3_21 ? &patchtable_3321::NoRemoteShutdown  : &patchtable_4116::NoRemoteShutdown),
                utils::GetASMStatus(handycafe::ver == HC_VER_3_3_21 ? &patchtable_3321::NoForegroundQuery : &patchtable_4116::NoForegroundQuery)
        );

        MessageBoxA(ui::handle::frm_Main, msgbuffer, "Assembly check", 0);
    }
}