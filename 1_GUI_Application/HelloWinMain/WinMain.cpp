/*
 *	Short description on Windows programming
 *
 *	@Author	: Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	: DSSD-Windows_System_Programming
 */


#include <windows.h>		// windows main header file
#include <stdio.h>

/*
	WINDOWS PROGRAMMING : 

		WIN32 is the SDK(language) is based on C language, is used to perform system operation on Windows 
		platform.
		This will also provide the UI based application. Designing the UI Based Window you need to program it.
		The WNDCLASS is one of the structure is used to submit the UI specification to kernel
		that you want to design.
		
		Apart from this, The Windows programming is completely based on Message Queue (IPC) mechanism
		whatever any event occure (like Mouse Clicks, keyboard button pressed, Mouse pointer move) with
		your window (it is not Windows) the kernel will generate the event handler and using
		Message passing techique, OS itself will pass the message to your Application(Window).
		some of the messages are: WM_CREATE, WM_SHOW, WM_PAINT, WM_CHAR.
		All messages are like CALLBACK calls

		After getting the message(event) from kernel programmer need to be handle on their basis (like
		what operation he/she want to do after getting that message).

		In Short: Windows programming is just the handling the messages(Events), and coming to logic
		that you have to build according to the requirement.
*/


// callback function, for handling the messages from kernel
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// wntry point function for Windows program (HINSTANCE - Handle of current running process)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;								// message Structure for getting the message from kernel
	HWND hwnd;								// get the handle for holding Window of our process
	WNDCLASSEX wndclassex;					// get the structure object for design the Window
	TCHAR AppName[] = L"MyWindow";			// Window Object Name

	// fill the structure object (this data will deside the Window screen)
	wndclassex.cbSize = sizeof(WNDCLASSEX);								// Structure Size
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	// Color for client area
	wndclassex.hCursor = LoadCursor(hInstance,TEXT("IDI_ICON"));		// Cursor info
	wndclassex.hIcon = LoadIcon(hInstance,TEXT("IDI_ICON"));			// Icon info
	wndclassex.hIconSm = LoadIcon(hInstance,TEXT("IDI_ICON"));			// Taskbar icon
	wndclassex.hInstance = hInstance;									// give the current process handle
	wndclassex.lpfnWndProc = WndProc;									// give the name of CALLBACK func
	wndclassex.lpszClassName = AppName;									// name for the window
	wndclassex.lpszMenuName = NULL;										// Menu if required
	wndclassex.style = CS_HREDRAW|CS_VREDRAW;							// Style for the Window

	// Register the Window's Data with Kernel
	RegisterClassEx(&wndclassex);

	// create the window on RAM (mean the window will not visible to user)
	hwnd = CreateWindow(AppName,										// Object Name						
						L"HelloWindow",									// Window Title name
						WS_OVERLAPPEDWINDOW,							// Window Specification
						100,											// X-axis on Shell screen
						100,											// Y-axis on Shell screen
						300,											// Window Height
						300,											// Window Length
						NULL,											// Parent of this Window
						NULL,											// Menu for the Window
						hInstance,										// Handle of the process
						NULL);											// parameter that want to pass

	// check whether window is successfully created or not
	if(NULL == hwnd)
	{
		MessageBox(hwnd,L"Sorry : unable to get the Window",L"Error",MB_OK);
		exit(1);
	}

	// Show our Window on user screen/shell
	ShowWindow(hwnd,nShowCmd);		// This will internally sends the message WM_SHOWWINDOW to WndProc
	UpdateWindow(hwnd);				// THis will internally sends the message WM_REPAINTWINDOW to WndProc
	
	// get the Message loop, so our process will continuously receives the messages from Kernel
	while(GetMessage(&msg,hwnd,0,0))
	{
		TranslateMessage(&msg);		// It Check the message
		DispatchMessage(&msg);		// from this control will pass to WndProc (internally) for all messages
	}

	return ((int)msg.wParam);
}

// lets define the CALLBACK function, so we can get the KERNEL's message
// (every received message(to our process) will come into this function)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// separate out the messages using switch statement
	switch(iMsg)
	{
		// This is the first message is received by your Window (it is not Windows (Operating System))
		// when your application(i.e Window) is receives this message that time Window is in creation mode.
		// i.e. Not Completely created
		case WM_CREATE:
			{
				MessageBox(hwnd,L"WM_CREATE",L"Message",MB_OK);
				break;
			}

		// This message will receive, when your Window is comming on screen (being loading)
		// i.e window is created but not completely visible 
		case WM_SHOWWINDOW:
			{
				MessageBox(hwnd,L"WM_SHOWWINDOW",L"Message",MB_OK);
				break;
			}

		// after showwindow kernel starts painting the Window (specification that you
		//submited using WNDCLASS structure) on Screen/shell.
		// Kernel generates this message continuously, so your Window may get this message more than 15-20 times
		// because painting a Window will happen on every clicks
		case WM_PAINT:
			{
				MessageBox(hwnd,L"WM_PAINT",L"Message",MB_OK);
				break;
			}

		// This is the last message that your window will receives (after click on close (X) button)
		case WM_DESTROY:
			{
				// you have to put the explicit QUIT message into message Pool so that will pass to DefWindowProc
				PostQuitMessage(0);
				ExitProcess(0);
				break;
			}
	}

	// secret of Windows Programming
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}
