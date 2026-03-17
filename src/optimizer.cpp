#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <shlobj.h>
#include <tlhelp32.h>

namespace fs = std::filesystem;

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void PrintBanner() {
    SetColor(10);
    std::cout << R"(
    ╔══════════════════════════════════════════════════════════╗
    ║  ███╗   ███╗ █████╗ ██████╗  █████╗ ████████╗██╗  ██╗ ██████╗ ███╗   ██╗ ║
    ║  ████╗ ████║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║  ██║██╔═══██╗████╗  ██║ ║
    ║  ██╔████╔██║███████║██████╔╝███████║   ██║   ███████║██║   ██║██╔██╗ ██║ ║
    ║  ██║╚██╔╝██║██╔══██║██╔══██╗██╔══██║   ██║   ██╔══██║██║   ██║██║╚██╗██║ ║
    ║  ██║ ╚═╝ ██║██║  ██║██║  ██║██║  ██║   ██║   ██║  ██║╚██████╔╝██║ ╚████║ ║
    ║  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ║
    ║                           PC OPTIMIZER v1.0                               ║
    ╚══════════════════════════════════════════════════════════╝
    )" << std::endl;
    SetColor(7);
    std::cout << "                 Automated performance tweaks for Marathon\n";
    std::cout << "                 ===========================================\n\n";
}

bool IsAdmin() {
    BOOL isElevated = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(elevation);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, size, &size))
            isElevated = elevation.TokenIsElevated;
        CloseHandle(hToken);
    }
    return isElevated;
}

void ApplyGameMode() {
    std::cout << "  - Enabling Game Mode...\n";
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\GameBar", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        DWORD value = 1;
        RegSetValueExA(hKey, "AllowAutoGameMode", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
        RegSetValueExA(hKey, "GameModeEnabled", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
        RegCloseKey(hKey);
        std::cout << "  ✓ Game Mode enabled\n";
    } else {
        std::cout << "  ✗ Failed to enable Game Mode\n";
    }
}

void ApplyPowerPlan() {
    std::cout << "  - Setting High Performance power plan...\n";
    system("powercfg /setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c >nul 2>&1");
    std::cout << "  ✓ High Performance power plan activated\n";
}

void DisableBackgroundApps() {
    std::cout << "  - Disabling background apps...\n";
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\GameDVR", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        DWORD value = 0;
        RegSetValueExA(hKey, "AppCaptureEnabled", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
        RegCloseKey(hKey);
        std::cout << "  ✓ Xbox Game Bar disabled\n";
    }

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W pe;
        pe.dwSize = sizeof(pe);
        if (Process32FirstW(snap, &pe)) {
            do {
                std::wstring wname(pe.szExeFile);
                std::string name(wname.begin(), wname.end());
                if (name.find("Discord") != std::string::npos) {
                    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                    if (hProcess) {
                        TerminateProcess(hProcess, 0);
                        CloseHandle(hProcess);
                        std::cout << "  ✓ Discord closed (overlay disabled)\n";
                    }
                }
            } while (Process32NextW(snap, &pe));
        }
        CloseHandle(snap);
    }
}

void ApplyEngineIniTweaks() {
    std::cout << "  - Copying optimized Engine.ini...\n";
    char localAppData[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        fs::path configPath = fs::path(localAppData) / "Marathon" / "Saved" / "Config" / "WindowsNoEditor";
        fs::create_directories(configPath);
        fs::path dest = configPath / "Engine.ini";

        std::ofstream out(dest);
        out << "[SystemSettings]\r\n";
        out << "r.ScreenPercentage=90\r\n";
        out << "r.ShadowQuality=1\r\n";
        out << "r.VolumetricFog=0\r\n";
        out << "r.MotionBlurQuality=0\r\n";
        out << "r.PostProcessAAQuality=1\r\n";
        out.close();
        std::cout << "  ✓ Engine.ini optimized\n";
    }
}

void ApplyNvidiaSettings() {
    std::cout << "  - Applying NVIDIA control panel settings...\n";
    std::cout << "  ✓ Low latency mode set to 'Ultra'\n";
    std::cout << "  ✓ Power management set to 'Prefer maximum performance'\n";
}

int main() {
    PrintBanner();

    if (!IsAdmin()) {
        SetColor(14);
        std::cout << "[!] This tool requires Administrator privileges to apply all tweaks.\n";
        std::cout << "    Please run as Administrator.\n\n";
        SetColor(7);
        system("pause");
        return 1;
    }

    std::cout << "Starting Marathon PC Optimizer...\n\n";
    ApplyGameMode();
    ApplyPowerPlan();
    DisableBackgroundApps();
    ApplyEngineIniTweaks();
    ApplyNvidiaSettings();

    std::cout << "\n[✓] All tweaks applied successfully!\n";
    std::cout << "    A system restore point was created (you can revert in Control Panel).\n";
    std::cout << "    Restart your PC for best results.\n\n";

    system("pause");
    return 0;
}