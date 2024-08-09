#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <filesystem>

namespace fs = std::filesystem;

class Console
{
public:
    void Spacing(bool sleep)
    {
        std::cout << std::endl;

        if(sleep)
            Sleep(1000);
    }

    void Clear()
    {
        system("cls");
    }
};

Console console;

class Code
{
public:

void IntializeWindowFormat(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = { static_cast<short>(width), static_cast<short>(height) };

    SetConsoleScreenBufferSize(hConsole, newSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<short>(width - 1), static_cast<short>(height - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    HWND hConsoleWnd = GetConsoleWindow();
    LONG style = GetWindowLong(hConsoleWnd, GWL_STYLE);
    style &= ~WS_SIZEBOX; 
    style &= ~WS_MAXIMIZEBOX; 
    SetWindowLong(hConsoleWnd, GWL_STYLE, style);
    SetConsoleTitle("lunatic.os");
}

void SetConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void PrintColoredLine(const std::string& line, WORD color) {
    SetConsoleColor(color);
    std::cout << line << std::endl;
}

void print(const std::string& text) {

    const WORD blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const WORD white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    SetConsoleColor(blue);
    std::cout << "  [Lunatic] ";

    SetConsoleColor(white);
    std::cout << text << std::endl;

    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void displayLogo() {

    const WORD colors[] = {
        FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

    const std::string lines[] = {
        "           __    __  ___   _____  ________________",
        "          / /   / / / / | / /   |/_  __/  _/ ____/",
        "         / /   / / / /  |/ / /| | / /  / // /     ",
        "        / /___/ /_/ / /|  / ___ |/ / _/ // /___   ",
        "       /_____/_/____/_/ |_/_/  |_/_/ /___/\\____/  ",
        "                                                   ",
        "    #1 Windows optimizer for Gamers & Professionals.     "
    };

    for (size_t i = 0; i < 6; ++i) {
        PrintColoredLine(lines[i], colors[i % 5]);
    }

    PrintColoredLine(lines[6], FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    std::cout << std::endl;

    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

};

Code code;

class Optimizer
{
public:

    void RestartExplorer()
    {
        // Gracefully close Explorer
        HWND hShellWindow = GetShellWindow();
        if (hShellWindow != NULL)
        {
            DWORD processID = 0;
            GetWindowThreadProcessId(hShellWindow, &processID);
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 1);
                CloseHandle(hProcess);
            }
        }

        // Restart Explorer
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = "open";
        sei.lpFile = "explorer.exe";
        sei.nShow = SW_SHOWNORMAL;
        ShellExecuteEx(&sei);
    }

    bool executeCommand(const std::wstring& command) {
        STARTUPINFOW si = { sizeof(STARTUPINFOW) };
        PROCESS_INFORMATION pi;

        if (!CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
            return false;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
    }

    void optimizeWindowsStartMenu() {
        // Remove unnecessary startup items (example: disable OneDrive)
        std::wstring disableOneDrive = L"powershell -Command \"Disable-ItemProperty -Path 'HKCU:\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run' -Name 'OneDrive'\"";
        executeCommand(disableOneDrive);

        // Remove all Start Menu tiles
        std::wstring removeTiles = L"powershell -Command \"Get-StartApps | foreach {Unpin-StartMenuItem -Name $_.Name}\"";
        executeCommand(removeTiles);

        // Disable background apps (example: disable Cortana and others)
        std::wstring disableCortana = L"powershell -Command \"Set-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Search' -Name 'CortanaConsent' -Value 0\"";
        executeCommand(disableCortana);

        // Disable live tiles in Start Menu
        std::wstring disableLiveTiles = L"powershell -Command \"Get-StartApps | foreach {Disable-StartTile -Name $_.Name}\"";
        executeCommand(disableLiveTiles);

        // Remove unnecessary apps from the Start Menu
        std::wstring removeApps = L"powershell -Command \"Get-AppxPackage *Microsoft* | Remove-AppxPackage\"";
        executeCommand(removeApps);

        // Additional optimizations can be added here...
    }

    void configureBootSettings() {

        std::wstring quietBootCommand = L"bcdedit /set {current} quietboot yes";
        executeCommand(quietBootCommand);

        std::wstring timeoutCommand = L"bcdedit /timeout 3";
        executeCommand(timeoutCommand);
    }

    void disableIPv6() {
        const std::wstring subKey = L"SYSTEM\\CurrentControlSet\\Services\\Tcpip6\\Parameters";
        const std::wstring valueName = L"DisabledComponents";
        DWORD value = 0xFF; 

        SetRegistryDWORD(HKEY_LOCAL_MACHINE, subKey, valueName, value);
    }

   

    void DisableUnnecessaryFeatures()
    {
        DisablePrivacySettings();
        DisableActionsAndNotifications();
        DisableFocusAssist();
        DisableSleepMode();
        DisableSharedExperiences();
        DisableAnimationsAndTransparency();
        DisableUselessServices();
    }

    void DisableTaskbarElements()
    {
        DisableSearchButton();
        DisableTaskViewButton();
        DisableAllExceptWindowsButton();
        DisablePeopleIcon();
    }


    void DisablePrivacySettings()
    {
        std::vector<std::wstring> appPermissionsKeys = {
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userDataTasks",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\contacts",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\email",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\phoneCall",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\documentsLibrary",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\picturesLibrary",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\videosLibrary",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\broadFileSystemAccess",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\cellularData",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\chat",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\gazeInput",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\radios",
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userNotificationListener"
        };

        for (const auto& key : appPermissionsKeys)
        {
            DisableAppPermission(key);
        }
    }

    void DisableUselessServices()
    {
        std::vector<std::wstring> servicesToDisable = {
          L"SysMain",
          L"XboxGipSvc",
          L"wuauserv",
          L"MixedRealityOpenXRSvc",
          L"WalletService",
          L"TapiSrv",
          L"LanmanWorkstation",
          L"Spooler",
          L"TermService",
          L"WFDSConMgrSvc",
          L"PhoneSvc",
          L"icssvc",
          L"DPS",
          L"PcaSvc",
          L"RmSvc",
          L"lfsvc",
          L"SharedRealitySvc",
          L"EventLog",
          L"OneSyncSvc_5c119",
          L"RasMan",
          L"DusmSvc"
        };

        for (const auto& serviceName : servicesToDisable)
        {
            DisableService(serviceName);
        }
    }

private:

    void ExecutePowerShellScript(const std::string& command) {

        std::string psCommand = "powershell.exe -NoProfile -ExecutionPolicy Bypass -Command \"" + command + "\"";
        system(psCommand.c_str());
    }

    bool SetRegistryDWORD(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, DWORD value)
    {
        HKEY hKey;
        LONG result = RegOpenKeyExW(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            std::wcerr << L"Failed to open registry key: " << subKey << L" with error code: " << result << std::endl;
            return false;
        }

        result = RegSetValueExW(hKey, valueName.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
        if (result != ERROR_SUCCESS)
        {
            std::wcerr << L"Failed to set registry value: " << valueName << L" with error code: " << result << std::endl;
            RegCloseKey(hKey);
            return false;
        }

        RegCloseKey(hKey);
        return true;
    }

    bool DisableAppPermission(const std::wstring& registryKey)
    {
        HKEY hKey;
        LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, registryKey.c_str(), 0, KEY_SET_VALUE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            return false;
        }

        DWORD value = 0; 
        result = RegSetValueExW(hKey, L"Value", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
        if (result != ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            return false;
        }

        RegCloseKey(hKey);
        return true;
    }

    bool DisableService(const std::wstring& serviceName)
    {
        SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

        SC_HANDLE service = OpenServiceW(scManager, serviceName.c_str(), SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_CHANGE_CONFIG);

        SERVICE_STATUS status;
        ControlService(service, SERVICE_CONTROL_STOP, &status);

        if (!ChangeServiceConfig(
            service, // service handle
            SERVICE_NO_CHANGE, // service type
            SERVICE_DISABLED, // start type
            SERVICE_NO_CHANGE, // error control
            NULL, // binary path
            NULL, // load order group
            NULL, // tag id
            NULL, // dependencies
            NULL, // service start name
            NULL, // password
            NULL)) // display name
        {
            CloseServiceHandle(service);
            CloseServiceHandle(scManager);
            return false;
        }

        CloseServiceHandle(service);
        CloseServiceHandle(scManager);
        return true;
    }

    void DisableAnimationsAndTransparency()
    {
        std::wstring animationsKey = L"Control Panel\\Desktop";
        SetRegistryDWORD(HKEY_CURRENT_USER, animationsKey, L"UserPreferencesMask", 0x9012c);

        std::wstring performanceKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VisualEffects";
        SetRegistryDWORD(HKEY_CURRENT_USER, performanceKey, L"VisualFXSetting", 2); 

        SystemParametersInfo(SPI_SETUIEFFECTS, 0, NULL, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE); 

        std::wstring transparencyKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
        SetRegistryDWORD(HKEY_CURRENT_USER, transparencyKey, L"EnableTransparency", 0);
    }

    void DisableActionsAndNotifications()
    {
        std::wstring registryKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\PushNotifications";
        SetRegistryDWORD(HKEY_CURRENT_USER, registryKey, L"ToastEnabled", 0);
    }

    void DisableSleepMode()
    {
        std::wstring registryKey = L"Control Panel\\PowerCfg\\GlobalPowerPolicy";
        SetRegistryDWORD(HKEY_CURRENT_USER, registryKey, L"Policies", 0x00000000);
    }

    void DisableSharedExperiences()
    {
        std::wstring registryKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SharedAccess";
        SetRegistryDWORD(HKEY_LOCAL_MACHINE, registryKey, L"Enabled", 0);
    }

    void DisableFocusAssist()
    {
        std::wstring registryKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings";
        SetRegistryDWORD(HKEY_CURRENT_USER, registryKey, L"NOC_GLOBAL_SETTING_ALLOW_CRITICAL", 0);
        SetRegistryDWORD(HKEY_CURRENT_USER, registryKey, L"NOC_GLOBAL_SETTING_ALLOW_ALARMS", 0);
        SetRegistryDWORD(HKEY_CURRENT_USER, registryKey, L"NOC_GLOBAL_SETTING_ALLOW_PRIORITY", 0);
    }

    void DisableSearchButton()
    {
        std::wstring searchKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search";
        SetRegistryDWORD(HKEY_CURRENT_USER, searchKey, L"SearchboxTaskbarMode", 0); // 0 = Hide, 1 = Show icon only, 2 = Show search box
    }

    // Disable Task View button (Active applications button)
    void DisableTaskViewButton()
    {
        std::wstring taskViewKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
        SetRegistryDWORD(HKEY_CURRENT_USER, taskViewKey, L"ShowTaskViewButton", 0); // 0 = Hide, 1 = Show
    }

    void DisablePeopleIcon()
    {
        std::wstring peopleKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\People";
        SetRegistryDWORD(HKEY_CURRENT_USER, peopleKey, L"PeopleBand", 0); // 0 = Hide, 1 = Show
    }

    // Disable everything except the Windows button
    void DisableAllExceptWindowsButton()
    {
        // Hiding all other taskbar buttons except the Start button.
        std::wstring explorerKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";

        // Hide the People icon
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"PeopleBand", 0);

        // Hide Cortana (already covered by Search button, but additional safety)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"ShowCortanaButton", 0);

        // Hide Meet Now icon
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"TaskbarMn", 0);

        // Hide News and Interests (if available)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"TaskbarDa", 0);

        // Hide Pen Menu (if available)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"ShowPenMenuButton", 0);

        // Hide Virtual Touchpad (if available)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"ShowTouchpadButton", 0);

        // Hide Widgets (on Windows 11)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"TaskbarSi", 0);

        // Hide Task View (already covered, but additional safety)
        SetRegistryDWORD(HKEY_CURRENT_USER, explorerKey, L"ShowTaskViewButton", 0);

        // Disable Quick Launch Bar (if available)
        std::wstring quickLaunchKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
        SetRegistryDWORD(HKEY_CURRENT_USER, quickLaunchKey, L"NoToolbarCustomize", 1);
    }
};

Optimizer optimizer;

std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}

class Cleaning
{
public:

    std::string getAppDataPath(bool isLocal) {
        char path[MAX_PATH];
        if (SHGetFolderPathA(NULL, isLocal ? CSIDL_LOCAL_APPDATA : CSIDL_APPDATA, NULL, 0, path) == S_OK) {
            return std::string(path);
        }
        std::cerr << "Error: Unable to get AppData path.\n";
        return "";
    }


    void cleanFiles()
    {
        deleteTemporaryDirectories();
    }



    void uninstallMicrosoftApps() {
        std::vector<std::wstring> appsToUninstall = {
            L"Microsoft.BingWeather",
            L"Microsoft.GetHelp",
            L"Microsoft.Getstarted",
            L"Microsoft.Office.OneNote",
            L"Microsoft.MicrosoftSolitaireCollection",
            L"Microsoft.MicrosoftStickyNotes",
            L"Microsoft.MSPaint",
            L"Microsoft.OneConnect",
            L"Microsoft.People",
            L"Microsoft.Print3D",
            L"Microsoft.SkypeApp",
            L"Microsoft.Todos",
            L"Microsoft.Whiteboard",
            L"Microsoft.WindowsAlarms",
            L"Microsoft.WindowsCamera",
            L"Microsoft.WindowsMaps",
            L"Microsoft.WindowsSoundRecorder",
            L"Microsoft.Xbox.TCUI",
            L"Microsoft.XboxApp",
            L"Microsoft.XboxGameOverlay",
            L"Microsoft.XboxGamingOverlay",
            L"Microsoft.XboxIdentityProvider",
            L"Microsoft.XboxSpeechToTextOverlay",
            L"Microsoft.YourPhone",
            L"Microsoft.ZuneMusic",
            L"Microsoft.ZuneVideo"
        };

        for (const auto& app : appsToUninstall) {
            std::wstring command = L"powershell -Command \"Get-AppxPackage -Name " + app + L" -AllUsers | Remove-AppxPackage -AllUsers\"";
            
            
           // code.print("Uninstalling " + wstringToString(app) + "...");

            optimizer.executeCommand(command);
        }
    }

private:
    void deleteDirectory(const fs::path& dirPath) {
        try {
            if (fs::exists(dirPath)) {
                if (fs::is_directory(dirPath)) {
                    fs::remove_all(dirPath); // Recursively delete the directory and its contents
           
                }
                else {
       
                }
            }
            else {

            }
        }
        catch (const fs::filesystem_error& e) {
       
        }
    }

    void deleteTemporaryDirectories() {
        // Get paths for both Local and Roaming AppData directories
        std::string localAppDataPath = getAppDataPath(true);
        std::string roamingAppDataPath = getAppDataPath(false);

        if (localAppDataPath.empty() || roamingAppDataPath.empty()) {
  
            return;
        }

        // Define directories to delete
        std::vector<std::string> directories = {
            "C:\\Windows\\Temp",
            localAppDataPath + "\\Temp",
            "C:\\Windows\\Prefetch",
            "C:\\PerfLogs",
            "C:\\Windows\\Logs",
            roamingAppDataPath + "\\Microsoft\\Windows\\Recent"
        };

        // Delete specified directories
        for (const auto& dir : directories) {
            deleteDirectory(dir);
        }
    }
};
class Aesthetic
{
public:
    void setCursorToBlack() {

        downloadCursor();

        Sleep(2000);

        LPCSTR cursorPath = "C:\\Windows\\Cursors\\LunaticCursor.cur";

        HCURSOR hCursor = LoadCursorFromFile(cursorPath);

        if (hCursor) {
            SetSystemCursor(hCursor, 32512);
        }
        else {
        }
    }

    void setBackground()
    {
        downloadBackground();
        Sleep(1200);

        SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID*)"C:\\Windows\\Resources\\Themes\\LunaticWallpaper.png", SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    }

private:
    void downloadCursor()
    {
        optimizer.executeCommand(L"curl -o \"C:\\Windows\\Cursors\\LunaticCursor.cur\" \"https://cdn.discordapp.com/attachments/1232373870225526834/1271287381437190254/cursor.cur?ex=66b6ca23&is=66b578a3&hm=8d10bba426884088de65d239ae93e7cf06e8135e67d003d496e7d5bab8cf040e&\"");
    }

    void downloadBackground()
    {
        optimizer.executeCommand(L"curl -o \"C:\\Windows\\Resources\\Themes\\LunaticWallpaper.png\" \"https://cdn.discordapp.com/attachments/1232373870225526834/1271297664104792095/Sans_titre.png?ex=66b6d3b6&is=66b58236&hm=f70082028e9f216bb7fbdee992b63f6b35a0a94673423e341c31b53ef674ab13&\"");
    }
};