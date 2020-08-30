#include "pkhandycafe.h"

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
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

    #ifndef PKHC_DISABLE_SPOOF
    // Key listener thread for spoof lockscreen event
    std::thread SpoofLockscreenKeyListener([]() ->  void
    {
        bool wasKeyDown = false;
        HWND hwndForeground = nullptr;
        while (pkhc::bSpoofLockscreenThreadKeep)
        {
            if (!pkhc::bSpoofLockscreenPatched)
            {
                Sleep(1500);
                continue;
            }
    
            Sleep(1);
    
            bool isKeyDown = GetAsyncKeyState(_PKHC_SL_VK_PATCH) & 0x1;
    
            if (isKeyDown && !wasKeyDown)
                wasKeyDown = true;
    
            // Check if event should be triggered
            if (!isKeyDown && wasKeyDown && (hwndForeground = GetForegroundWindow()))
            {
                wasKeyDown = false; // Reset key listen
    
                char buffTitle[32] = { '\0' };
                char buffClass[32] = { '\0' };
    
                // Obtain window info
                if (!GetWindowTextA(hwndForeground, buffTitle, 32)
                ||  !GetClassNameA(hwndForeground, buffClass, 32))
                {
                    continue;
                }
    
                // Compare window info
                if (utils::hashfnv_partial(buffTitle, handycafe::lockscreen::wndTitleLen) != handycafe::lockscreen::wndTitle
                ||  utils::hashfnv_partial(buffClass, handycafe::lockscreen::wndClassLen) != handycafe::lockscreen::wndClass)
                {
                    continue;
                }
    
                // Patch Lockscreen
                utils::Patch(&patchtable_3321::SpoofLockscreen_event_getforeground);
    
                // Hide the lockscreen
                ShowWindow(hwndForeground, SW_HIDE);
            }
        }
    });
    #endif

    // Message handling
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

#ifndef PKHC_DISABLE_SPOOF
    SpoofLockscreenKeyListener.join();
#endif

    return static_cast<int>(msg.wParam);
}

