#include "StdAfx.h"
#include "run.h"
#include "../Enc_Blowfish/Blowfish.h"//C/C++不同文件夹下包含头文件的方法及#include的使用有一定的规则
#include "EncryptionInterface.h"
#include "../yxyDES2/yxyDES2.h"
run::run(void)
{
}


run::~run(void)
{
}
//加密解密的过程函数
void run::processing(bool mark,const char *source, const char *dest, const char *pwd)
{  
	
	strcpy(_readFile,source);
	strcpy(_writeFile,dest);
	strcpy(_password,pwd);
	FILE *readFile = fopen(_readFile, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要加密的文件。");//打开失败

	const size_t bufferSize = 64;
	int barSize = 0;//记录读取文件的字节数

	// reaching the end of the file and getting position = getting file size (bytes).获得文件长度
	fseek(readFile, 0, SEEK_END);//将文件指针移动到文件的结尾
	barSize = ftell(readFile);//ftell得到流式文件的当前读写位置,其返回值是当前读写位置偏离文件头部的字节数.
	fseek(readFile, 0, SEEK_SET);//将文件指针移动到文件的头尾
	if (barSize == -1) 
    AfxMessageBox("不能获取文件长度");//不能获取文件字节数
	barSize = barSize / bufferSize;

	FILE *writeFile = fopen(_writeFile, "wb");
	if (writeFile == 0) 
	AfxMessageBox("写入文件失败.");//打开失败

	char readBuffer[bufferSize];
	char writeBuffer[bufferSize];
	size_t readRet = 0;

	BlowFishEnc encryption(_password);
	int encRet;
	

	while (!feof(readFile))//feof(fp)有两个返回值:如果遇到文件结束，函数feof（fp）的值为1，否则为0。
	{
		//readRet = fread(pInPut, sizeof(char), barSize, readFile);//读入buffreSize个sizeof(char)大小的块。也就是buffreSize字节了
		memset(readBuffer,0,64);
		readRet = fread(readBuffer, sizeof(char), bufferSize, readFile);

		if (mark==false) //如果为解密
		{
			
            memset(writeBuffer,0,64);
			encRet = encryption.decryptStream(readBuffer, (DWORD)readRet, writeBuffer);
			if (feof(readFile))
			{
				int pos = 0;
				// removing trailing zeros - encrypted file must be x8 bytes.
				while ((pos < 8) && ((writeBuffer + encRet - pos)[0] == 0)) pos++;
				// if found trailing zeros - decreasing the writing buffer marker (not writing them).
				if (pos) encRet -= (pos - 1);
				
			}
		}
		else //如果为加密
		{
			//memset(readBuffer,0,1024);
			memset(writeBuffer,0,64);
			encRet = encryption.encryptStream(readBuffer, (DWORD)readRet, writeBuffer);
		}
		
		fwrite(writeBuffer, sizeof(char),encRet, writeFile);
		
		
	}
       // char *str=";";
	   // fwrite(str ,sizeof(char), 1, writeFile);
    fflush(writeFile);

	fclose(writeFile);
	fclose(readFile);
	
	ZeroMemory(writeBuffer, bufferSize);
	ZeroMemory(readBuffer, bufferSize);

}
//删除源文件
void run::clearing(const char *source)
{
	CString strdeletefile=source;
		if (!::DeleteFile(strdeletefile))
	  {
		int nerr=::GetLastError();
		AfxMessageBox("delete file wrong");
		return;
	  }

}




//还原密文
void run::rebackencfile(const char *mifilename,int len)
{
	FILE *readFile = fopen(mifilename, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	AfxMessageBox("不能打开要检测的文件。");//打开失败
	fseek(readFile,-len, SEEK_END);//将文件指针移动到删除内容前
	int barSize = ftell(readFile);//要读取的字节数，ftell得到流式文件的当前读写位置,其返回值是当前读写位置偏离文件头部的字节数.
	fseek(readFile, 0, SEEK_SET);//将文件指针移动到文件的头部
	if (barSize == -1) 
    AfxMessageBox("不能获取文件长度");//不能获取文件字节数
	//int barSize1 = barSize*8;//文件的位数
	 char *poutPut = ( char *)malloc(barSize);//开辟内存存储读取文件
	 fread(poutPut, sizeof(char), barSize, readFile);//读入barSize个sizeof(char)大小的块。也就是barSize字节了，barSize为文件总长度，相当于一次性读取整个文件
     FILE *writeFile = fopen(mifilename, "wb");
	if (writeFile == 0) 
	AfxMessageBox("写入文件失败.");//打开失败
	fwrite(poutPut, sizeof(char), barSize, writeFile);
	if (poutPut)
	 {
		free(poutPut);   //释放内存空间

	 }
	fflush(writeFile);

	fclose(writeFile);
	fclose(readFile);

}
//向密文中写入密码
void run::writemimatofile(const char *mifilename, const char* pwd)
{
	FILE *writeFile = fopen(mifilename, "a");//打开写入文件的方式为a，原内容仍存在注意写入方式
	if (writeFile == 0) 
	AfxMessageBox("写入文件失败.");//打开失败
	fseek(writeFile, 0, SEEK_END);//将文件指针移动到文件的结尾
	
	fwrite(pwd, sizeof(char), strlen(pwd), writeFile);//将密码写入到密文中
	
	fflush(writeFile);
	fclose(writeFile);
	return ;
}
//从密文中读取密码
CString run:: readmimafromfile(const char *mifilename)
{
	FILE *readFile = fopen(mifilename, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要检测的文件。");//打开失败
	
	char mimalen[2];//一个字符一个字符的读取，字符数组内存不用太大
	int i=1;//记录读取的字符总数
	
	while(strcmp(mimalen,";")!=0)//如果读到分解符“；”，就停止读取，即可得到i的值
	{
     fseek(readFile, -i, SEEK_END);//将文件指针移动到文件的结尾
	 fread(mimalen, sizeof(char),1, readFile);//一个字符一个字符的读取
	 mimalen[1]=0;//加字符串结束标志
	 i++;
	}
	 
	 char mima[100];
	 fread(mima, sizeof(char),i-2, readFile);//从密文中读密码
	 mima[i-2]=0;//加字符串结束标志
	 fclose(readFile);
	 
	 return mima;
}
//从密文中读取密钥1
CString run::readmima1fromfile(const char *mifilename,int lenght)
{
	FILE *readFile = fopen(mifilename, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要检测的文件。");//打开失败
	
	char mimalen[2];//一个字符一个字符的读取，字符数组内存不用太大
	int i=1;//记录读取的字符总数
	
	while(strcmp(mimalen,";")!=0)//如果读到分解符“；”，就停止读取，即可得到i的值
	{
     fseek(readFile, -(lenght+1+i), SEEK_END);//将文件指针移动到文件的结尾
	 fread(mimalen, sizeof(char),1, readFile);//一个字符一个字符的读取
	 mimalen[1]=0;//加字符串结束标志
	 i++;
	}
	 
	 char mima[100];
	 fread(mima, sizeof(char),i-2, readFile);//从密文中读密码
	 mima[i-2]=0;//加字符串结束标志
	 fclose(readFile);
	 
	 return mima;
}









//3des文件加解密处理函数
void run:: desprocess(bool mark,const char *source, const char *dest, const char *pwd1,const char *pwd2)
{
	strcpy(_readFile,source);
	strcpy(_writeFile,dest);
	strcpy(_password1,pwd1);
	strcpy(_password2,pwd2);
	char buff[8] = {0};
	size_t readRet = 0;

	FILE *readFile = fopen(_readFile, "rb");//为输入打开二进制文件
	if (readFile == 0) 
	 AfxMessageBox("不能打开要加密的文件。");//打开失败
	int barSize = 0;//记录读取文件的字节数
	// reaching the end of the file and getting position = getting file size (bytes).获得文件长度
	fseek(readFile, 0, SEEK_END);//将文件指针移动到文件的结尾
	barSize = ftell(readFile);//ftell得到流式文件的当前读写位置,其返回值是当前读写位置偏离文件头部的字节数.
	if(mark==true)
	filldes(_readFile,barSize);//填充“；”
	fseek(readFile, 0, SEEK_SET);//将文件指针移动到文件的头尾
	if (barSize == -1) 
    AfxMessageBox("不能获取文件长度");//不能获取文件字节数

	FILE *writeFile = fopen(_writeFile, "wb");
	if (writeFile == 0) 
	AfxMessageBox("写入文件失败.");//打开失败
    DES.InitializeKey(_password1,0);
	DES.InitializeKey(_password2,1);
	if(mark==true)//如果为加密
	{
		while(!feof(readFile))
		{
			memset(buff,0,8);
			readRet=fread(buff,sizeof(char),8,readFile);//记录读取的字节数
			DES.EncryptData(buff, 0);
			DES.DecryptData(DES.GetCiphertextInBytes(), 1);
			DES.EncryptData(DES.GetPlaintext(), 0);
			fwrite(DES.GetCiphertextInBytes(),sizeof(char),readRet,writeFile);//readRet读了多少，就写入多少
		}

		fclose(readFile);
		fflush(writeFile);
		fclose(writeFile);
		return;
	}
	else if(mark==false)//如果为解密
	{
		while(!feof(readFile))
		{
			memset(buff,0,8);
			readRet=fread(buff,sizeof(char),8,readFile);//记录读取的字节数
			//D(key0)-E(key1)-D(key0)
			DES.DecryptData(buff, 0);
			DES.EncryptData(DES.GetPlaintext(), 1);
			DES.DecryptData(DES.GetCiphertextInBytes(), 0);
			fwrite(DES.GetPlaintext(),sizeof(char),readRet,writeFile);//readRet读了多少，就写入多少
			
		}
		fclose(readFile);
		fflush(writeFile);
		fclose(writeFile);
		int fill=readfill(_writeFile);//读取填充位数
		if(fill>1)//判断是否进行了填充
		rebackencfile(_writeFile,fill-2);//还原明文
		return;
	}

}
//3DES填充
void run::filldes(const char *mifilename,int len)
{
	if(len%8==0)
		return;
	int fillnum=8-len%8;
	FILE *writeFile = fopen(mifilename, "a");
	if (writeFile == 0) 
		AfxMessageBox("写入文件失败.");//打开失败
	//char fillcontent[8]={0};
	//memset(fillcontent,0,9);
	CString fillcontent=";";
	int i;
	for(i=1;i<fillnum;i++)
	{
		fillcontent+=";";

	}
	//fillcontent[fillnum]='/0';
	fwrite(fillcontent,fillnum,1,writeFile);
	fflush(writeFile);
	fclose(writeFile);
	return;
}
//读取填充位数
int run:: readfill(const char *mingfilename)
{
	FILE *readFile = fopen(mingfilename, "rb");//为输入打开二进制文件
	if (readFile == 0) 
		AfxMessageBox("不能打开要加密的文件。");//打开失败
	char mimalen[2]={0};//一个字符一个字符的读取，字符数组内存不用太大
	int i=1;//记录读取的字符总数
	//fseek(readFile,-i, SEEK_END);//将文件指针移动到文件的结尾
	    fseek(readFile,-1, SEEK_END);//将文件指针移动到文件的结尾
		fread(mimalen, sizeof(char),1, readFile);//一个字符一个字符的读取
	while(strcmp(mimalen,";")==0)//如果读到不是“；”时，就停止读取，即可得到i的值
	{
		fseek(readFile,-i, SEEK_END);//将文件指针移动到文件的结尾
		fread(mimalen, sizeof(char),1, readFile);//一个字符一个字符的读取
		mimalen[1]=0;//加字符串结束标志
		i++;
	}
	fclose(readFile);
	return i;
}