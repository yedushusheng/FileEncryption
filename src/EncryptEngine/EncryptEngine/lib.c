#include "lib.h"
#include "ctx.h"



NTSTATUS
File_EncryptBuffer(
    __in PVOID buffer,
    __in ULONG Length,
    __in PCHAR PassWord,
    __inout PUSHORT CryptIndex,
    __in ULONG ByteOffset
    )
{
    PCHAR buf;
    UINT64 i;

    UNREFERENCED_PARAMETER(PassWord);

    buf = (PCHAR)buffer;

    //if (NULL != CryptIndex)
    //{
        //if (*CryptIndex == CRYPT_INDEX_BIT)
        //{
            for(i=0;i<Length;i++)
            {
                buf[i] ^= ENC_BUFF_KEY_BIT;
            }
       // } else {
            //其他加密算法
       // }
    //}
    
    return STATUS_SUCCESS;
}

NTSTATUS
File_DecryptBuffer(
    __in PVOID buffer,
    __in ULONG Length,
    __in PCHAR PassWord,
    __inout PUSHORT CryptIndex,
    __in ULONG ByteOffset
)
{
    PCHAR buf;
    UINT64 i;

    UNREFERENCED_PARAMETER(PassWord);

    buf = (PCHAR)buffer;

    //if (NULL != CryptIndex)
    //{
        //if (*CryptIndex == CRYPT_INDEX_BIT)
        //{
            for(i=0;i<Length;i++)
            {
                buf[i] ^= ENC_BUFF_KEY_BIT;
            }
       // } else {
            //其他加密算法
       // }
    //}
    
    return STATUS_SUCCESS;
}

