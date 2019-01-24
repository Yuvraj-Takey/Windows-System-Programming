/*
 *	Demonstrate the MailSlot IPC mechanism in windows
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [CLIENT - Application]
 */

/**
	INFO : 
		A mailslot is a mechanism for one-way interprocess communications (IPC).
		Applications can store messages in a mailslot.
		The owner of the mailslot can retrieve messages that are stored there.
		These messages are typically sent over a network to either a specified
		computer or to all computers in a specified domain.		[MAX SIZE OF MAILSLOT IS  424 bytes]
*/

#include <stdio.h>
#include <windows.h>

#define MAXBUFF	50

int main()
{

	HANDLE hMail;
	char buffer[MAXBUFF] = {"\0"};
	DWORD byteSuccess = 0, ret = 0;

	// get the mailslot file
	if((hMail = CreateFile(L"\\\\.\\mailslot\\mSlot",
							GENERIC_READ| GENERIC_WRITE,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL)) < 0)
	{
		printf("sorry : cerateFile errorcode [%d]\n",GetLastError());
		return -1;
	}

	// get the message
	strcpy_s(buffer,"HELLO FROM CLIENT MAILSLOT");

	if((ret = WriteFile(hMail,buffer,strlen(buffer),&byteSuccess,NULL)) < 0)
	{
		printf("sorry : CreateMailSlot errorcode [%d]\n",GetLastError());

		// close mailslot
		CloseHandle(hMail);

		return -1;
	}

	return 0;
}