// Window procedure callback for the main UI
LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            ui::handle::btn_Attach = CreateWindowExA(0, "button", "Attach", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 5, 84, 50, 20, hWnd, ui::id::btn_Attach, NULL, NULL);
            ui::handle::btn_Check = CreateWindowExA(0, "button", "Check Assembly", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 58, 84, 120, 20, hWnd, ui::id::btn_Check, NULL, NULL);
            ui::handle::btn_About = CreateWindowExA(0, "button", "?", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 40, 84, 20, 20, hWnd, ui::id::btn_About, NULL, NULL);

            // No lockscreen feature            
            ui::handle::btn_Feature_NoLockscreen_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 108, 60, 20, hWnd, ui::id::btn_Feature_NoLockscreen_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoLockscreen_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 108, 60, 20, hWnd, ui::id::btn_Feature_NoLockscreen_Disable, NULL, NULL);

            // No Process clearing feature             
            ui::handle::btn_Feature_NoProcClear_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 130, 60, 20, hWnd, ui::id::btn_Feature_NoProcClear_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoProcClear_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 130, 60, 20, hWnd, ui::id::btn_Feature_NoProcClear_Disable, NULL, NULL);

            // No browser when logging in
            ui::handle::btn_Feature_NoBrowserLogin_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 152, 60, 20, hWnd, ui::id::btn_Feature_NoBrowserLogin_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoBrowserLogin_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 152, 60, 20, hWnd, ui::id::btn_Feature_NoBrowserLogin_Disable, NULL, NULL);

            // No remote shutdown
            ui::handle::btn_Feature_NoRemoteShutdown_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 174, 60, 20, hWnd, ui::id::btn_Feature_NoRemoteShutdown_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoRemoteShutdown_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 174, 60, 20, hWnd, ui::id::btn_Feature_NoRemoteShutdown_Disable, NULL, NULL);

            // Exit handycafe             
            ui::handle::btn_Feature_ExitHC = CreateWindowExA(0, "button", "Activate", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 196, 125, 20, hWnd, ui::id::btn_Feature_ExitHC, NULL, NULL);

            // No foreground query
            ui::handle::btn_Feature_NoForegroundQuery_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 219, 60, 20, hWnd, ui::id::btn_Feature_NoForegroundQuery_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoForegroundQuery_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 219, 60, 20, hWnd, ui::id::btn_Feature_NoForegroundQuery_Disable, NULL, NULL);

            // No authentication
            ui::handle::btn_Feature_NoAuthentication_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 242, 60, 20, hWnd, ui::id::btn_Feature_NoAuthentication_Enable, NULL, NULL);
            ui::handle::btn_Feature_NoAuthentication_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 242, 60, 20, hWnd, ui::id::btn_Feature_NoAuthentication_Disable, NULL, NULL);

            // Spoof lockscreen
            ui::handle::btn_Feature_SpoofLockscreen_Enable = CreateWindowExA(0, "button", "Enable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 145, 265, 60, 20, hWnd, ui::id::btn_Feature_SpoofLockscreen_Enable, NULL, NULL);
            ui::handle::btn_Feature_SpoofLockscreen_Disable = CreateWindowExA(0, "button", "Disable", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WND_WIDTH - 80, 265, 60, 20, hWnd, ui::id::btn_Feature_SpoofLockscreen_Disable, NULL, NULL);

            break;
        }

        case WM_COMMAND:
        {
            HMENU ctrl_id = reinterpret_cast<HMENU>(LOWORD(wParam));

            FeatureMethod flag = FeatureMethod::DISABLE;

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
            else if (ctrl_id == ui::id::btn_Feature_ExitHC)
                pkhc::FeatureFn_ExitHC(FeatureMethod::ENABLE);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoLockscreen_Enable))      == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoLockscreen_Disable)
                pkhc::FeatureFn_NoLockscreen(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoProcClear_Enable))       == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoProcClear_Disable)
                pkhc::FeatureFn_NoProcClear(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoBrowserLogin_Enable))    == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoBrowserLogin_Disable)
                pkhc::FeatureFn_NoBrowserOnLogin(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoRemoteShutdown_Enable))  == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoRemoteShutdown_Disable)
                pkhc::FeatureFn_NoRemoteShutdown(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoForegroundQuery_Enable)) == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoForegroundQuery_Disable)
                pkhc::FeatureFn_NoForegroundQuery(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_SpoofLockscreen_Enable))   == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_SpoofLockscreen_Disable)
                pkhc::FeatureFn_SpoofLockscreen(flag);
            else if ((flag = static_cast<FeatureMethod>(ctrl_id == ui::id::btn_Feature_NoAuthentication_Enable))  == FeatureMethod::ENABLE || ctrl_id == ui::id::btn_Feature_NoAuthentication_Disable)
                pkhc::FeatureFn_NoAuthentication(flag);

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

            TextOutA(hdc, 2, WND_HEIGHT - 58, ui::status::str, ui::status::len); // Status text

            TextOutA(hdc, 10, 110, "No logout lockscreen:", 21);
            TextOutA(hdc, 10, 132, "No Process clear:", 17);
            TextOutA(hdc, 10, 154, "No Browser on login:", 20);
            TextOutA(hdc, 10, 176, "No Remote shutdown:", 19);
            TextOutA(hdc, 10, 198, "Exit handycafe:", 15);
            TextOutA(hdc, 10, 220, "No foreground query:", 20);
            TextOutA(hdc, 10, 242, "No authentication:", 18);
            TextOutA(hdc, 10, 264, "Spoof lockscreen:", 17);

            EndPaint(hWnd, &ps);
            break;
        }

        case WM_DESTROY:
        {
            if (handycafe::handle)
                CloseHandle(handycafe::handle);
#ifndef PKHC_DISABLE_SPOOF
            pkhc::bSpoofLockscreenThreadKeep = false;
#endif
            PostQuitMessage(0);
            break;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Function callbacks
namespace features
{
    void NoLockscreen(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching lockscreen..." : "Restoring lockscreen...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoLockScreen : &patchtable_4116::NoLockScreen) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoLockScreen : &patchtable_4116::NoLockScreen))
        ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching lockscreen failed..." : "Restoring lockscreen failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No lockscreen enabled" : "No lockscreen disabled");
    }

    void NoProcClear(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching proc clear..." : "Restoring proc clear...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoProcClear : &patchtable_4116::NoProcClear) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoProcClear : &patchtable_4116::NoProcClear)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching proc clear failed..." : "Restoring proc clear failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No proc clear enabled" : "No proc clear disabled");
    }

    void NoBrowserOnLogin(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching browser on login..." : "Restoring browser on login...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoBrowserOnLogin : &patchtable_4116::NoBrowserOnLogin) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoBrowserOnLogin : &patchtable_4116::NoBrowserOnLogin)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching proc clear failed..." : "Restoring proc clear failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No browser on login enabled" : "No browser on login disabled");
    }

    void NoRemoteShutdown(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching remote shutdown..." : "Restoring remote shutdown...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoRemoteShutdown : &patchtable_4116::NoRemoteShutdown) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoRemoteShutdown : &patchtable_4116::NoRemoteShutdown)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching remote shutdown failed..." : "Restoring remote shutdown failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No remote shutdown enabled" : "No remote shutdown disabled");
    }

    void ExitHC(FeatureMethod fm)
    {
        ui::status::set("Executing exit thread...");

        HANDLE hCRT = CreateRemoteThread(handycafe::handle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(handycafe::base + (handycafe::ver == HandyCafeVersion::V3_3_21 ? patchtable_3321::ExitHC_v::offset : patchtable_4116::ExitHC_v::offset)), nullptr, 0, nullptr);
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
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching foreground query..." : "Restoring foreground query...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoForegroundQuery : &patchtable_4116::NoForegroundQuery) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoForegroundQuery : &patchtable_4116::NoForegroundQuery)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching foreground query failed..." : "Restoring foreground query failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No foreground query enabled" : "No foreground query disabled");
    }

    #ifndef PKHC_DISABLE_SPOOF
    void SpoofLockscreen(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Enabling lockscreen spoof..." : "Disabling lockscreen spoof...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(&patchtable_3321::SpoofLockscreen) : // Only patch the desktop setup, lockscreen spoof patch is applied on event
            utils::Restore(&patchtable_3321::SpoofLockscreen) && utils::Restore(&patchtable_3321::SpoofLockscreen_event_getforeground)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Enabling lockscreen spoof failed..." : "Disabling lockscreen spoof failed...");
            return;
        }

        pkhc::bSpoofLockscreenPatched = fm == FeatureMethod::ENABLE;
        ui::status::set(fm == FeatureMethod::ENABLE ? "Lockscreen spoof enabled" : "Lockscreen spoof disabled");
    }
    #endif

    void NoAuthentication(FeatureMethod fm)
    {
        ui::status::set(fm == FeatureMethod::ENABLE ? "Patching no auth..." : "Restoring no auth...");
        if (!(fm == FeatureMethod::ENABLE ?
            utils::Patch(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoAuthentication : &patchtable_4116::NoAuthentication) :
            utils::Restore(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoAuthentication : &patchtable_4116::NoAuthentication)
            )
            ) {
            ui::status::set(fm == FeatureMethod::ENABLE ? "Patching no auth failed..." : "Restoring no auth failed...");
            return;
        }

        ui::status::set(fm == FeatureMethod::ENABLE ? "No auth enabled" : "No auth disabled");
    }

    namespace v3321
    {
    }

    namespace v4116
    {
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
        handycafe::pid = 0;
        handycafe::ver = HandyCafeVersion::NONE;
        handycafe::ver_a = handycafe::ver_b = handycafe::ver_c = 0;

        // Reset procedure: features
        pkhc::FeatureFn_NoLockscreen      = FeatureFn_Default;
        pkhc::FeatureFn_NoProcClear       = FeatureFn_Default;
        pkhc::FeatureFn_NoBrowserOnLogin  = FeatureFn_Default;
        pkhc::FeatureFn_NoRemoteShutdown  = FeatureFn_Default;
        pkhc::FeatureFn_NoForegroundQuery = FeatureFn_Default;
        pkhc::FeatureFn_ExitHC            = FeatureFn_Default;
        pkhc::FeatureFn_SpoofLockscreen   = FeatureFn_Default;
        pkhc::FeatureFn_NoAuthentication  = FeatureFn_Default;

        // Reset procedure: handle
        CloseHandle(handycafe::handle);
        handycafe::handle = nullptr;
        handycafe::ReDrawText();

        // Init
        HANDLE            hTool32 = nullptr; // Handle to cth32
        DWORD             _pid    = 0;       // Temp pid
        HANDLE            _handle = nullptr; // temp handle pointer
        ptr_t             _base   = nullptr; // Temp base address pointer
        LPSTR             verData = nullptr; // Version data
        VS_FIXEDFILEINFO* verInfo = nullptr; // File version info

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
            char   path[256] = { 0 };
            DWORD  hVer      = 0;
            UINT   size      = 0;
            LPBYTE lpBuffer  = nullptr;
            DWORD  verSize   = 0;

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
            if (!GetFileVersionInfoA(path, hVer, verSize, verData))
            {
                ui::status::set("Failed to obtain file version info!");
                return;
            }

            ui::status::set("Querying file version info...");
            if (!VerQueryValueA(verData, "\\", (VOID FAR * FAR*) &lpBuffer, &size))
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

            if (!verInfo || verInfo->dwSignature != 0xfeef04bd)
            {
                ui::status::set("Invalid file version signature..");
                return;
            }
        }

        // Assign values parsed
        handycafe::handle = _handle;
        handycafe::pid    = _pid;
        handycafe::base   = _base;
        handycafe::ver_a  = (verInfo->dwProductVersionMS) >> 16 & 0xffff;
        handycafe::ver_b  = verInfo->dwProductVersionMS & 0xffff;
        handycafe::ver_c  = (((verInfo->dwProductVersionLS) >> 16 & 0xffff));

        if (verInfo->dwProductVersionLS & 0xffff)
        {
            handycafe::ver_c *= 10;
            handycafe::ver_c += verInfo->dwProductVersionLS & 0xffff;
        }

        ui::status::set("Deallocating ver data buffer...");
        delete[] verData;
        
        ui::status::set("Setting up features...");

        // Set Version
        if (handycafe::ver_a == 3 && handycafe::ver_b == 3 && handycafe::ver_c == 21)
        {
            handycafe::ver = HandyCafeVersion::V3_3_21;
        }
        else if (handycafe::ver_a == 4 && handycafe::ver_b == 1 && handycafe::ver_c == 16)
        {
            #ifndef PKHC_DISABLE_SUPPORT_NEW
            handycafe::ver = HandyCafeVersion::V4_1_16;
            #else
            handycafe::ver = HandyCafeVersion::DISABLED;
            #endif
        }
        else
        {
            handycafe::ver = HandyCafeVersion::UNSUPPORTED;
        }

        // Setup pkhc by version
        switch (handycafe::ver)
        {
            case HandyCafeVersion::V3_3_21:
            case HandyCafeVersion::V4_1_16:
            {
                pkhc::FeatureFn_NoLockscreen      = features::NoLockscreen;
                pkhc::FeatureFn_NoProcClear       = features::NoProcClear;
                pkhc::FeatureFn_NoBrowserOnLogin  = features::NoBrowserOnLogin;
                pkhc::FeatureFn_NoRemoteShutdown  = features::NoRemoteShutdown;
                pkhc::FeatureFn_ExitHC            = features::ExitHC;
                pkhc::FeatureFn_NoForegroundQuery = features::NoForegroundQuery;
                pkhc::FeatureFn_NoAuthentication  = features::NoAuthentication;

                #ifndef PKHC_DISABLE_SPOOF
                pkhc::FeatureFn_SpoofLockscreen = features::SpoofLockscreen;
                #endif
                break;
            }

            case HandyCafeVersion::UNSUPPORTED:
            case HandyCafeVersion::DISABLED:
            default:
            {
                pkhc::FeatureFn_NoLockscreen      = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_NoProcClear       = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_NoBrowserOnLogin  = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_NoRemoteShutdown  = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_ExitHC            = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_NoForegroundQuery = pkhc::FeatureFn_NotSupported;
                pkhc::FeatureFn_NoAuthentication  = pkhc::FeatureFn_NotSupported;

                #ifndef PKHC_DISABLE_SPOOF
                pkhc::FeatureFn_SpoofLockscreen = pkhc::FeatureFn_NotSupported;
                #endif
                break;
            }
        }

        #ifdef PKHC_DISABLE_SPOOF
        pkhc::FeatureFn_SpoofLockscreen = [](FeatureMethod fm) -> void
        {
            ui::status::set("Spoof lockscreen is disabled");
        };
        #endif

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

        if (handycafe::ver == HandyCafeVersion::NONE || handycafe::ver == HandyCafeVersion::UNSUPPORTED)
        {
            ui::status::set("Invalid version");
            return;
        }

        char msgbuffer[256] = { '\0' };

        _snprintf_s(msgbuffer,
                  255,
                  "No lockscreen: %s\r\n"
                  "No Process clear: %s\r\n"
                  "No browser on login: %s\r\n"
                  "No remote shutdown: %s\r\n"
                  "No foreground query:%s\r\n"
                  #ifndef PKHC_DISABLE_SPOOF
                  "Spoof Lockscreen: %s\r\n"
                  #endif
                  "No Authentication: %s",
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoLockScreen      : &patchtable_4116::NoLockScreen, nullptr),
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoProcClear       : &patchtable_4116::NoProcClear, nullptr),
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoBrowserOnLogin  : &patchtable_4116::NoBrowserOnLogin, nullptr),
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoRemoteShutdown  : &patchtable_4116::NoRemoteShutdown, nullptr),
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoForegroundQuery : &patchtable_4116::NoForegroundQuery, nullptr),
                  #ifndef PKHC_DISABLE_SPOOF
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::SpoofLockscreen   : &patchtable_4116::SpoofLockscreen, nullptr),
                  #endif
                  utils::GetASMStatus(handycafe::ver == HandyCafeVersion::V3_3_21 ? &patchtable_3321::NoAuthentication  : &patchtable_4116::NoAuthentication, nullptr)
        );

        MessageBoxA(ui::handle::frm_Main, msgbuffer, "Assembly check", 0);
    }
}

