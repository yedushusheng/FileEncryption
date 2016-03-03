#ifndef _LIB_H_
#define _LIB_H_

#include "common.h"

//异或加密
#define CRYPT_INDEX_BIT 1
#define CRYPT_FUNC_INDEX sizeof(UCHAR)
#define ENC_BUFF_KEY_BIT 0x77



VOID
Cc_ClearFileCache1 (
					__inout PFLT_CALLBACK_DATA Data,
					__in PCFLT_RELATED_OBJECTS FltObjects,
					__deref_out_opt PVOID *CompletionContext
					
					);



/**
 * 加密缓存内容
 *buffer:指向缓存的指针
 *Length:缓存长度
 *PassWord:密码，目前未使用
 *CryptIndex:加密解密算法索引号
 */
NTSTATUS
File_EncryptBuffer(
    __in PVOID buffer,
    __in ULONG Length,
    __in PCHAR PassWord,
    __inout PUSHORT CryptIndex,
    __in ULONG ByteOffset
);

/**
 * 解密缓存内容
  *buffer:指向缓存的指针
 *Length:缓存长度
 *PassWord:密码，目前未使用
 *CryptIndex:加密解密算法索引号
 */
NTSTATUS
File_DecryptBuffer(
    __in PVOID buffer,
    __in ULONG Length,
    __in PCHAR PassWord,
    __inout PUSHORT CryptIndex,
    __in ULONG ByteOffset
);




#endif