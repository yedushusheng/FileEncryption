#include "StdAfx.h"
#include "EncryptionInterface.h"


EncryptionInterface::EncryptionInterface(const char *pwd)
{   
	if ((!pwd) ) throw "Invalid processing constructor params.";
	strncpy(_encryptionKey, pwd, 99);
   _encryptionKey[99] = 0; //strncpy可以将一字符串的一部分拷贝到另一个字符串中
}


EncryptionInterface::~EncryptionInterface()
{
	ZeroMemory(_encryptionKey, 100);
}
