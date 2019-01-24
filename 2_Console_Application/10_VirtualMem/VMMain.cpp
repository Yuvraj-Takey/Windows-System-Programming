/*
 *	The windows API for using virtual memory access and get system's memory information
 *
 *	@Author	- Yuvraj Takey
 *		  yuvraj.takey@gmail.com
 *	@Title	- Windows_System_Programming
 */

#include <stdio.h>
#include <windows.h>

int main()
{
	LPVOID vAlloc;
	MEMORY_BASIC_INFORMATION pBasic;

	// SYSTEM_INFO : Contains information about the current computer system.
	//This includes the architecture and type of the processor, the number of processors in the system
	SYSTEM_INFO sInfo;

	//MEMORYSTATUS : Contains information about the current state of both physical and virtual memory
	MEMORYSTATUS mStat;

	// get information about host
	GetSystemInfo(&sInfo);

	// Retrieves information about the system's current usage of both physical and virtual memory
	GlobalMemoryStatus(&mStat);

	printf("Page Size : %d\n", sInfo.dwPageSize);
	printf("Avail Virtual Mem : %d\n",mStat.dwAvailVirtual);

	// Reserves, commits, or changes the state of a region of pages in the virtual address space of the calling process
	vAlloc = VirtualAlloc(NULL,				// The starting address of the region to allocate
				4096,				// The size of the region, in bytes.
				MEM_COMMIT|MEM_RESERVE,		// The type of memory allocation
				PAGE_READWRITE);		// The memory protection for the region of pages to be allocated.

	if(vAlloc == NULL)
	{
		printf("sorry : VirtualAlloc errocode [%d]\n",GetLastError());
		return -1;
	}

	// Retrieves information about a range of pages in the virtual address space of the calling process.
	if((VirtualQuery(vAlloc,&pBasic,sizeof(pBasic))) < 0)
	{
		printf("sorry : VirtualAlloc errocode [%d]\n",GetLastError());
		
		// Releases, decommits, or releases and decommits a region
		//of pages within the virtual address space of the calling process.
		VirtualFree(vAlloc,5*4096,MEM_RELEASE);
		return -1;
	}
	else
	{
		printf("The Virtual region size : %d\n",pBasic.RegionSize);
	}


	// Releases, decommits, or releases and decommits a region
	//of pages within the virtual address space of the calling process.
	VirtualFree(vAlloc,5*4096,MEM_RELEASE);
	
	return 0;
}
