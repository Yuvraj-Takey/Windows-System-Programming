/*
 *	Demonstrate the working of dynamic link library and exported functions in windows
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming
 */


#include <stdio.h>
#include <windows.h>

int main()
{
	HMODULE hLib;
	char*(*dllFun)();

	// Loads the specified module into the address space of the calling process
	if((hLib = LoadLibrary(L"DLL_Make")) == NULL)
	{
		printf("sorry : LoadLibrary errorcode [%d]\n",GetLastError());
		return -1;
	}
	
	// Retrieves the address of an exported function or variable from the specified DLL
	if((dllFun = (char*(*)())GetProcAddress(hLib,"PrintString")) == NULL)
	{
		printf("sorry : GetProcAddress errorcode [%d]\n",GetLastError());

		// release the library
		FreeLibrary(hLib);

		return -1;
	}

	// get the data from DLL
	printf("Using DLL - [%s]\n",dllFun());

	// release the library
	FreeLibrary(hLib);

}
