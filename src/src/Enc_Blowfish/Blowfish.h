
// _THE BlowFishEnc ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger
// Updated to support FileEncryption Utility by Nir Dremer, 9/02
//#include "stdafx.h"
//#include"resource.h"

#pragma once
#include "../blowfishencryption/stdafx.h"
#include "../blowfishencryption/EncryptionInterface.h"
//#include "EncryptionInterface.h"
class BlowFishEnc : public EncryptionInterface
{
public:
	 BlowFishEnc(const char *pwd);
	~BlowFishEnc();

	 DWORD encryptStream(const char *plain, const DWORD size, char *cipher);
	DWORD decryptStream(const char *cipher, const DWORD size, char *plain);

private:
	DWORD	GetOutputLength(DWORD lInputLong);

	DWORD 	*PArray;
	DWORD	(*SBoxes)[256];
	void 	BlowFishEnc_encipher(DWORD *xl, DWORD *xr);
	void 	BlowFishEnc_decipher(DWORD *xl, DWORD *xr);
};

union aword {
	DWORD dword;
	BYTE byte [4];
	struct {             //位域的定义和位域变量的说明位域定义与结构定义相仿
	unsigned int byte3:8;//其中位域列表的形式为： 类型说明符 位域名：位域长度 
	unsigned int byte2:8;
	unsigned int byte1:8;
	unsigned int byte0:8;
	} w;
};
