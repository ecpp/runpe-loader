#include "api.h"
#include <iostream>
#include <vector>
#include <shlwapi.h>
#include <tchar.h>
#include "pre-loader.h"
#pragma comment(lib, "shlwapi.lib")

std::string version = "0.1";

int main()
{
    if (!isRunningAsAdmin()) {
		std::cout << "Please run as admin!" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 0;
	}

    API api;

    if (!api.checkLoaderVersion(version, "pre-loader")) {
		std::cout << "Outdated version!" << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 0;
	}


    std::vector<std::string> dllList;
    dllList.push_back("libssl-1_1-x64.dll");
    dllList.push_back("libcrypto-1_1-x64.dll");

    for (auto& dll : dllList) {
        std::cout << "Checking: " << dll << '\n';
        if (!checkDllExists(api.get_system32_path(), dll)) {
            std::cout << "Downloading missing: " << dll;
            if (!api.downloadDll(dll)) {
                std::cout << "...FAILED" << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return 0;
            }
            std::cout << "...OK" << '\n';
        }
        else
        {
            std::cout << dll << "...OK" << '\n';
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
	}
    //hide console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    if (!api.downloadLoader())
    {
		std::cout << "Failed to start loader!" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 0;
	}
    
}