#define  _CRT_SECURE_NO_WARNINGS 
#define CRTDBG_MAP_ALLOC    
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
#define nullptr NULL
#include "LibStrStr.h"
#include <crtdbg.h>



#pragma comment(lib,"LibStrStr.lib")
void use_lib(const char *StrContent, const char *KeyWord, Optional your_op)
{
	PFQ PTest;
	PTest.KeyWord = /*"123|567|789|iii"*/KeyWord;
	PTest.StrContent = /*"123123124324123hfj789ahuiou56712o377812973123789"*/StrContent;
	Optional o1 = your_op;
	PTest.MyOptional = o1;

	MainStrStr(&PTest);
	if (o1 == AllMathch)
	{
		for (int i = 0; i < PTest.KeyCount; i++)
		{
			//printf("关键字%s的出现的次数为%d\n", PTest.My_Result[i]->KeyWord, PTest.My_Result[i]->KeyAppearCount);
			for (int j = 0; j < PTest.My_Result[i]->KeyAppearCount; j++)
			{
				//printf("%d ", PTest.My_Result[i]->Position[j]);
			}
			//printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < PTest.KeyCount; i++)
		{
			printf("关键字%s的出现的次数为%d\n", PTest.My_Result[i]->KeyWord, PTest.My_Result[i]->KeyAppearCount);
			if(PTest.My_Result[i]->KeyAppearCount != -1)
				printf("%d ", PTest.My_Result[i]->Once_Position);
			printf("\n");
		}
	}
	DeleteAllMem(&PTest);
	//_CrtDumpMemoryLeaks();
}
void read_file_and_use_fun()
{
	FILE *fp = fopen("string.txt", "r");
	char strcontent[10000] = { 0 };
	fread(strcontent, 1, 10000, fp);
	Optional my_op = OnceMatch;
	//use_lib(strcontent, "秘密|we|me", AllMathch);
	for (int i = 0; i < 100; i++)
	{
		use_lib(strcontent, "秘密|we|me", AllMathch);
	}
	/*EveryKeyWords pE;
	pE.KeyWord = "123|567|890";
	SpiltKeyWords(&pE);
	for (int i = 0; i < pE.KeyWordsCount; i++)
	{
		printf("%s\n", pE.AllKeyWords[i]);
	}*/
	fclose(fp);
}
int main()
{
	read_file_and_use_fun();
	printf("hello...\n");
	system("pause");
	return 0;
}