#include "StdAfx.h"
#include "Folderoperate.h"
//#include"blowfishencryptionDlg.h"

Folderoperate::Folderoperate(void)
{
}


Folderoperate::~Folderoperate(void)
{
}
//打开文件函数
CString Folderoperate::openFloder()
{
	BROWSEINFO info;//声明结构体对象
	memset(&info,0,sizeof(BROWSEINFO));//初始化对象
	CWnd m_hWnd;
	info.hwndOwner=m_hWnd;//结构体参数赋值
	info.lpszTitle="选择路径";
	LPCITEMIDLIST pidl;//声明返回对象指针接受返回值
	pidl=SHBrowseForFolder(&info);//展示选择对话框进行路径选择
	if (pidl==NULL)
	{
		return 0;
	}
	char pszPath[512];//声明路径缓冲
	if (!SHGetPathFromIDList(pidl,pszPath))//从项目列表中获取选择的路径
	{
		AfxMessageBox("打开Folder路径失败");
		return 0;
	}
	return pszPath;
}
//文件夹blowfish加密解密处理
int Folderoperate:: EncDencFolder(bool mark,const char *sourcefile,const char *destfile,const char *pwd)
{
	strcpy(sourcefile1,sourcefile);
	strcpy(destfile1,destfile);
	strcpy(pwd1,pwd);
	CString readhash;//存放从密文中读取的hash
	CString strminghash;//解密后明文的hash
	bool markhash=true;//标记文件完整的标记
	bool bsrcisdirectory(false);//标志复制源是否为文件夹
	bool bdesisdirectory(false);//标志复制目标文件是否为文件夹
	if(::GetFileAttributesA(sourcefile)&FILE_ATTRIBUTE_DIRECTORY)
		bsrcisdirectory=true;//ture表示是文件夹
	if(::GetFileAttributesA(destfile)&FILE_ATTRIBUTE_DIRECTORY)
		bdesisdirectory=true;//ture表示是文件夹
	CFileFind filefind1;//声明MFC的文件查找对象
	
		//CString strfoldername=sourcefile1.Right(strold.GetLength()-strold.ReverseFind('\\')-1);
		//下面是对查找源父文件夹下的所有子文件夹进行复制
		//CString strfind=strcpy(sourcefile1,"\\*.*");//查找源文件夹下的所有文件和文件夹
	     CString str=sourcefile1;
	     CString strfind=str+"\\*.*";
		bool bfind=filefind1.FindFile(strfind);//查找第一个符合的文件或文件夹
		while(bfind)
		{
			bfind=filefind1.FindNextFileA();//查找符合的下一个文件或文件夹
			if (filefind1.IsDirectory())//找到的是文件夹
			{
				if(filefind1.IsDots()) continue;//排除DOS系统自带的
				CString srcfilepath=filefind1.GetFilePath();
				CString desfilepath=srcfilepath;
				EncDencFolder(mark,srcfilepath,desfilepath,pwd);//递归调用加密子文件夹
			}
			else//找到的是文件
			{
				CString srcfilepath;
				CString desfilepath;
				if(mark==true)//如果为加密
				{
					 srcfilepath=filefind1.GetFilePath();

					 desfilepath=srcfilepath+".enc";
					CString strhash= md5folder.md5file(srcfilepath);//获取hash值
					running1.processing(mark,srcfilepath,desfilepath,pwd);//调用加密函数
					md5folder.writehashtofile(desfilepath,strhash);//将hash写入到密文中
					running1.writemimatofile(desfilepath,pwd);//将密码写入到密文中
					running1.clearing(srcfilepath);//调用删除文件函数，删除源文件
				     //此处必能加return，否则就跳出循环
				}
				if(mark==false)//如果为解密
				{  
					desfilepath=filefind1.GetFilePath();
					readmima=running1.readmimafromfile(desfilepath);//从密文中读取密码
					//密码输入判断必须放在这个位置，如果密码不对，不能对密文做任何处理，否则无法解密，判断完后再还原密文
					 if(readmima!=pwd)
			          {
				         AfxMessageBox("输入密码错误，请重新输入密码");
				         return 1;
			          }
				    running1.rebackencfile(desfilepath,readmima.GetLength()+1);//删除密码，还原密文
				    readhash=md5folder.readhashfromfile(desfilepath);//从密文中读取hash
					running1.rebackencfile(desfilepath,32);//删除密文结尾的hash值，便于进行解密
					srcfilepath=desfilepath.Left(desfilepath.GetLength()-4);//获得明文路径
					running1.processing(mark,desfilepath,srcfilepath,pwd);//调用解密函数
				    strminghash=md5folder.md5file(srcfilepath);//获得解密文件的hash
					running1.clearing(desfilepath);//调用删除文件函数，删除源文件
					//if(strminghash==readhash)
						//markhash=true;
					//	AfxMessageBox("加密解密后，文件完整性良好");
					 if(strminghash!=readhash)
                      {
						  AfxMessageBox("加密解密后，"+srcfilepath+"文件完整性被破坏");
						  markhash=false;
					 }

				}

			}
		} 
		if((markhash==true)&&(mark==false))
        AfxMessageBox("加密解密后，文件完整性良好");
		return 0;
}
//文件夹3des加密解密处理
int Folderoperate:: EncDencDESFolder(bool mark,const char *soursefile,const char *destfile,const char *pwd_1,const char *pwd_2)
{
	strcpy(sourcefile1,soursefile);
	strcpy(destfile1,destfile);
	strcpy(pwd1,pwd_1);
	strcpy(pwd2,pwd_2);
	CString readhash;//存放从密文中读取的hash
	CString strminghash;//解密后明文的hash
	bool markhash=true;//标记文件完整的标记
	CFileFind filefind1;//声明MFC的文件查找对象
	CString str=sourcefile1;
	CString strfind=str+"\\*.*";
	bool bfind=filefind1.FindFile(strfind);//查找第一个符合的文件或文件夹
	while(bfind)
	{
		bfind=filefind1.FindNextFileA();//查找符合的下一个文件或文件夹
		if (filefind1.IsDirectory())//找到的是文件夹
		{
			if(filefind1.IsDots()) continue;//排除DOS系统自带的
			CString srcfilepath=filefind1.GetFilePath();
			CString desfilepath=srcfilepath;
			EncDencDESFolder(mark,srcfilepath,desfilepath,pwd1,pwd2);//递归调用加密子文件夹
		}
		else//找到的是文件
		{
			CString srcfilepath;
			CString desfilepath;
			if(mark==true)//如果为加密
			{
				srcfilepath=filefind1.GetFilePath();

				desfilepath=srcfilepath+".encD";
				CString strhash= md5folder.md5file(srcfilepath);//获取hash值
				running1.desprocess(mark,srcfilepath,desfilepath,pwd1,pwd2);//调用3DES加密处理函数
				md5folder.writehashtofile(desfilepath,strhash);//将hash写入到密文中
				running1.writemimatofile(desfilepath,pwd1);//将密码1写入到密文中
				char *str=";";
	            running1.writemimatofile(desfilepath,str);//用；分开两个密钥
			    running1.writemimatofile(desfilepath,pwd2);//将密码2写入到密文中
				running1.clearing(srcfilepath);//调用删除文件函数，删除源文件
				 //此处必能加return，否则就跳出循环
			}
			if(mark==false)//如果为解密
			{  
				desfilepath=filefind1.GetFilePath();
				readmima1=running1.readmimafromfile(desfilepath);//从密文中读取密码2
				readmima=running1.readmima1fromfile(desfilepath,readmima1.GetLength());//从密文中读取密码1
				//密码输入判断必须放在这个位置，如果密码不对，不能对密文做任何处理，否则无法解密，判断完后再还原密文
				if((readmima!=pwd1)&&(readmima1!=pwd2))
				{
					AfxMessageBox("输入密码错误，请重新输入密码");
					return 1;
				}
				running1.rebackencfile(desfilepath,readmima.GetLength()+readmima1.GetLength()+2);//删除密码，还原密文
				readhash=md5folder.readhashfromfile(desfilepath);//从密文中读取hash
				running1.rebackencfile(desfilepath,32);//删除密文结尾的hash值，便于进行解密
				srcfilepath=desfilepath.Left(desfilepath.GetLength()-5);//获得明文路径
				running1.desprocess(mark,desfilepath,srcfilepath,pwd1,pwd2);//调用解密函数
				strminghash=md5folder.md5file(srcfilepath);//获得解密文件的hash
				running1.clearing(desfilepath);//调用删除文件函数，删除源文件
				//if(strminghash==readhash)
					//markhash=true;
					//	AfxMessageBox("加密解密后，文件完整性良好");
					if(strminghash!=readhash)
					{
						AfxMessageBox("加密解密后，"+srcfilepath+"文件完整性被破坏");
						markhash=false;
					}

			}

		}
	}
	if((markhash==true)&&(mark==false))
		AfxMessageBox("加密解密后，文件完整性良好");
	return 0;

}
