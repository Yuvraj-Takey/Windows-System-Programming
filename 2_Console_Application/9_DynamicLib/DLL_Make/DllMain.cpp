/*
 *	Create the DLL application project
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Program
 *
 */


#include <stdio.h>
#include <windows.h>

// entry point for DLL - DllMain (CALLBACK)
BOOL WINAPI DllMain(HANDLE hnd, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			printf("DLL : Process Attached\n");
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			printf("DLL : Process Detached\n");
			break;
		}
	case DLL_THREAD_ATTACH:
		{
			printf("DLL : Thread Atttached\n");
			break;
		}
	case DLL_THREAD_DETACH:
		{
			printf("DLL : Thread Detached\n");
			break;
		}
	}

	return (TRUE);
}

// export the symbol to outside
extern "C" __declspec(dllexport)char* PrintString()
{
	return ("HELLO_FROM_DLL");
}

// export the symbol to outside
extern "C" __declspec(dllexport)void PrintStringOwn()
{
	printf("HELLO_INTO_DLL\n");
}
