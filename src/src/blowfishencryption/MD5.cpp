/*
 * RFC 1321 compliant MD5 implementation,
 * by Christophe Devine <devine@cr0.net>;
 * this program is licensed under the GPL.
 */
#include "StdAfx.h"
#include "MD5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include"string.h"
//此处“\”为延续符
#define GET_UINT32(n,b,i)                         \
{                                                  \
    (n) = (uint32) ((uint8 *) b)[(i)]               \
      | (((uint32) ((uint8 *) b)[(i)+1]) <<  8)      \
      | (((uint32) ((uint8 *) b)[(i)+2]) << 16)       \
      | (((uint32) ((uint8 *) b)[(i)+3]) << 24);       \
}

#define PUT_UINT32(n,b,i)                                   \
{                                                            \
    (((uint8 *) b)[(i)]  ) = (uint8) (((n)      ) & 0xFF);     \
    (((uint8 *) b)[(i)+1]) = (uint8) (((n) >>  8) & 0xFF);      \
    (((uint8 *) b)[(i)+2]) = (uint8) (((n) >> 16) & 0xFF);     \
    (((uint8 *) b)[(i)+3]) = (uint8) (((n) >> 24) & 0xFF);     \
}

//extern pthread_mutex_t mutexMemory;

void MD5::md5_starts( struct md5_context *ctx )
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;
    ctx->state[0] = 0x67452301;//4个32位的连接变量，有初始值
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}
//主循环有四轮，每轮很相似。每轮进行16次操作，
//每次操作对a、b、c、d四个变量中的三个作一次非线性函数运算，
//然后将所得结果加上第四个变量，消息的一个子分组和一个常数。
//再将所得结果向右环移一个不定的数，并加上a,b,c或d中之一。
//最后用该结果取代a,b,c或d中之一。
void MD5::md5_process( struct md5_context *ctx, uint8 data[64] )//data[64]明文分组，每组512位
{
    uint32 A, B, C, D, X[16];

    GET_UINT32( X[0],  data,  0 );
    GET_UINT32( X[1],  data,  4 );
    GET_UINT32( X[2],  data,  8 );
    GET_UINT32( X[3],  data, 12 );
    GET_UINT32( X[4],  data, 16 );
    GET_UINT32( X[5],  data, 20 );
    GET_UINT32( X[6],  data, 24 );
    GET_UINT32( X[7],  data, 28 );
    GET_UINT32( X[8],  data, 32 );
    GET_UINT32( X[9],  data, 36 );
    GET_UINT32( X[10], data, 40 );
    GET_UINT32( X[11], data, 44 );
    GET_UINT32( X[12], data, 48 );
    GET_UINT32( X[13], data, 52 );
    GET_UINT32( X[14], data, 56 );
    GET_UINT32( X[15], data, 60 );

#define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))

#define P(a,b,c,d,k,s,t)                                    \
{                                                            \
    a += F(b,c,d) + X[k] + t; a = S(a,s) + b;      \
}

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];

//round 1 
#define F(x,y,z) (z ^ (x & (y ^ z)))

    P( A, B, C, D,  0,  7, 0xD76AA478 );
    P( D, A, B, C,  1, 12, 0xE8C7B756 );
    P( C, D, A, B,  2, 17, 0x242070DB );
    P( B, C, D, A,  3, 22, 0xC1BDCEEE );
    P( A, B, C, D,  4,  7, 0xF57C0FAF );
    P( D, A, B, C,  5, 12, 0x4787C62A );
    P( C, D, A, B,  6, 17, 0xA8304613 );
    P( B, C, D, A,  7, 22, 0xFD469501 );
    P( A, B, C, D,  8,  7, 0x698098D8 );
    P( D, A, B, C,  9, 12, 0x8B44F7AF );
    P( C, D, A, B, 10, 17, 0xFFFF5BB1 );
    P( B, C, D, A, 11, 22, 0x895CD7BE );
    P( A, B, C, D, 12,  7, 0x6B901122 );
    P( D, A, B, C, 13, 12, 0xFD987193 );
    P( C, D, A, B, 14, 17, 0xA679438E );
    P( B, C, D, A, 15, 22, 0x49B40821 );

