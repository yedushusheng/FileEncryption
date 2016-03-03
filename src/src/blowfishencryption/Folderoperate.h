#pragma once
#include<afx.h>
#include"stdafx.h"
#include"run.h"
#include "MD5.h"
class Folderoperate
{
public:
	Folderoperate(void);
	~Folderoperate(void);
	CString openFloder();//打开文件函数
	int EncDencFolder(bool mark,const char *soursefile,const char *destfile,const char *pwd);//文件夹blowfish加密解密处理
	int EncDencDESFolder(bool mark,const char *soursefile,const char *destfile,const char *pwd1,const char *pwd2);//文件夹3DES加解密处理
	int EncDencDBFolder(bool mark,const char *soursefile,const char *destfile,const char *pwd1,const char *pwd2);//
public:
	char sourcefile1[MAX_PATH];
	char destfile1[MAX_PATH];
	char pwd1[MAX_PATH];
	char pwd2[MAX_PATH];
	run running1;
	MD5 md5folder;
	CString readmima;
	CString readmima1;
};

