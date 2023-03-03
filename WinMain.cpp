#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "resource.h"

#define MAX_STRING			100

// ������ ���� �� �ʼ����� �� 4����
// 1. ������ Ŭ���� ��� (Regist �Լ� ����)
// 2. ������ ���� �� ����
// 3. �޽��� ���� �ۼ�
// 4. �޽��� ���ν��� �ۼ� (WndProc)

HINSTANCE _hInst;
HWND _hWnd;

TCHAR _lpszClassName[MAX_STRING] = { 0, };
TCHAR _lpszTitleName[MAX_STRING] = { 0, };

/* Window ���� �ʼ� ���� �Լ� */
void RegistWindow(HINSTANCE hInst);
bool InitializeWindow(HINSTANCE hInst, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // �޽��� ���ν���


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					 LPSTR lqszCmdParam, int nCmdShow)
{
	MSG message;

	LoadString(hInstance, IDS_APP_TITLE, _lpszTitleName, MAX_STRING);
	LoadString(hInstance, IDS_WNDCLASS, _lpszClassName, MAX_STRING);

	// 1. Regist Window Class
	RegistWindow(hInstance);

	// 2. Generate & Open 
	InitializeWindow(hInstance, nCmdShow);

	// 3. Message Loop
	while (GetMessage(&message, NULL, 0, 0)) // �Է� �̺�Ʈ �߻� ��, ����
	{
		TranslateMessage(&message); // Message ����
		DispatchMessage(&message);	// �޽��� ���ν����� ������
	}

	return 0;
}

void RegistWindow(HINSTANCE hInst)
{
	// WINDOW CLASS
	_hInst = hInst;
	WNDCLASS wc;

	// Ȯ�� ��� ����
	wc.cbClsExtra = 0;	// â Ŭ���� ���� ������ �Ҵ��� �߰� ����Ʈ ��
	wc.cbWndExtra = 0;	// â �ν��Ͻ� ������ �Ҵ��� �߰� ����Ʈ ��
	// ������� �ʴ� ������ ���� 0���� �ʱ�ȭ
	
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// window background color setting
	
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	// mouse pointer setting

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// icon setting

	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	// Menu Name

	wc.style = CS_HREDRAW | CS_VREDRAW;
	// ȭ�� ũ�Ⱑ ��ȭ�� �� ���� �׸���.

	wc.lpszClassName = _lpszClassName;
	// Class Name

	wc.hInstance = hInst;
	// 

	wc.lpfnWndProc = WndProc;
	// Message Procedure

	RegisterClass(&wc);
	// ������ Ŭ���� ����ü ���
}

bool InitializeWindow(HINSTANCE hInst, int nCmdShow)
{
	_hWnd = CreateWindow(_lpszClassName, _lpszTitleName, WS_OVERLAPPEDWINDOW
						, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL
						, (HMENU)NULL, hInst, NULL);
	
	if (_hWnd == NULL)
	{
		return false;
	}

	// OPEN WINDOW
	ShowWindow(_hWnd, nCmdShow);

	return true;
}

// 4. Message Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
						 WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		{
			int comID = LOWORD(wParam);
			switch (comID)
			{
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}