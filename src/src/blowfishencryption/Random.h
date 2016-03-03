//random.h∂®“Â
#include"resource.h"
#include "stdafx.h"
#include "afxdialogex.h"

#include <ctime>

const int LEN_NAME = 16;
#define KEYFILE_NAME "KEY.txt"
char zhifubiao[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

class CRandom{
 
public:
	 char *rand_str(char *str, const int len);
};

char* CRandom::rand_str(char *str, const int len)
{   
	int i;
	for(i = 0;i < len; ++i) {
		str[i]=*(&zhifubiao[0]+rand()%62);
	}
	str[++i]='\0';
	return str;
}