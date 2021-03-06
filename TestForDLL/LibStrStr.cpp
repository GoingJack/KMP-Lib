// LibStrStr.cpp : 定义 DLL 应用程序的导出函数。
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibStrStr.h"

LIB_API int MainStrStr(PFQ * Information)
{
	if (Information == nullptr || Information->KeyWord == nullptr || Information->StrContent == nullptr)
	{
		return ParameterError;
	}
	if (strlen(Information->StrContent) < 1 || strlen(Information->StrContent) < strlen(Information->KeyWord))
	{
		return LengthError;
	}
	EveryKeyWords *My_KeyWords = (EveryKeyWords *)malloc(sizeof(EveryKeyWords));
	if (My_KeyWords == nullptr)
	{
		return MallocError;
	}
	Optional o1 = OnceMatch;
	Optional o2 = AllMathch;

	My_KeyWords->KeyWord = (char *)malloc(sizeof(char)*strlen(Information->KeyWord) + 1);
	strcpy(My_KeyWords->KeyWord, Information->KeyWord);

	SpiltKeyWords(My_KeyWords);//先把特殊字符串分割
	//根据关键字的个数，确定结构体数组的个数
	Information->My_Result = (Result**)malloc(sizeof(Result*)*My_KeyWords->KeyWordsCount);

	//
	Information->KeyCount = My_KeyWords->KeyWordsCount;//把Key的个数传给用户
	for (int i = 0; i < My_KeyWords->KeyWordsCount; i++)
	{
		Information->My_Result[i] = (Result*)malloc(sizeof(Result));
		memset(Information->My_Result[i], 0, sizeof(Result));

		Information->My_Result[i]->StrContent = Information->StrContent;

		Information->My_Result[i]->KeyWord = (char *)malloc(strlen(My_KeyWords->AllKeyWords[i])+1);
		strcpy(Information->My_Result[i]->KeyWord, My_KeyWords->AllKeyWords[i]);
		//Information->My_Result[i]->KeyWord = My_KeyWords->AllKeyWords[i];


		Information->My_Result[i]->KeyAppearCount = 0;
		//memset(My_Result[i]->Postion, 0, sizeof(My_Result[i]->Postion));
		//实现功能
		if (Information->MyOptional == o1)
		{
			OnceStrStr(Information->My_Result[i]);
		}
		else if (Information->MyOptional == o2)
		{
			Information->My_Result[i]->Position = (int *)malloc(sizeof(int) * ALLSTRMAXFOUNDCOUNT);//限制最多可以查询的次数ALLSTRMAXFOUNDCOUNT
			AllStrStr(Information->My_Result[i]);
		}
	}
	//释放处理关键字字符串申请的控件
	if (My_KeyWords->KeyWord != nullptr)
	{
		free(My_KeyWords->KeyWord);
		My_KeyWords->KeyWord = nullptr;
	}
	for (int i = 0; i < My_KeyWords->KeyWordsCount; i++)
	{
		if (My_KeyWords->AllKeyWords[i] != nullptr)
		{
			free(My_KeyWords->AllKeyWords[i]);
			My_KeyWords->AllKeyWords[i] = nullptr;
		}
	}
	if (My_KeyWords->AllKeyWords != nullptr)
	{
		free(My_KeyWords->AllKeyWords);
		My_KeyWords->AllKeyWords = nullptr;
	}
	free(My_KeyWords);
	My_KeyWords = nullptr;
}
LIB_API int OnceStrStr(Result * Information)
{
	int sp = 0;
	int mp = 0;
	int *next = (int *)malloc(sizeof(int) * strlen(Information->KeyWord));
	if (next == nullptr)
	{
		printf("malloc error\n");
		return MallocError;
	}
	getNextArray(Information->KeyWord, next);
	while ((sp < (int)strlen(Information->StrContent)) && (mp < (int)strlen(Information->KeyWord)))
	{
		if (Information->StrContent[sp] == Information->KeyWord[mp])
		{
			sp++;
			mp++;
		}
		else if (next[mp] == -1)
		{
			sp++;
		}
		else
		{
			mp = next[mp];
		}
	}
	free(next);
	if (next != nullptr)
	{
		next = nullptr;
	}
	if (mp == strlen(Information->KeyWord))
	{
		Information->Once_Position = sp - mp;
		Information->KeyAppearCount++;
		return SuccessMatched;
	}
	else
	{
		Information->KeyAppearCount = -1;
		return NotFound;
	}
}

