#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
void main1()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |  _CRTDBG_LEAK_CHECK_DF);
	char *p = new char[30];
	char *p1 = (char *)malloc(sizeof(char) * 10);
	//free(p1);
	delete[]p;
	printf("hello...\n");
	_CrtDumpMemoryLeaks();
	return ;
}