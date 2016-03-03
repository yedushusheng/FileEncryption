#include "../blowfishencryption/StdAfx.h"
// _THE BlowFishEnc ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger
// Updated to support FileEncryption Utility by Nir Dremer, 9/02
//#include "StdAfx.h"
#include <afxwin.h>
#include "BlowFish.h"
#include "Sboxs.h"	// holds the random digit tables随机数字表
#include "../blowfishencryption/EncryptionInterface.h"
#define S(x,i)(SBoxes[i][x.w.byte##i])//＃＃表示变量名称的连接,表示SBoxes字符串数组中的一个32位的字符串 
#define bf_F(x)(((S(x,0) + S(x,1)) ^ S(x,2)) + S(x,3))//blowfish算法中的F(xL)函数，对待加密信息的计算
#define ROUND(a,b,n)(a.dword ^= bf_F(b) ^ PArray[n])

BlowFishEnc::BlowFishEnc(const char *pwd) : EncryptionInterface(pwd)
{
  
	
 	PArray = new DWORD[18];//dword4个字节32位
 	SBoxes = new DWORD[4][256];

	int			i, j;
	DWORD		data, datal, datar;
	union aword	temp;//aword是联合的名，temp是联合的变量

	int keyLen = (int)strlen(_encryptionKey);//strlen返回的是一个无符号类型,在表达式中使用无符号数可能导致不可预料的结果，把strlen强制转换成int可以解决这个问题

	// first fill arrays from data tables首先从数据表中获得数据填充数组
	for(i = 0; i < 18; i++)
		PArray[i] = bf_P[i];//用bf_P给PArray赋值

	for(i = 0; i < 4; i++)
	{
	 	for(j = 0; j < 256; j++)
	 		SBoxes[i][j] = bf_S[i][j];//用bf_S给SBoxes赋值
	}

	j = 0;
	for(i = 0; i < NPASS + 2; ++i)       //给联合中的成员赋值，NPASS=16，
	{
		temp.dword = 0;
		temp.w.byte0 = _encryptionKey[j];
		temp.w.byte1 = _encryptionKey[(j+1) % keyLen];
		temp.w.byte2 = _encryptionKey[(j+2) % keyLen];
		temp.w.byte3 = _encryptionKey[(j+3) % keyLen];
		data = temp.dword;
		PArray[i] ^= data;//给PArray中的内容取反
		j = (j + 4) % keyLen;
	}

	datal = 0;
	datar = 0;

	for(i = 0; i < NPASS + 2; i += 2)
	{
		BlowFishEnc_encipher(&datal, &datar);
		PArray[i] = datal;
		PArray[i + 1] = datar;
	}

	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 256; j += 2)
		{
		  BlowFishEnc_encipher(&datal, &datar);
		  SBoxes[i][j] = datal;
		  SBoxes[i][j + 1] = datar;
		}
	}
}

BlowFishEnc::~BlowFishEnc()
{
	delete PArray;
	delete[] SBoxes;
}

// Encode pIntput into pOutput.  Input length in lSize.  Returned value
// is length of output which will be even MOD 8 bytes.  Input buffer and
// output buffer can be the same, but be sure buffer length is even MOD8.
DWORD BlowFishEnc::encryptStream(const char *plain, const DWORD size, char *cipher)//cipher:密码。
{
	if (plain != cipher)
		memcpy(cipher, plain, size);//从源plain所指的内存地址的起始位置开始拷贝size个字节到目标cipher所指的内存地址的起始位置中
	
	DWORD lOutSize = GetOutputLength(size);
	for(DWORD lCount = 0; lCount < lOutSize; lCount += 8)
	{
		// if padding is required.如果填充是必要的，即输入字节数不是8的倍数
		if (lCount + 8 > size)
		{
			// point at byte past the end of actual data
			char *po = (char*)cipher + (size - lCount);
			// padding with 255 (FF) characters.
			for(DWORD i = 0; i < (lOutSize - size); i++)
				*po++ = (char)0;
		}
		BlowFishEnc_encipher((DWORD*)cipher, (DWORD*)(cipher + 4));
		cipher += 8;
	}
	
	return lOutSize;
}

// Decode pIntput into pOutput.  Input length in lSize.  Input buffer and
// output buffer can be the same, but be sure buffer length is even MOD8.
DWORD BlowFishEnc::decryptStream(const char *cipher, const DWORD size, char *plain)
{
	if (plain != cipher)
		memcpy(plain, cipher, size);

	for (DWORD lCount = 0; lCount < size; lCount += 8)
	{
	 	BlowFishEnc_decipher((DWORD*)plain, (DWORD*)(plain + 4));
		plain += 8;
	}
	
	return size;
}

// the low level(private) encryption function 低水平(私人)加密功能
void BlowFishEnc::BlowFishEnc_encipher(DWORD *xl, DWORD *xr)
{
	union aword  Xl, Xr;

	Xl.dword = *xl;
	Xr.dword = *xr;

	Xl.dword ^= PArray[0];
	ROUND(Xr, Xl, 1);
	ROUND(Xl, Xr, 2);
	ROUND(Xr, Xl, 3);
	ROUND(Xl, Xr, 4);
	ROUND(Xr, Xl, 5);
	ROUND(Xl, Xr, 6);
	ROUND(Xr, Xl, 7);
	ROUND(Xl, Xr, 8);
	ROUND(Xr, Xl, 9);
	ROUND(Xl, Xr, 10);
	ROUND(Xr, Xl, 11);
	ROUND(Xl, Xr, 12);
	ROUND(Xr, Xl, 13);
	ROUND(Xl, Xr, 14);
	ROUND(Xr, Xl, 15);
	ROUND(Xl, Xr, 16);
	Xr.dword ^= PArray[17];

	*xr = Xl.dword;
	*xl = Xr.dword;
}

// the low level(private) decryption function
void BlowFishEnc::BlowFishEnc_decipher(DWORD *xl, DWORD *xr)
{
   union aword  Xl;
   union aword  Xr;

   Xl.dword = *xl;
   Xr.dword = *xr;

   Xl.dword ^= PArray[17];
   ROUND(Xr, Xl, 16);
   ROUND(Xl, Xr, 15);
   ROUND(Xr, Xl, 14);
   ROUND(Xl, Xr, 13);
   ROUND(Xr, Xl, 12);
   ROUND(Xl, Xr, 11);
   ROUND(Xr, Xl, 10);
   ROUND(Xl, Xr, 9);
   ROUND(Xr, Xl, 8);
   ROUND(Xl, Xr, 7);
   ROUND(Xr, Xl, 6);
   ROUND(Xl, Xr, 5);
   ROUND(Xr, Xl, 4);
   ROUND(Xl, Xr, 3);
   ROUND(Xr, Xl, 2);
   ROUND(Xl, Xr, 1);
   Xr.dword ^= PArray[0];

   *xl = Xr.dword;
   *xr = Xl.dword;
}

// get output length, which must be even MOD 8保证输入输出的字节数是8的倍数
DWORD BlowFishEnc::GetOutputLength(DWORD lInputLong)
{
	DWORD 	lVal;

	lVal = lInputLong % 8;	// find out if uneven number of bytes at the end
	if(lVal != 0)
		return lInputLong + 8 - lVal;
	else
		return lInputLong;
}