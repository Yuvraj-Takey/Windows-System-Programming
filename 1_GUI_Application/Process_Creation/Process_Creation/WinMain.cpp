/**********************************************************************************************

	Demonstrate the Multithreading in win32

	@Author	- Yuvraj Takey
 		  yuvraj.takey@gmail.com
 	@Title	- Windows_System_Program

***********************************************************************************************/


#include <stdio.h>
#include <windows.h>

// callback function for mesage receive
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// internally	:	#define WINAPI __stdcall
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wndclassex;
	TCHAR AppName[] = TEXT("Window");

	// design our application window
	wndclassex.cbClsExtra = 0;
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.cbWndExtra = 0;
	wndclassex.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclassex.hCursor = LoadCursor(hInstance,TEXT("IDI_ICON"));
	wndclassex.hIcon = LoadIcon(hInstance,TEXT("IDI_ICON"));
	wndclassex.hIconSm = LoadIcon(hInstance,TEXT("IDI_ICON"));
	wndclassex.hInstance = hInstance;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.lpszClassName = AppName;
	wndclassex.lpszMenuName = NULL;
	wndclassex.style = CS_HREDRAW|CS_VREDRAW;

	// Register our program class with os
	RegisterClassEx(&wndclassex);

	// create the window
	hWnd = CreateWindow(AppName,L"Threading",WS_OVERLAPPEDWINDOW,100,100,300,300,NULL,NULL,hInstance,NULL);
	if(NULL == hWnd)
	{
		MessageBox(NULL,L"SORRY : unable to load window",L"Caution",MB_OK);
		exit(0);
	}

	// get the window
	ShowWindow(hWnd,nShowCmd);
	UpdateWindow(hWnd);

	// enable listening the messages from kernel
	while(GetMessage(&msg,hWnd,0,0))
	{
		// filter the messages
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

// message callback function
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND thStart1 = NULL, thStart2 = NULL;
	//HINSTANCE hInstance = GetModuleHandleA(NULL);
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongA(hWnd,GWLP_HINSTANCE);

	switch(iMsg)
	{
	case WM_CREATE:
		{
			// create the button
			thStart1 = CreateWindow(L"BUTTON",L"Notepad",
				 WS_VISIBLE | WS_CHILD ,
				45,95,80,30,hWnd,NULL,hInstance,NULL);

			thStart2 = CreateWindow(L"BUTTON",L"Calculator",
				 WS_VISIBLE | WS_CHILD ,
				145,95,80,30,hWnd,NULL,hInstance,NULL);

			break;
		}
	case WM_SHOWWINDOW:
		{
			// code
			break;
		}

	case WM_COMMAND:
		{
			int iret = 0;
			TCHAR str[20];

			STARTUPINFO s_info;
			PROCESS_INFORMATION p_info;

			ZeroMemory( &s_info, sizeof(s_info) );
			s_info.cb = sizeof(s_info);
			ZeroMemory( &p_info, sizeof(p_info) );

			// handle Notepad application
			if(thStart1 == (HWND)lParam)
			{
				iret = CreateProcess(TEXT("C:\\Windows\\notepad.exe"),NULL,
					NULL,NULL,FALSE,0,NULL,NULL, &s_info, &p_info);
			
			}// handle calculator application
			else if(thStart2 == (HWND)lParam)
			{
				iret = CreateProcess(TEXT("C:\\Windows\\System32\\calc.exe"),NULL,
					NULL,NULL,FALSE,0,NULL,NULL, &s_info, &p_info);
			}

			break;
		}
	case WM_DESTROY:
		{
			// post the message self into message pool
			PostQuitMessage(0);
			ExitProcess(0);
			break;
		}
	default:
		{
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
		}
	}
}

