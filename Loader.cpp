#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "globals.h"
#include "Loader.h"
#include "icons.h"
#include "menu.h"
#include <string>
#include <codecvt>
#include <locale>
#define NOMINMAX // You have to do this for windows.h to work, else u'll get mistakes with datetime.h           
#include <windows.h> // (without the space)    
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Advapi32.lib")
#include <ShellAPI.h> // without space also
#include <WinBase.h>


std::string convert_wchar_to_string(const wchar_t* wstr) {
    // Create a wide string from the wchar_t*
    std::wstring w(wstr);

    // Create a converter object using the selected locale
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Convert the wide string to a narrow string using the converter
    std::string str = converter.to_bytes(w);

    return str;
}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (!isRunningAsAdmin()) {
		MessageBoxA(NULL, "Please run the loader as a admin.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

    
    try {
        if (!globals::api.checkLoaderVersion()) {
            MessageBoxA(NULL, "Please download the latest version of the loader.", "Error", MB_OK | MB_ICONERROR);
            return 0;
        }
    }
    catch (const std::exception& e) {
        MessageBoxA(NULL, "Failed to connect to the server. Please check your internet connection.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    HW_PROFILE_INFO hwProfileInfo;
    if (GetCurrentHwProfile(&hwProfileInfo)) {
        globals::hwid = convert_wchar_to_string(hwProfileInfo.szHwProfileGuid);
	}
    else {
        MessageBoxA(NULL, "Can't get HWID.", "Error", MB_OK | MB_ICONERROR);
	}
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandleA(0), 0,0,0, 0, L"set to anything", 0 };
    RegisterClassEx(&wc);
    Window = CreateWindow(wc.lpszClassName, L"3r3n.3x3 L04D3R", WS_POPUP, 0, 0, 5, 5, 0, 0, wc.hInstance, 0);

    if (!CreateDeviceD3D(Window)) 
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(Window, SW_HIDE);
    UpdateWindow(Window);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 
   
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 19.5, &CustomFont);
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 32.5f, &icons_config, icons_ranges);
    io.Fonts->AddFontDefault();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    MSG msg;

    memset(&msg, 0, sizeof(msg));
   
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        Menu::Theme();
        {   
            
            
            ImGui::Begin("3r3n.3x3 L04D3R", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            {
                Menu::Render();
            }
            ImGui::End();
            
      
        }
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!Enabled) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(Window);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}