// yxyDES2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "yxyDES2.h"

int _tmain(int argc, _TCHAR* argv[])
{
	yxyDES2* my_des = new yxyDES2();
	//set key
	my_des->InitializeKey("12345678",0);
	printf("key is :\n 12345678 \n\n");

	//----------------------stand test------------------------------
	//encrypt
	printf("Test 8 bytes:\n yxyDES2. \n\n");
	my_des->EncryptData("yxyDES2.",0);

	//Ciphertext in bin
	printf("Ciphertext in bin:\n %s\n\n",my_des->GetCiphertextInBinary());

	//Ciphertext in Hex
	printf("Ciphertext in Hex:\n %s\n\n",my_des->GetCiphertextInHex());

	//decrypt
	my_des->DecryptData(my_des->GetCiphertextInBytes(),0);

	//show plaintext
	printf("After decrypt:\n %s\n\n",my_des->GetPlaintext());

	//----------------------------test any lenth---------------------------
	char* anyLenTest = "any length test of yxyDES2! a test, a test!";
	printf("Test anylenth :\n %s\n\n",anyLenTest);
	//encrypt
	my_des->EncryptAnyLength(anyLenTest,strlen(anyLenTest),0);
	
	// Ciphertext in bin .........Ciphertext in Hex
	char bitsCiphertextAnyLength[1024] = {0},hexCiphertextAnyLength[256] = {0};
	my_des->Bytes2Bits(my_des->GetCiphertextAnyLength(),bitsCiphertextAnyLength,strlen(anyLenTest)<<3);
	my_des->Bits2Hex(hexCiphertextAnyLength,bitsCiphertextAnyLength,strlen(anyLenTest)<<3);
	printf("Ciphertext in bin:\n");
	for(unsigned i=0;i<(strlen(anyLenTest)<<3);putchar(bitsCiphertextAnyLength[i++] + 48));
	printf("\n\nCiphertext in Hex:\n %s\n\n",hexCiphertextAnyLength);
	//decrypt
	my_des->DecryptAnyLength(my_des->GetCiphertextAnyLength(),strlen(anyLenTest),0);
	printf("After decrypt:\n %s\n\n",my_des->GetPlaintextAnyLength());

	//-------------这段是文件加密，请将路径修改后取消注释可看到效果----------------
	/*
	printf("FILE TEST:\n %s\n\n");

	
	FILE *fp = fopen("E:\\destest.avi","rb");
	FILE *fp2 = fopen("E:\\destest.des","wb+");
	FILE *fp3 = fopen("E:\\destest.des.avi","wb");

	while(!feof(fp))
	{
		char buf[8] = {0};
		fread(buf,sizeof(char),8,fp);
		my_des->EncryptData(buf,0);
		fwrite(my_des->GetCiphertextInBytes(),sizeof(char),8,fp2);
	}
	printf("En OK!");

	rewind(fp2);
	while(!feof(fp2))
	{
		char buf[8] = {0};
		fread(buf,sizeof(char),8,fp2);
		my_des->DecryptData(buf,0);
		fwrite(my_des->GetPlaintext(),sizeof(char),8,fp3);
	}

	fclose(fp);fclose(fp2);fclose(fp3);
	printf("De OK!");
	*/
	//pause
	getchar();
	return 0;
}
