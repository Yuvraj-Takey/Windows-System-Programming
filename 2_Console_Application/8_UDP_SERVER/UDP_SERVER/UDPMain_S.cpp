/*
 *	Demostrate the UDP socket appliction using winsock library on windows platform
 *
 *
 *	@Auther	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming [SERVER - Application]
 */

#include <stdio.h>
#include <windows.h>
#include <winsock.h>

#define MAXBUFF	100

int main()
{
	WSADATA WSAData;
	SOCKET sock_fd;
	sockaddr_in addr, addr_c;
	int add_len = 0, add_len_c = sizeof(addr_c), ret = 0;
	char buffer[MAXBUFF] = {"\0"};

	WSAStartup(MAKEWORD(2,2), &WSAData);

	// Establish the socket connection
	if((sock_fd = socket(AF_INET,SOCK_DGRAM, 0)) < 0)
	{
		printf("sorry : socket errorcode [%d]\n",GetLastError());

		// close the socket connection
		closesocket(sock_fd);
		return -1;
	}

	// fill the sockadd structure
	addr.sin_family = AF_INET;
	addr.sin_port = 2002;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// get the structure length
	add_len = sizeof(addr);

	// The bind function associates a local address with a socket.
	if((ret = bind(sock_fd,(sockaddr *) &addr,add_len)) < 0)
	{
		printf("sorry : bind errorcode [%d]\n",GetLastError());

		// close the socket connection
		closesocket(sock_fd);
		return -1;
	}

	// start the server
	printf("Server is Running..\n");

	while(1)
	{
		// The recvfrom function receives a datagram and stores the source address.
		if((ret = recvfrom(sock_fd,buffer,MAXBUFF,0,(sockaddr*)&addr_c,&add_len_c)) < 0)
		{
			printf("sorry : recvfrom errorcode [%d]\n",GetLastError());
			break;
		}

		// message
		printf("message from client [%s]\n",buffer);

		// set the buffer
		memset(buffer,0,MAXBUFF);

		// fill the buffer
		strcpy_s(buffer,"HELLO FROM SERVER");

		// send the message to client
		if((ret = sendto(sock_fd,buffer,strlen(buffer),0,(sockaddr *)&addr_c,add_len_c)) < 0)
		{
			printf("sorry : sendto errorcode [%d]\n",GetLastError());
			break;
		}

		printf("Done : message is passed to client\n");

	}

	// close the socket connection
	closesocket(sock_fd);
	WSACleanup();

	return 0;
}