namespace utils
{
    // Patches a section of memory
    bool Patch(patchtable_t* pt)
    {
        if (!pt)
            return false;

        do
        {

            if (!pt->byte_old || !pt->offset || !pt->size)
            {
                MessageBoxA(ui::handle::frm_Main, pt->id, "Invalid patch table", 0);
                continue;
            }

            DWORD oldProtect = 0; // Stores the old protection flag of the memory section
            unsigned char  singlebyte = _PKHC_OPCODE_NOP; // Used if allocation for the NOP patching is unecessary
            unsigned char* bytearray = nullptr; // Pointer to the bytearray

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

            // Unlock, Patch, then Restore the memory section
            if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
            ||  !WriteProcessMemory(handycafe::handle, handycafe::base + pt->offset, bytearray, pt->size, NULL)
            ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
            ) {
                if (!pt->byte_new)
                    delete[] bytearray;

                MessageBoxA(ui::handle::frm_Main, pt->id, "Patch failed on id", 0);

                return false;
            }

            // Free the memory
            if (!pt->byte_new)
                delete[] bytearray;

        } while (pt = pt->next); // Load the next Patch table

        return true;
    }

    // Restores the original bytes in a section of a patched memory
    bool Restore(patchtable_t* pt)
    {
        if (!pt)
            return false;

        do
        {

            if (!pt->byte_old || !pt->offset || !pt->size)
            {
                MessageBoxA(ui::handle::frm_Main, pt->id, "Invalid patch table", 0);
                continue;
            }

            DWORD oldProtect = 0; // Stores the old protection flag of the memory section

            // Patch and Restore the original bytes
            if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
            ||  !WriteProcessMemory(handycafe::handle, handycafe::base + pt->offset, pt->byte_old, pt->size, NULL)
            ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
            ) {
                MessageBoxA(ui::handle::frm_Main, pt->id, "Restore failed on id", 0);
                
                return false;
            }

        } while (pt = pt->next); // Load the next patchtable

        return true;
    }

    // Compares a section of memory to the provided bytecode for difference
    const char* GetASMStatus(patchtable_t* pt, HCASMSTATUS* out_status)
    {
        // helper function for comparing bytes
        static bool(*comparebytes)(unsigned char* a, pkhc_byte_t b, pkhc_size_t size) = [](unsigned char* a, pkhc_byte_t b, pkhc_size_t size) -> bool
        {
            for (int idx = 0; idx < size; idx++)
            {
                if (a[idx] != (b != nullptr ? static_cast<unsigned char>(b[idx]) : _PKHC_OPCODE_NOP))
                    return false;
            }

            return true;
        };

        static const char* hcasm_to_text[] =
        {
            "Invalid",
            "Disabled",
            "Enabled"
        };

        if (!pt || !pt->byte_old || !pt->offset || !pt->size)
        {
            MessageBoxA(ui::handle::frm_Main, pt ? pt->id : "No ID", "Invalid patch table", 0);

            if (out_status)
                *out_status = HCASMSTATUS::HC_ASM_INVALID;

            return hcasm_to_text[static_cast<unsigned char>(HCASMSTATUS::HC_ASM_INVALID)];
        }

        DWORD          oldProtect = 0; // Stores the old protection flag of the memory section
        unsigned char  singlebyte = 0x0; // Used if allocation is unecessary
        unsigned char* readbuffer = pt->size > 1 ? new unsigned char[pt->size] : &singlebyte; // Points to the byte array for comparison
        HCASMSTATUS    asmstat    = HCASMSTATUS::HC_ASM_INVALID; // Status of the assembly

        if (!readbuffer)
            return nullptr;

        // Unlocks the memory, reads it into a buffer, then restores its original protection flag
        if (!VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, PAGE_READWRITE, &oldProtect)
        ||  !ReadProcessMemory(handycafe::handle, handycafe::base + pt->offset, readbuffer, pt->size, NULL)
        ||  !VirtualProtectEx(handycafe::handle, handycafe::base + pt->offset, pt->size, oldProtect, &oldProtect)
        ) {
            delete[] readbuffer;
            MessageBoxA(ui::handle::frm_Main, pt->id, "ASM check failed on id", 0);
            return nullptr;
        }

        // Check for Patch bytes
        if (comparebytes(readbuffer, pt->byte_new, pt->size))
            asmstat = HCASMSTATUS::HC_ASM_PATCHED;
        // Check if bytes are unmodified
        else if (comparebytes(readbuffer, pt->byte_old, pt->size))
            asmstat = HCASMSTATUS::HC_ASM_ORIGIN;
        // If neither, by default the byte array is invalid.

        // Return the asm status through the out_status pointer if available
        if (out_status)
            *out_status = asmstat;

        // Delete the buffer
        delete[] readbuffer;

        // Return the status
        return hcasm_to_text[static_cast<unsigned char>(asmstat)];
    }
}