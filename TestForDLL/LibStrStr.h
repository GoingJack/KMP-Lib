#pragma  once

#ifndef __LIBSTRSTR
#define __LIBSTRSTR

#define LIB_API __declspec(dllexport)



#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#define nullptr NULL


#define SuccessMatched		0	//�ɹ�ƥ��
#define NotFound			-1	//ƥ��ʧ��
#define ParameterError		-2	//��������
#define LengthError			-3	//����������
#define MallocError			-4  //next��������ռ�����

#define ALLSTRMAXFOUNDCOUNT	256 //ȫ���������������ֵĴ������������������������

typedef enum {
	OnceMatch = 1,
	AllMathch
}Optional;

//ÿ�δ���Ľṹ��
typedef struct {
	const char	*StrContent;		//���������ַ���ָ�롣
	const char	*KeyWord;			//���ݽ����Ĺؼ���ָ�롣

	/*�������ص�ֵ�����ڸ�����ṹ�帳ֵ*/
	//1
	int			Once_Position;		//OnceStrStr���
	//2
	int			*Position;			//AllStrStr�����
	int			KeyAppearCount;		//ÿ�ιؼ��ʳ��ֵ��ܴ���

}Result;

typedef struct {
	/*�û������ֵ*/
	const char	*StrContent;		//���������ַ���ָ�롣
	const char	*KeyWord;			//���ݽ����Ĺؼ���ָ�롣
	Optional	MyOptional;			//��ʾѡ��ѡ��OnceMatch����ʾֻƥ��һ��;AllMathch����ʾƥ�����С�

	Result		**My_Result;		//�������Ľṹ������
	int			KeyCount;			//�����ָ�֮��ؼ��ֵĸ���

}/*Parameter for QuickStrStr()*/PFQ;
//�����ַ����ָ�֮�������ȫ�������ٷ���
typedef struct
{
	/*Copy PFQ���û�����Ĵ�*/
	char	*KeyWord;			//���ݽ����Ĺؼ���ָ�롣

	/*����ѭ����������Key*/
	int			KeyWordsCount;		//�����û���������Keywords�����عؼ��ֵĸ���
	char		**AllKeyWords;		//�����˷ָ�֮����ַ���
}EveryKeyWords;



/*
����:	�ִ�ƥ���㷨��
����:	�ṹ��ָ�롣
����ֵ:	�ɹ�����SuccessMatched
*/
LIB_API int MainStrStr(PFQ *Information);

/*
����:	�ִ�ƥ���㷨->�ӹ���:ֻƥ��һ�ξͷ��ء�
����:	�ṹ��ָ�롣
����ֵ:	�ɹ�����SuccessMatched
*/
LIB_API int OnceStrStr(Result *Information);

/*
����:	�ִ�ƥ���㷨->�ӹ���:ƥ���������ַ���
����:	�ṹ��ָ�롣
����ֵ:	�ɹ�����SuccessMatched
*/
LIB_API int AllStrStr(Result *Information);

/*
����:	KMP�㷨:����KeyWord����next����
����:	�ṹ��ָ�롣
����ֵ:	�޷���ֵ��
*/
LIB_API void getNextArray(const char *match, int *next);

/*
����:	����ָ���ĸ�ʽ�ָ�ؼ����ַ���
����:	�ṹ��ָ��
����ֵ:	���طָ�õ��ַ���
*/
LIB_API char **SpiltKeyWords(EveryKeyWords *Information);

#endif
