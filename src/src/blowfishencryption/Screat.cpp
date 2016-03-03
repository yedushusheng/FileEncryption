// Screat.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "Screat.h"
#include "afxdialogex.h"
#include <io.h>
#include "blowfishencryptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CONFIG_FILE_NAME   "config.ini"
#define CONFIG_VALUE_LENGTH 64


// Screat 对话框

IMPLEMENT_DYNAMIC(Screat, CDialogEx)

Screat::Screat(CWnd* pParent /*=NULL*/)
	: CDialogEx(Screat::IDD, pParent)
{

}

Screat::~Screat()
{
}

void Screat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Screat, CDialogEx)
	ON_BN_CLICKED(IDOK, &Screat::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Screat::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_ADMINAME, &Screat::OnEnChangeEditAdminame)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, &Screat::OnEnChangeEditPassword)
END_MESSAGE_MAP()


// Screat 消息处理程序


void Screat::OnBnClickedOk()
{
	//从窗口读入的用户名和密码
	CString gtAdmin;
	CString gtPassWord;

	memset(szPassWord, 0, CONFIG_VALUE_LENGTH);
	memset(szAdmin, 0, CONFIG_VALUE_LENGTH);
	memset(szCurrentPath, 0, 512);

	GetCurrentDirectory(512, szCurrentPath);     //取得config.ini的地址
	strcat(szCurrentPath, "\\");
	strcat(szCurrentPath, CONFIG_FILE_NAME);

	if(-1 == access(szCurrentPath, 0))    //ini文件不存在
	{
		MessageBox("密码配置文档不存在","提示信息");
	}
	else
	{
		GetDlgItemText(IDC_EDIT_ADMINAME,gtAdmin);
		GetDlgItemText(IDC_EDIT_PASSWORD,gtPassWord);

		GetPrivateProfileString("admin", "admin", "admin", szAdmin, CONFIG_VALUE_LENGTH, szCurrentPath);
		GetPrivateProfileString("password", "password", "password", szPassWord, CONFIG_VALUE_LENGTH, szCurrentPath);



		if ((0 == strcmp(szAdmin,gtAdmin))&&(0 == strcmp(szPassWord,gtPassWord)))
		{
			MessageBox("登陆成功！","提示信息");
			CblowfishencryptionDlg *p = (CblowfishencryptionDlg*)GetParent();
			p->m_LonginButton.ShowWindow(SW_HIDE);//隐藏登陆按键
			p->m_logoutButton.ShowWindow(SW_SHOW);//显示注销和修改建
			p->m_changeButton.ShowWindow(SW_SHOW);
			p->m_static_adminName.ShowWindow(SW_SHOW);
			p->m_static_adminName.SetWindowTextA(gtAdmin);

			p->m_generatekeyButton.ShowWindow(SW_SHOW);
			p->m_openfileButton.ShowWindow(SW_SHOW);//显示随机生成密钥的按钮
			CDialogEx::OnCancel();
		}
		else
		{
			MessageBox("用户名或密码错误！","提示信息");
			SetDlgItemText(IDC_EDIT_PASSWORD,"");
		}
	}


	//CDialogEx::OnOK();
}


void Screat::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void Screat::OnEnChangeEditAdminame()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Screat::OnEnChangeEditPassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
