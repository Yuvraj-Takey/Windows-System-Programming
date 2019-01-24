/*
 *	Demonstrate the MailSlot IPC mechanism in windows
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [SERVER - Application]
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

	// get the mailSlot
	if((hMail = CreateMailslot(L"\\\\.\\mailslot\\mSlot",	// The name of the mailslot.
					0,							// The maximum size of a single message that can be written to the mailslot.
					MAILSLOT_WAIT_FOREVER,		// wait for message to be written to the mailslot before time-out
					NULL)) < 0)					// SECURITY level
	{
		printf("sorry : CreateMailSlot errorcode [%d]\n",GetLastError());
		return -1;
	}

	// message
	printf("Waiting for MailSlot message\n");

	// read the mesage from MailSlot
	if((ret = ReadFile(hMail,buffer,MAXBUFF,&byteSuccess,NULL)) < 0)
	{
		printf("sorry : ReadFile errorcode [%d]\n",GetLastError());

		// close mailslot
		CloseHandle(hMail);
		return -1;
	}

	// message
	printf("Message in mailslot [%s] \n",buffer);

	// close mailslot
	CloseHandle(hMail);

	return 0;
}