#undef F

	//round 2 
#define F(x,y,z) (y ^ (z & (x ^ y)))

    P( A, B, C, D,  1,  5, 0xF61E2562 );
    P( D, A, B, C,  6,  9, 0xC040B340 );
    P( C, D, A, B, 11, 14, 0x265E5A51 );
    P( B, C, D, A,  0, 20, 0xE9B6C7AA );
    P( A, B, C, D,  5,  5, 0xD62F105D );
    P( D, A, B, C, 10,  9, 0x02441453 );
    P( C, D, A, B, 15, 14, 0xD8A1E681 );
    P( B, C, D, A,  4, 20, 0xE7D3FBC8 );
    P( A, B, C, D,  9,  5, 0x21E1CDE6 );
    P( D, A, B, C, 14,  9, 0xC33707D6 );
    P( C, D, A, B,  3, 14, 0xF4D50D87 );
    P( B, C, D, A,  8, 20, 0x455A14ED );
    P( A, B, C, D, 13,  5, 0xA9E3E905 );
    P( D, A, B, C,  2,  9, 0xFCEFA3F8 );
    P( C, D, A, B,  7, 14, 0x676F02D9 );
    P( B, C, D, A, 12, 20, 0x8D2A4C8A );

#undef F
  
	//round 3
#define F(x,y,z) (x ^ y ^ z)

    P( A, B, C, D,  5,  4, 0xFFFA3942 );
    P( D, A, B, C,  8, 11, 0x8771F681 );
    P( C, D, A, B, 11, 16, 0x6D9D6122 );
    P( B, C, D, A, 14, 23, 0xFDE5380C );
    P( A, B, C, D,  1,  4, 0xA4BEEA44 );
    P( D, A, B, C,  4, 11, 0x4BDECFA9 );
    P( C, D, A, B,  7, 16, 0xF6BB4B60 );
    P( B, C, D, A, 10, 23, 0xBEBFBC70 );
    P( A, B, C, D, 13,  4, 0x289B7EC6 );
    P( D, A, B, C,  0, 11, 0xEAA127FA );
    P( C, D, A, B,  3, 16, 0xD4EF3085 );
    P( B, C, D, A,  6, 23, 0x04881D05 );
    P( A, B, C, D,  9,  4, 0xD9D4D039 );
    P( D, A, B, C, 12, 11, 0xE6DB99E5 );
    P( C, D, A, B, 15, 16, 0x1FA27CF8 );
    P( B, C, D, A,  2, 23, 0xC4AC5665 );

#undef F

	//round 4 
#define F(x,y,z) (y ^ (x | ~z))

    P( A, B, C, D,  0,  6, 0xF4292244 );
    P( D, A, B, C,  7, 10, 0x432AFF97 );
    P( C, D, A, B, 14, 15, 0xAB9423A7 );
    P( B, C, D, A,  5, 21, 0xFC93A039 );
    P( A, B, C, D, 12,  6, 0x655B59C3 );
    P( D, A, B, C,  3, 10, 0x8F0CCC92 );
    P( C, D, A, B, 10, 15, 0xFFEFF47D );
    P( B, C, D, A,  1, 21, 0x85845DD1 );
    P( A, B, C, D,  8,  6, 0x6FA87E4F );
    P( D, A, B, C, 15, 10, 0xFE2CE6E0 );
    P( C, D, A, B,  6, 15, 0xA3014314 );
    P( B, C, D, A, 13, 21, 0x4E0811A1 );
    P( A, B, C, D,  4,  6, 0xF7537E82 );
    P( D, A, B, C, 11, 10, 0xBD3AF235 );
    P( C, D, A, B,  2, 15, 0x2AD7D2BB );
    P( B, C, D, A,  9, 21, 0xEB86D391 );

#undef F

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
}

