#pragma once


// Screat 对话框

class Screat : public CDialogEx
{
	DECLARE_DYNAMIC(Screat)

public:
	Screat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Screat();

	char szCurrentPath[512];//路径
	char szAdmin[64];   //用户名
	char szPassWord[64];//密码

// 对话框数据
	enum { IDD = IDD_SCRETE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditAdminame();
	afx_msg void OnEnChangeEditPassword();
};
