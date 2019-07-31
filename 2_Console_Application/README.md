# Windows System programming interface (WIN-API)



1)	Write a simple MailSlot (IPC Mechanism) client and server application program using Win32 API.

2) 	Demonstrate the working of Named Pipe (IPC Mechanism) client and server application program using Win32 API. Create separate thread for IPC operation.

3)	Demonstrate the TCP socket client and server application using winsock library in windows platform.

4)	Demonstrate the UDP socket client and server application using winsock library in windows platform.

5)	Demonstrate the working of dynamic link library and exported functions in windows programming. Create a application that will use this library.

6)	Demonstrate virtual memory access and get system's memory information using windows API.


#### Note:
upon socket programming, please dont forget to include Ws2_32.lib into Project_property->Linker->Input->Additional Dependancies
or just add one line before main -> #pragma comment(lib, "ws2_32.lib")
