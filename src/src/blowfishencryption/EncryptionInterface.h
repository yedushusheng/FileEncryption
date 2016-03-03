#pragma once
#include <windows.h>
class EncryptionInterface
{
public:
	EncryptionInterface(const char *pwd);
	~EncryptionInterface();
	virtual DWORD encryptStream(const char *plain, const DWORD size, char *cipher) = 0;
	virtual DWORD decryptStream(const char *cipher, const DWORD size, char *plain) = 0;
protected:
	char _encryptionKey[100];
};

