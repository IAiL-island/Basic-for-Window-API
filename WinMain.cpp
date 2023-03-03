#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "resource.h"

#define MAX_STRING			100

// 윈도울 만들 때 필수적인 것 4가지
// 1. 윈도우 클래스 등록 (Regist 함수 만듦)
// 2. 윈도우 생성 및 열기
// 3. 메시지 루프 작성
// 4. 메시지 프로시저 작성 (WndProc)

HINSTANCE _hInst;
HWND _hWnd;

TCHAR _lpszClassName[MAX_STRING] = { 0, };
TCHAR _lpszTitleName[MAX_STRING] = { 0, };

/* Window 생성 필수 전역 함수 */
void RegistWindow(HINSTANCE hInst);
bool InitializeWindow(HINSTANCE hInst, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 메시지 프로시져


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
	while (GetMessage(&message, NULL, 0, 0)) // 입력 이벤트 발생 시, 실행
	{
		TranslateMessage(&message); // Message 가공
		DispatchMessage(&message);	// 메시지 프로시져로 보내기
	}

	return 0;
}

void RegistWindow(HINSTANCE hInst)
{
	// WINDOW CLASS
	_hInst = hInst;
	WNDCLASS wc;

	// 확장 기능 설정
	wc.cbClsExtra = 0;	// 창 클래스 구조 다음에 할당할 추가 바이트 수
	wc.cbWndExtra = 0;	// 창 인스턴스 다음에 할당할 추가 바이트 수
	// 사용하지 않는 상태일 때는 0으로 초기화
	
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// window background color setting
	
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	// mouse pointer setting

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// icon setting

	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	// Menu Name

	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 화면 크기가 변화할 때 새로 그린다.

	wc.lpszClassName = _lpszClassName;
	// Class Name

	wc.hInstance = hInst;
	// 

	wc.lpfnWndProc = WndProc;
	// Message Procedure

	RegisterClass(&wc);
	// 윈도우 클래스 구조체 등록
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