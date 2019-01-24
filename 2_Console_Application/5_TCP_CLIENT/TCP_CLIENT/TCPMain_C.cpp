/*
 *	Demonstrate the TCP socket appliction using winsock library on windows platform
 *
 *
 *	@Auther	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [CLIENT - Application]
 */


#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#define MAXBUFF 100

int main()
{
	WSADATA WSAData;
	SOCKET sock_fd;
	SOCKADDR_IN addr;
	int addr_len = 0, ret = 0;
	char buffer[MAXBUFF]  = {"\0"};

	// entry for Socket 
	WSAStartup(MAKEWORD(2,2),&WSAData);

	// get the socket connection	
	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
	{
		printf("sorry : socket errorcode [%d]\n",GetLastError());
		return -1;
	}

	// get the sockaddr_in structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// get the size of structure
	addr_len = sizeof(addr);

	// The connect function establishes a connection to a specified socket.
	if((ret = connect(sock_fd,(sockaddr *)&addr,addr_len)) < 0)
	{
		printf("sorry : connect errorcode [%d]\n",GetLastError());
		
		// close the socket conncetion
		closesocket(sock_fd);
		return -1;
	}

	// The recv function receives data from a connected socket or a bound connectionless socket.
	if((ret = recv(sock_fd,buffer,MAXBUFF,0)) < 0)
	{
		printf("sorry : recv errorcode [%d]\n",GetLastError());
		
		// close the socket conncetion
		closesocket(sock_fd);
		return -1;
	}

	// message
	printf("Message from server - [%s]\n",buffer);

	// close the socket conncetion
	closesocket(sock_fd);
	WSACleanup();
	return 0;
}
