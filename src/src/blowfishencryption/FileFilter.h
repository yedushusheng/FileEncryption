#pragma once
#include "stdafx.h"

class FileFilter
{
public:
	 FileFilter(void);
	~FileFilter(void);


		CEdit m_edit;
	CEdit m_total;
	CEdit m_type_total;

	//读取文件名字
	CString	FilePath;

	int total;
	int typetotal;
	// 获得当前文件夹下的文件总数
	void GetFolderFilesCount(LPCTSTR pPathName);
	// 查找当前目录下的文件
	void FindFiles(CString sPath);
	CListCtrl m_typelist;
	CStringArray typeArray;
	struct typeCount{
		CString type;
		int num;
	}TypeCount[1000];
	bool newtypeFlag;
	void showtype();

     void GetFolderFilesCount(LPCTSTR pPathName);
	 void FindFiles(CString sPath);
	 void showtype();
}