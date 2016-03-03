
// blowfishencryptionDlg.h : 头文件
//
//#include "resource.h“
#include "stdafx.h"
#include "afxdialogex.h"
#include"string.h"
#include "../Enc_Blowfish/Blowfish.h"//C/C++不同文件夹下包含头文件的方法及#include的使用有一定的规则
#include "EncryptionInterface.h"
#include"MD5.h"
#include"Folderoperate.h"

#pragma once


// CblowfishencryptionDlg 对话框
class CblowfishencryptionDlg : public CDialogEx
{
// 构造
public:
	CblowfishencryptionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BLOWFISHENCRYPTION_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnchosesrcfile();
	afx_msg void OnBnClickedBtnenorden();

	//CIPHER _cipher;
	char _readFile[MAX_PATH];
	char _writeFile[MAX_PATH];
    char _password[100];
	char _password1[100];
	char md5hash[MAX_PATH];
	CString hashresult;//加密前的hash值
	CString hashresult1;//解密后的hash值
   // BlowFishEnc encryption;
	MD5 iMD5;
	Folderoperate folderoperate;
	CString readmima;
	CString readmima1;
	CString m_editmima;
	CString m_editmima1;
	afx_msg void OnBnClickedBtnchoosedestfile();
	void wipePwds(char *pwd, char *verify);
	afx_msg void OnBnClickedBtnsuaxin();
	afx_msg void OnBnClickedRadiojimi();
	afx_msg void OnBnClickedRadiojiemi();
	afx_msg void OnBnClickedRadioblowfish();
	afx_msg void OnBnClickedRadio3des();
	afx_msg void OnBnClickedLoginbutton();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonChange();

//登录
public:
	//afx_msg void OnBnClickedLoginbutton();
	// 登陆按钮
	CButton m_LonginButton;
	// 注销
	CButton m_logoutButton;
	// 显示登陆的用户名
	CStatic m_static_adminName;

	//afx_msg void OnBnClickedButtonLogout();

	// 修改用户名密码的button
	CButton m_changeButton;
	//afx_msg void OnBnClickedButtonChange();

	afx_msg void OnStnClickedadminname();

	afx_msg void OnBnClickedTwice();

	afx_msg void OnBnClickedButtonKeys();
	afx_msg void OnBnClickedButtonOpenfile();

	CString m_editquerenmima;
	afx_msg void OnBnClickedButtonLog();

	CButton m_generatekeyButton;
	CButton m_openfileButton;

	//读取文件名字
	CString	FilePath;
	int typetotal;
	// 查找当前目录下的文件
	void FindFiles(CString sPath);
	CStringArray typeArray;
	struct typeCount{
		CString type;
		int num;
	}TypeCount[1000];
	afx_msg void OnBnClickedButtonDriver();
};