LIB_API int AllStrStr(Result * Information)
{
	int SaveKeyAppearCount		= 0;
	int OffsetNumber			= 0;
	int offsetAddress			= 0;
	const char *SaveStrContent	= Information->StrContent;
	memset(Information->Position, 0, ALLSTRMAXFOUNDCOUNT * sizeof(int));
	while (OnceStrStr(Information) == SuccessMatched)
	{
		//给当前本次查询的Position赋值为上次的offsetNumber + 本次Infomation->positions
		Information->Position[SaveKeyAppearCount] = OffsetNumber + Information->Once_Position;

		//下次偏移的地址数 等于本次找到的位置加上关键字的长度
		offsetAddress = strlen(Information->KeyWord) + Information->Once_Position;
		
		//下次偏移的位置必须的加上上次的offsetNumber
		OffsetNumber = Information->Position[Information->KeyAppearCount - 1] + strlen(Information->KeyWord);
		
		Information->StrContent += offsetAddress;
		if (SaveKeyAppearCount > ALLSTRMAXFOUNDCOUNT)break;

		//出现的次数加1
		SaveKeyAppearCount++;
	}
	if (SaveKeyAppearCount != 0)
	{
		Information->KeyAppearCount		= SaveKeyAppearCount;
		Information->StrContent			= SaveStrContent;
		return SuccessMatched;
	}
	else
	{
		return NotFound;
	}
}

LIB_API void getNextArray(const char * match, int *next)
{
	if (match == nullptr || next == nullptr)
		return;
	int length = strlen(match);
	if (length == 1)
	{
		next[0] = -1;
		return;
	}
	
	next[0] = -1;
	next[1] = 0;
	int pos = 2;//从下标2开始
	int cn = 0;//
	while (pos < length)
	{
		if (match[pos - 1] == match[cn])
		{
			next[pos++] = ++cn;
		}
		else if (cn > 0)
		{
			cn = next[cn];
		}
		else
		{
			next[pos++] = 0;
		}
	}
}

LIB_API void SpiltKeyWords(EveryKeyWords * Information)
{
	char **res = (char **)malloc(sizeof(char *) * 20);//返回字符串的二级指针 限制一次最多20的关键字
	if (res == nullptr)
	{
		return ;
	}
	char ArrKeyWords[256];
	strcpy(ArrKeyWords, Information->KeyWord);
	char *KeyWords = ArrKeyWords;
	KeyWords = strtok(KeyWords, "|");
	int i = 0;
	do
	{
		res[i] = (char *)malloc(strlen(KeyWords) + 1);
		strcpy(res[i], KeyWords);
		KeyWords = strtok(NULL, "|");
		i++;
	} while (KeyWords != NULL);
	Information->KeyWordsCount		= i;
	Information->AllKeyWords		= res;
}

LIB_API void DeleteAllMem(PFQ * Information)
{
	//typedef struct {
	//	/*用户输入的值*/
	//	const char	*StrContent;		//传进来的字符串指针。
	//	const char	*KeyWord;			//传递进来的关键字指针。
	//	Optional	MyOptional;			//表示选择选项OnceMatch：表示只匹配一次;AllMathch：表示匹配所有。

	//	Result		**My_Result;		//保存结果的结构体数组
	//	int			KeyCount;			//经过分割之后关键字的个数

	//}/*Parameter for QuickStrStr()*/PFQ;
	


	//typedef struct {
	//	const char	*StrContent;		//传进来的字符串指针。
	//	char	*KeyWord;			//传递进来的关键字指针。

	//	/*程序处理返回的值：用于给结果结构体赋值*/
	//	//1
	//	int			Once_Position;		//OnceStrStr结果
	//	//2
	//	int			*Position;			//AllStrStr结果。
	//	int			KeyAppearCount;		//每次关键词出现的总次数

	//}Result;
	for (int i = 0; i < Information->KeyCount; i++)
	{
		if (Information->My_Result[i]->KeyWord != nullptr)
		{
			free(Information->My_Result[i]->KeyWord);
			Information->My_Result[i]->KeyWord = nullptr;
		}
		if (Information->My_Result[i]->Position != nullptr)
		{
			free(Information->My_Result[i]->Position);
			Information->My_Result[i]->Position = nullptr;
		}
		if(Information->MyOptional == OnceMatch)
			continue;
		if (Information->My_Result[i]->Position != nullptr)
		{
			free(Information->My_Result[i]->Position);
			Information->My_Result[i]->Position = nullptr;
		}
		if (Information->My_Result[i] != nullptr)
		{
			free(Information->My_Result[i]);
			Information->My_Result[i] = nullptr;
		}
	}
	/*if (Information != nullptr)
	{
		free(Information);
		Information = nullptr;
	}*/
}