//add the number of  original input (the last 64bits)
//这主要是在字符串末尾追加64位的密钥
void MD5::md5_update( struct md5_context *ctx, uint8 *input, uint32 length )
{
    uint32 left, fill;

    if( ! length ) return;

    left = ( ctx->total[0] >> 3 ) & 0x3F;
    fill = 64 - left;

    ctx->total[0] += length <<  3;
    ctx->total[1] += length >> 29;

    ctx->total[0] &= 0xFFFFFFFF;
    ctx->total[1] += ctx->total[0] < length << 3;

    if( left && length >= fill )
    {
        memcpy( (void *) (ctx->buffer + left), (void *) input, fill );
        md5_process( ctx, ctx->buffer );
        length -= fill;
        input  += fill;
        left = 0;
    }

    while( length >= 64 )
    {
        md5_process( ctx, input );
        length -= 64;
        input  += 64;
    }

    if( length==0 )
    {
        memcpy( (void *) (ctx->buffer + left), (void *) input, length );
    }
}
// padding with 100000... to remain_ and add the 64bit original size of input 
//这句就是在字符串后面补充一个1，若干个0
static uint8 md5_padding[64] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void MD5::md5_finish( struct md5_context *ctx, uint8 digest[16] )
{
    uint32 last, padn;
    uint8 msglen[8];

    PUT_UINT32( ctx->total[0], msglen, 0 );
    PUT_UINT32( ctx->total[1], msglen, 4 );

    last = ( ctx->total[0] >> 3 ) & 0x3F;
    padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );

    md5_update( ctx, md5_padding, padn );
    md5_update( ctx, msglen, 8 );

    PUT_UINT32( ctx->state[0], digest,  0 );
    PUT_UINT32( ctx->state[1], digest,  4 );
    PUT_UINT32( ctx->state[2], digest,  8 );
    PUT_UINT32( ctx->state[3], digest, 12 );
}

void MD5::GenerateMD5(unsigned char* buffer,int bufferlen)
{
    struct md5_context context;
    md5_starts (&context);
    md5_update (&context, buffer, bufferlen);
    md5_finish (&context,(unsigned char*)m_data);
}

MD5::MD5()
{
    for(int i=0;i<4;i++)
        m_data[i]=0;
}

MD5::MD5(unsigned long* md5src)
{
    memcpy(m_data,md5src,16);
}
int _httoi(const char *value)
{
  struct CHexMap
  {
    char chr;
    int value;
  };
  const int HexMapL = 16;
  CHexMap HexMap[HexMapL] =
  {
    {'0', 0}, {'1', 1},
    {'2', 2}, {'3', 3},
    {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9},
    {'a', 10}, {'b', 11},
    {'c', 12}, {'d', 13},
    {'e', 14}, {'f', 15}
  };
  //pthread_mutex_lock(&mutexMemory);
  char *mstr = strdup(value);
  //主要是拷贝字符串s的一个副本，由函数返回值返回，这个副本有自己的内存空间，和s不相干
  //pthread_mutex_unlock(&mutexMemory);
  char *s = mstr;
  int result = 0;
  if (*s == '0' && *(s + 1) == 'X') s += 2;
  bool firsttime = true;
  while (*s != '/0')
  {
    bool found = false;
    for (int i = 0; i < HexMapL; i++)
    {
      if (*s == HexMap[i].chr)
      {
        if (!firsttime) result <<= 4;
        result |= HexMap[i].value;
        found = true;
        break;
      }
    }
    if (!found) break;
    s++;
    firsttime = false;
  }
  //pthread_mutex_lock(&mutexMemory);
  free(mstr);
  //pthread_mutex_unlock(&mutexMemory);
  return result;
}


MD5::MD5(const char* md5src)
{
    if (strcmp(md5src,"")==0)
    {
        for(int i=0;i<4;i++)
            m_data[i]=0;
        return;
    }
    for(int j = 0; j < 16; j++ )
    {
        char buf[10];
        strncpy(buf,md5src,2);
        md5src+=2;
        ((unsigned char*)m_data)[j] = _httoi(buf);
    }
}

