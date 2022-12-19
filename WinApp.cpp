#include "WinApp.h"
#include <Windows.h>

#pragma comment(lib,"winmm.lib")

void WinApp::Initialize()
{
    // �E�B���h�E�N���X�̐ݒ�

    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = (WNDPROC)WindowProc; // �E�B���h�E�v���V�[�W����ݒ�
    w.lpszClassName = L"DirectXGame"; // �E�B���h�E�N���X��
    w.hInstance = GetModuleHandle(nullptr); // �E�B���h�E�n���h��
    w.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

    // �E�B���h�E�N���X��OS�ɓo�^����
    RegisterClassEx(&w);
    // �E�B���h�E�T�C�Y{ X���W Y���W ���� �c�� }
    RECT wrc = { 0, 0, window_width, window_height };
    // �����ŃT�C�Y��␳����
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    // �E�B���h�E�I�u�W�F�N�g�̐���
    hwnd = CreateWindow(w.lpszClassName, // �N���X��
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

    // �E�B���h�E��\����Ԃɂ���
    ShowWindow(hwnd, SW_SHOW);

    //�V�X�e���^�C�}�[�̕���\���グ��
    timeBeginPeriod(1);

}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //���b�Z�[�W�ŕ���
    switch (msg)
    {
    case WM_DESTROY:       
        PostQuitMessage(0);
        return 0;;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);//�W���̏������s��

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
    // �E�B���h�E�N���X��o�^����
    UnregisterClass(w.lpszClassName, w.hInstance);
}