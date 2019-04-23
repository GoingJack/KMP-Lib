#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define nullptr NULL
#include "LibStrStr.h"


#pragma comment(lib,"LibStrStr.lib")

int main()
{
	PFQ PTest;
	PTest.KeyWord = "123|567|789|iii";
	PTest.StrContent = "123123124324123hfj789ahuiou56712o377812973123789";
	Optional o1 = AllMathch;
	PTest.MyOptional = o1;
	
	MainStrStr(&PTest);
	for (int i = 0; i < PTest.KeyCount; i++)
	{
		printf("关键字%s的出现的次数为%d\n", PTest.My_Result[i]->KeyWord, PTest.My_Result[i]->KeyAppearCount);
		for (int j = 0; j < PTest.My_Result[i]->KeyAppearCount; j++)
		{
			printf("%d ", PTest.My_Result[i]->Position[j]);
		}
		printf("\n");
	}
	/*EveryKeyWords pE;
	pE.KeyWord = "123|567|890";
	SpiltKeyWords(&pE);
	for (int i = 0; i < pE.KeyWordsCount; i++)
	{
		printf("%s\n", pE.AllKeyWords[i]);
	}*/
	printf("hello...\n");
	system("pause");
	return 0;
}