MD5 MD5::operator +(MD5 adder)
{
    unsigned long m_newdata[4];
    for(int i=0;i<4;i++)
        m_newdata[i]=m_data[i]^(adder.m_data[i]);
    return MD5(m_newdata);
}

bool MD5::operator ==(MD5 cmper)
{
    return (memcmp(cmper.m_data ,m_data,16)==0);
	//比较内存区域buf1和buf2的前count个字节
}

//void MD5::operator =(MD5 equer)
//{
//    memcpy(m_data,equer.m_data ,16);
//}

CString MD5::ToString()
{
    char output[128];
    for(int j = 0; j < 16; j++ )
    {
        sprintf( output + j * 2, "%02x", ((unsigned char*)m_data)[j]);
		//把格式化的数据写入某个字符串缓冲区,这里表示把m_data[j]中的数据以16进制的形式显示到output+j*2中，长度为两位，不足两位左补0
    }
    return CString (output);
}
//得到hash值
CString MD5:: md5file(const char *md5hashfile)
{  
	char hashfile[MAX_PATH];//存放要检验的文件路径
	strcpy(hashfile,md5hashfile);
	FILE *readFile = fopen(hashfile, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要检测的文件。");//打开失败

	//const size_t bufferSize = 64;
	int barSize = 0;//记录读取文件的字节数
	// char readBuffer[bufferSize];
	// reaching the end of the file and getting position = getting file size (bytes).获得文件长度
	fseek(readFile, 0, SEEK_END);//将文件指针移动到文件的结尾
	barSize = ftell(readFile);//ftell得到流式文件的当前读写位置,其返回值是当前读写位置偏离文件头部的字节数.
	fseek(readFile, 0, SEEK_SET);//将文件指针移动到文件的头尾
	if (barSize == -1) 
    AfxMessageBox("不能获取文件长度");//不能获取文件字节数
	//int barSize1 = barSize*8;//文件的位数
	 char *pInPut = ( char *)malloc(barSize);//开辟内存存储读取文件
	
	fread(pInPut, sizeof(char), barSize, readFile);
	//读入barSize个sizeof(char)大小的块。也就是barSize字节了，barSize为文件总长度，相当于一次性读取整个文件
        
	  MD5 imd5(pInPut);//MD5文件检测对象
	  GenerateMD5((unsigned char *)pInPut,barSize);//调用MD5函数
      CString hashresult=ToString();//获得hash值
     if (pInPut)
	 {
		free(pInPut);   //释放内存空间
	 }
   
	fclose(readFile);
	return hashresult;//一定要放到程序的结尾处
}
//向密文中写入hash值
int MD5:: writehashtofile(const char *mifilename, const char* hashvalue)
{
	FILE *writeFile = fopen(mifilename, "a");
	if (writeFile == 0) 
	AfxMessageBox("写入文件失败.");//打开失败
	fseek(writeFile, 0, SEEK_END);//将文件指针移动到文件的结尾
	//int hashlength=hashvalue.GetLength();//获得hash值的长度
	int hashlength=strlen(hashvalue);
	fwrite(hashvalue, sizeof(char), hashlength, writeFile);//将hash值写入到密文中
	char *str=";";
	fwrite(str ,sizeof(char), 1, writeFile);//作为hash和密码的分界线
	fflush(writeFile);
	fclose(writeFile);
	return 0;
}
//读取密文中的hash值
CString MD5:: readhashfromfile(const char *mifilename)
{
	FILE *readFile = fopen(mifilename, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要检测的文件。");//打开失败
	fseek(readFile, -32, SEEK_END);//将文件指针移动到文件的结尾
	 char hash[33];//字符串尾部应该有个'\0'作为字符串结尾标志,所以申请空间应该多申请一个。
	fread(hash, sizeof(char),32, readFile);
	 hash[32]='\0';
	 CString hashresult=hash;
	 fclose(readFile);
	 return hashresult;
}