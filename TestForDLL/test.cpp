#include "LibStrStr.h"

typedef struct {
	char *name;
	int bb;
	double p;
	int arr[256];

}MyStr;
typedef enum {
	Mon = 1,
	T,
	W
}WeekDay;
char **splitWords(const char *KeyWords)
{
	char **res = (char **)malloc(sizeof(char *));//�����ַ����Ķ���ָ��
	if (res == nullptr)
	{
		return nullptr;
	}

	//����KeyWords,�ָ��ַ���ʱ����
	char *TmpKeyWords = (char *)malloc(sizeof(strlen(KeyWords)));
	if (TmpKeyWords == NULL)
	{
		return nullptr;
	}
	strcpy(TmpKeyWords, KeyWords);
	//ͳ�Ʒ��ŵĸ���
	int CCount = 0;
	while (*KeyWords != '\0')
	{
		KeyWords++;
		if (*KeyWords == '|')
			CCount++;
	}
	//����ռ�
	int i = 0;//
	for (i = 0; i < CCount + 1; i++)
	{
		res[i] = (char*)malloc(sizeof(char));//����̶���С�Ŀռ䣬���ƹؼ��ֵ��ֽ������ܳ���256.
		if (res[i] == nullptr)
		{
			return nullptr;
		}
	}
	char *Findc = nullptr;
	Findc = strtok(TmpKeyWords, "|");
	i = 0;
	do 
	{
		strcpy(res[i], Findc);
		Findc = strtok(NULL, "|");
		i++;
	} while (Findc!=NULL);
	return NULL;
	free(TmpKeyWords);
	TmpKeyWords = nullptr;
}
int main()
{
	char str[123] = { "123|456|789" };
	char **uuu = splitWords(str);


	
	
	
	MyStr *test = (MyStr*)malloc(sizeof(MyStr));
 	memset(test->arr, 0, sizeof(test->arr));
	int b = sizeof(test->arr);



	PFQ Text;
	/*Text.StrContent = "12312312312����13213123����12313123����1j3123123123123����";
	Text.KeyWord = "����";*/
	Text.StrContent = "aaaaaaaaaaaaaaaab";
	Text.KeyWord	= "aaaab";
	int a = 0;
	Text.KeyAppearCount = &a;
	Optional o1 = OnceMatch;
	Optional o2 = AllMathch;
	Text.MyOptional = o1;
	QuickStrStr(&Text);

	
}