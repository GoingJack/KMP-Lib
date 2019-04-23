#pragma  once

#ifndef __LIBSTRSTR
#define __LIBSTRSTR

#define LIB_API __declspec(dllexport)



#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#define nullptr NULL


#define SuccessMatched		0	//成功匹配
#define NotFound			-1	//匹配失败
#define ParameterError		-2	//参数错误
#define LengthError			-3	//串长度问题
#define MallocError			-4  //next数组申请空间问题

#define ALLSTRMAXFOUNDCOUNT	256 //全部搜索限制最大出现的次数，超过这个次数不做处理

typedef enum {
	OnceMatch = 1,
	AllMathch
}Optional;

//每次处理的结构体
typedef struct {
	const char	*StrContent;		//传进来的字符串指针。
	const char	*KeyWord;			//传递进来的关键字指针。

	/*程序处理返回的值：用于给结果结构体赋值*/
	//1
	int			Once_Position;		//OnceStrStr结果
	//2
	int			*Position;			//AllStrStr结果。
	int			KeyAppearCount;		//每次关键词出现的总次数

}Result;

typedef struct {
	/*用户输入的值*/
	const char	*StrContent;		//传进来的字符串指针。
	const char	*KeyWord;			//传递进来的关键字指针。
	Optional	MyOptional;			//表示选择选项OnceMatch：表示只匹配一次;AllMathch：表示匹配所有。

	Result		**My_Result;		//保存结果的结构体数组
	int			KeyCount;			//经过分割之后关键字的个数

}/*Parameter for QuickStrStr()*/PFQ;
//根据字符串分割之后再完成全部工作再返回
typedef struct
{
	/*Copy PFQ中用户输入的串*/
	char	*KeyWord;			//传递进来的关键字指针。

	/*用于循环处理所有Key*/
	int			KeyWordsCount;		//根据用户传进来的Keywords串返回关键字的个数
	char		**AllKeyWords;		//保存了分割之后的字符串
}EveryKeyWords;



/*
功能:	字串匹配算法。
参数:	结构体指针。
返回值:	成功返回SuccessMatched
*/
LIB_API int MainStrStr(PFQ *Information);

/*
功能:	字串匹配算法->子功能:只匹配一次就返回。
参数:	结构体指针。
返回值:	成功返回SuccessMatched
*/
LIB_API int OnceStrStr(Result *Information);

/*
功能:	字串匹配算法->子功能:匹配完所有字符。
参数:	结构体指针。
返回值:	成功返回SuccessMatched
*/
LIB_API int AllStrStr(Result *Information);

/*
功能:	KMP算法:根据KeyWord求其next数组
参数:	结构体指针。
返回值:	无返回值。
*/
LIB_API void getNextArray(const char *match, int *next);

/*
功能:	根据指定的格式分割关键字字符串
参数:	结构体指针
返回值:	返回分割好的字符串
*/
LIB_API char **SpiltKeyWords(EveryKeyWords *Information);

#endif
