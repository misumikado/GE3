#include "WinApp.h"
#include <Windows.h>

#pragma comment(lib,"winmm.lib")

void WinApp::Initialize()
{
    // ウィンドウクラスの設定

    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = (WNDPROC)WindowProc; // ウィンドウプロシージャを設定
    w.lpszClassName = L"DirectXGame"; // ウィンドウクラス名
    w.hInstance = GetModuleHandle(nullptr); // ウィンドウハンドル
    w.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソル指定

    // ウィンドウクラスをOSに登録する
    RegisterClassEx(&w);
    // ウィンドウサイズ{ X座標 Y座標 横幅 縦幅 }
    RECT wrc = { 0, 0, window_width, window_height };
    // 自動でサイズを補正する
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    // ウィンドウオブジェクトの生成
    hwnd = CreateWindow(w.lpszClassName, // クラス名
        L"DirectXGame",         
        WS_OVERLAPPEDWINDOW,    
        CW_USEDEFAULT,          
        CW_USEDEFAULT,          
        wrc.right - wrc.left,   
        wrc.bottom - wrc.top,   
        nullptr,                
        nullptr,                
        w.hInstance,            
        nullptr);               

    // ウィンドウを表示状態にする
    ShowWindow(hwnd, SW_SHOW);

    //システムタイマーの分解能を上げる
    timeBeginPeriod(1);

}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //メッセージで分岐
    switch (msg)
    {
    case WM_DESTROY:       
        PostQuitMessage(0);
        return 0;;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);//標準の処理を行う

}

void WinApp::Update()
{

}

bool WinApp::ProcessMessage()
{
    MSG msg{};

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT)
    {
        return true;
    }

    return false;
}

void WinApp::Finalize()
{
    // ウィンドウクラスを登録解除
    UnregisterClass(w.lpszClassName, w.hInstance);
}