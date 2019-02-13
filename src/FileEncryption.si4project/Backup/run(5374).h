#pragma once
#include "../yxyDES2/yxyDES2.h"
class run
{
public:
	run(void);
	~run(void);
	void processing(bool mark,const char *source, const char *dest, const char *pwd);//blowfish加解密处理
	void clearing(const char *clearfile);//删除源文件
	void writemimatofile(const char *mifilename, const char* pwd);//向密文中写入密码
	CString readmimafromfile(const char *mifilename);//读取密文中的密码
	CString readmima1fromfile(const char *mifilename,int lenght);//读取密文中的密码1
	void rebackencfile(const char *mifilename,int len);//还原密文
	void filldes(const char *mifilename,int len);//3DES填充
	int readfill(const char *mingfilename);//读取填充位数
	void desprocess(bool mark,const char *source, const char *dest, const char *pwd1,const char *pwd2);//3DES加解密处理
public:
	char _readFile[MAX_PATH];
	char _writeFile[MAX_PATH];
    char _password[100];
	
    char _password1[100];
	char _password2[100];
	yxyDES2 DES;

};

