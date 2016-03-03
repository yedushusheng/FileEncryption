#pragma once

#include "Resource.h"  
// Change 对话框

class Change : public CDialogEx
{
	DECLARE_DYNAMIC(Change)

public:
	Change(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Change();

 	char szCurrentPath[512];
	char szAdmin[64];
	char szPassWord[64];

// 对话框数据
	enum { IDD = IDD_CHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditNewname();
	afx_msg void OnEnChangeEditNewpassword();
	afx_msg void OnEnChangeEditPasswordagine();
};
