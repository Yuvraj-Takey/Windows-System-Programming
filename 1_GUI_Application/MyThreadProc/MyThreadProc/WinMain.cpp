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

// Thread Handler
DWORD WINAPI Thread1(LPVOID);
DWORD WINAPI Thread2(LPVOID);


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
	HWND thStart = NULL;
	//HINSTANCE hInstance = GetModuleHandleA(NULL);
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongA(hWnd,GWLP_HINSTANCE);

	switch(iMsg)
	{
	case WM_CREATE:
		{
			// create the button
			thStart = CreateWindow(L"BUTTON",L"Start",
				 WS_VISIBLE | WS_CHILD ,
				45,95,50,30,hWnd,NULL,hInstance,NULL);
			break;
		}
	case WM_SHOWWINDOW:
		{
			// code
			break;
		}

	case WM_COMMAND:
		{
			if(thStart == (HWND)wParam)
			{
				HANDLE hTh1, hTh2;

				// create the thread as per the requirement
				hTh1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Thread1,(LPVOID)hWnd,0,NULL);
				hTh2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Thread2,(LPVOID)hWnd,0,NULL);
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

// Thread handler defination
DWORD WINAPI Thread1(LPVOID hwnd)
{
	HDC hdc;
	int index = 0;
	TCHAR str[40];

	// get the handle of device context
	hdc = GetDC((HWND)hwnd);

	// iterate the loop
	for(index = 100000; index >= 0; index--)
	{
		// print message on screen
		wsprintf(str,TEXT("Thread one status -> %d"),index);
		TextOut(hdc,5,5,str,lstrlen(str));
		//Sleep(500);
	}

	// release the device context
	ReleaseDC((HWND)hwnd,hdc);
	return (0);
}

// Thread handler defination
DWORD WINAPI Thread2(LPVOID hwnd)
{
	HDC hdc;
	int index = 0;
	TCHAR str[40];

	// get the handle of device context
	hdc = GetDC((HWND)hwnd);

	// iterate the loop
	for(index = 100000; index >= 0; index--)
	{
		// print message on screen
		wsprintf(str,TEXT("Thread two status -> %d"),index);
		TextOut(hdc,5,45,str,lstrlen(str));
		//Sleep(500);
	}

	// release the device context
	ReleaseDC((HWND)hwnd,hdc);
	return (0);
}
