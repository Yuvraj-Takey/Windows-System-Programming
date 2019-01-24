
/*
 *	Demonstrate the TCP socket appliction using winsock library on windows platform
 *
 *
 *	@Auther	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [SERVER - Application]
 */


#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#define MAXBUFF 100

int main()
{
	WSADATA WSAData;
	SOCKET sock_fd, ses_fd;
	sockaddr_in addr, addr_cl;
	int addr_len = 0, addr_len_cl = sizeof(addr_cl), ret = 0;
	char buffer[MAXBUFF] = {"\0"};

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

	// bind the name with socket
	if((ret = bind(sock_fd,(sockaddr *)&addr,addr_len)) == SOCKET_ERROR)
	{
		printf("sorry : bind errorcode [%d]\n",GetLastError());
		
		// close the socket conncetion
		closesocket(sock_fd);
		return -1;
	}

	// a socket in a state in which it is listening for an incoming connection.
	if((ret = listen(sock_fd,10)) < SOCKET_ERROR )
	{
		printf("sorry : bind errorcode [%d]\n",GetLastError());
		
		// close the socket conncetion
		closesocket(sock_fd);
		return -1;
	}

	// run the server
	printf("Server is running..\n");

	while(1)
	{
		// The accept function permits an incoming connection attempt on a socket.
		ses_fd = accept(sock_fd,(sockaddr *)&addr_cl,&addr_len_cl);

		strcpy_s(buffer,"HELLO FROM SERVER");

		// the send function sends data on a connected socket.
		if((ret = send(ses_fd,buffer,strlen(buffer),0)) < 0)
		{
			printf("sorry : bind errorcode [%d]\n",GetLastError());
			return -1;
		}

		// message
		printf("Done : message is successfully send to client\n");

		// close the socket connection
		closesocket(ses_fd);
	}

	// close the socket connection
	closesocket(sock_fd);
	WSACleanup();

	return 0;
}
