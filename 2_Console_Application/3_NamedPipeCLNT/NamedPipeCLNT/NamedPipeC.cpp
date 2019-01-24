/*
 *	Demonstrate the working of Named Pipe (IPC Mechanism) in windows.
 *
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [CLIENT - Application]
 */

#include <windows.h>
#include <stdio.h>
#define MAXBUFF	50

static HANDLE hPipe;

int main()
{
	/*
		CreatePipe Creates or opens a file. The most commonly used I/O devices are as follows: file,
		directory, physical disk, volume, console buffer, tape drive, 
		communications resource, mailslot, and pipe. Default Location : \\\\.\\pipe\Pipe1
	*/
	hPipe = CreateFile(L"\\\\.\\pipe\\MyPipe",				// The name of the file to be create or open
			PIPE_ACCESS_DUPLEX,					// The requested access to the file 
			FILE_SHARE_READ | FILE_SHARE_WRITE,			// The requested sharing mode of the file (READ|WRITE)
			NULL,							// SECURITY INFO
			OPEN_EXISTING,						// FILE MODE
			FILE_ATTRIBUTE_NORMAL,					// attributes and flags
			NULL);

	if(hPipe == NULL)
	{
		printf("sorry : Create File [%d]\n",GetLastError());
		return -1;
	}
	
	// get the empty buffer for getting the data
	char buffer[MAXBUFF] = {'\0'};
	DWORD byteSuccess;

	// get the data from server
	if(!ReadFile(hPipe,buffer,MAXBUFF,&byteSuccess,NULL))
	{
		printf("sorry : Read File [%d]\n",GetLastError());
		return -1;
	}

	// print the data, which got from server
	printf("Data : [%s]\n",buffer);

	// close the pipe
	CloseHandle(hPipe);
}
