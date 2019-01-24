/*
 *	Demonstrate the working of Named Pipe (IPC Mechanism) in windows, Create separate thread for IPC operation
 *
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [SERVER - Application]
 */


#include <windows.h>
#include <stdio.h>
#define MAXBUFF	50

DWORD ThreadProc(LPVOID);
static HANDLE hPipe, hThread;

int main(int argc, char *argv[])
{
	printf("WINAPI CODE [Server Running..]\n\n");

	// it Creates an instance of a named pipe and returns a handle for subsequent pipe operations (ATU)
	hPipe = CreateNamedPipe(L"\\\\.\\pipe\\MyPipe",			// pipe name
							PIPE_ACCESS_DUPLEX,				// pipe opening mode [Get the bi-directional Pipe]
							PIPE_TYPE_BYTE,					// pipe mode [Data is written to the pipe as a stream of bytes]
							PIPE_UNLIMITED_INSTANCES,		// The maximum number of instances that can be created for this pipe.
							MAXBUFF,						// The number of bytes to reserve for the output buffer
							MAXBUFF,						// The number of bytes to reserve for the input buffer
							0,								// The default time-out value, in milliseconds,
							NULL);							// SECURITY level

	if(hPipe == NULL)
	{
		printf("sorry : Create Pipe [%d]\n",GetLastError());
		return -1;
	}

	// create the thread
	hThread = CreateThread(NULL,							// determines whether the returned handle can be inherited by child processes
						   0,								// The initial size of the stack, in bytes. 
						   (LPTHREAD_START_ROUTINE)ThreadProc,// Thread Function
						   (LPVOID)NULL,					// Parameter that want to pass to ThreadProc function
						   0,								// Thread Creation flag that control thread
						   0);								// The thread identifier.

	// check thread creation status
	if(hThread == NULL)
	{
		return -1;
	}

	// wait for child thread
	WaitForSingleObject(hThread,INFINITE);

	// close the pipe
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}

DWORD ThreadProc(LPVOID pop)
{
	// Enables a server process to wait for a client process to request for connect.
	if(!ConnectNamedPipe(hPipe,NULL))
	{
		printf("sorry : Connect [%d]\n",GetLastError());
		return -1;
	}

	char buffer[MAXBUFF] = "HELLO FROM SERVER";
	DWORD byteSuccess;


	// IF CLIENT MAKES REQUEST TO SERVER,

	// Write the data into pipe
	if(!WriteFile(hPipe,buffer,strlen(buffer),
			&byteSuccess					// A pointer to the variable that receives the number of bytes written
			,NULL))
	{
		printf("sorry : Write File [%d]\n",GetLastError());
		return -1;
	}

	printf("Successfull Execution\n");

	return 0;
}
