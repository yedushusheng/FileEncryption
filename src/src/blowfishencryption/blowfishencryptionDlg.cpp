
// blowfishencryptionDlg.cpp : 实现文件
//
#include"resource.h"
#include "stdafx.h"
#include "blowfishencryption.h"
#include "blowfishencryptionDlg.h"
#include "afxdialogex.h"
#include "../Enc_Blowfish/Blowfish.h"//C/C++不同文件夹下包含头文件的方法及#include的使用有一定的规则
#include "EncryptionInterface.h"
#include "run.h"
#include "MD5.h"
#include"Folderoperate.h"

#include "stdafx.h"
#include "afxdialogex.h"
#include "Screat.h"
#include "Change.h"

#include "Random.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#ifndef EncryptionInterface.h
//#define EncryptionInterface.h
//#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CblowfishencryptionDlg 对话框




CblowfishencryptionDlg::CblowfishencryptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CblowfishencryptionDlg::IDD, pParent)
	, m_editquerenmima(_T(""))
{   //BlowFishEnc encryption;
	//BlowFishEnc encryption(const char *pwd);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_mima = _T("");
	m_editmima = _T("");
	m_editmima1 = _T("");
}

void CblowfishencryptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_mima, m_mima);
	DDX_Text(pDX, IDC_EDITmima, m_editmima);
	DDX_Text(pDX, IDC_EDITquerenmima, m_editmima1);
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LoginButton, m_LonginButton);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_logoutButton);
	DDX_Control(pDX, IDC_adminName, m_static_adminName);

	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_changeButton);



	DDX_Control(pDX, IDC_BUTTON_KEYS, m_generatekeyButton);
	DDX_Control(pDX, IDC_BUTTON_OPENFILE, m_openfileButton);
}

BEGIN_MESSAGE_MAP(CblowfishencryptionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Btnchosesrcfile, &CblowfishencryptionDlg::OnBnClickedBtnchosesrcfile)
	ON_BN_CLICKED(IDC_Btnenorden, &CblowfishencryptionDlg::OnBnClickedBtnenorden)
	ON_BN_CLICKED(IDC_Btnchoosedestfile, &CblowfishencryptionDlg::OnBnClickedBtnchoosedestfile)
	ON_BN_CLICKED(IDC_Btnsuaxin, &CblowfishencryptionDlg::OnBnClickedBtnsuaxin)
	ON_BN_CLICKED(IDC_RADIOjimi, &CblowfishencryptionDlg::OnBnClickedRadiojimi)
	ON_BN_CLICKED(IDC_RADIOjiemi, &CblowfishencryptionDlg::OnBnClickedRadiojiemi)
	ON_BN_CLICKED(IDC_RADIOblowfish, &CblowfishencryptionDlg::OnBnClickedRadioblowfish)
	ON_BN_CLICKED(IDC_RADIO3des, &CblowfishencryptionDlg::OnBnClickedRadio3des)
	ON_BN_CLICKED(IDC_LoginButton, &CblowfishencryptionDlg::OnBnClickedLoginbutton)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CblowfishencryptionDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CblowfishencryptionDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_TWICE, &CblowfishencryptionDlg::OnBnClickedTwice)
	ON_BN_CLICKED(IDC_BUTTON_KEYS, &CblowfishencryptionDlg::OnBnClickedButtonKeys)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CblowfishencryptionDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CblowfishencryptionDlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_DRIVER, &CblowfishencryptionDlg::OnBnClickedButtonDriver)
END_MESSAGE_MAP()


// CblowfishencryptionDlg 消息处理程序

BOOL CblowfishencryptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CblowfishencryptionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CblowfishencryptionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CblowfishencryptionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//选择要加解密的文件或文件夹
void CblowfishencryptionDlg::OnBnClickedBtnchosesrcfile()
{
	// TODO: Add your control notification handler code here
     char resultFile[MAX_PATH];
	 char destfile[MAX_PATH];
	  if((IsDlgButtonChecked(IDC_RADIOblowfish) != BST_CHECKED)&&(IsDlgButtonChecked(IDC_RADIO3des)!= BST_CHECKED)&&(IsDlgButtonChecked(IDC_TWICE)!= BST_CHECKED))
	  MessageBox("请选择解密算法");
	  else
	  {
		  if (IsDlgButtonChecked(IDC_RADIOjimi) == BST_CHECKED)//如果为加密
		  {  
			  if (IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如果为单一文件
			  {
				  CFileDialog filedlg(true);//创建打开文件对话框
				  filedlg.m_ofn.lpstrTitle=(_T("选择加密文件"));//添加打开对话框名
				  filedlg.m_ofn.lpstrFilter=_T("All Files(*.*)\0*.*\0\0");//设置对话框中文件类型
				  if(IDOK==filedlg.DoModal())
				  {
					  SetDlgItemText(IDC_srcfile,filedlg.GetPathName());//获得文件路径
					  GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);
					  
						  if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
						  strcat(resultFile,".enc");
					      if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
                          strcat(resultFile,".encD");
						  else if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
						  {
								strcat(resultFile,".encD.enc");
						  }
						  SetDlgItemText(IDC_destfile,resultFile);
					 // }
				  }
				  return;
			  }
			  if (IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如果为文件夹加密
			  {

				  SetDlgItemText(IDC_srcfile,folderoperate.openFloder());
				  GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);
				 // GetDlgItemText(IDC_destfile,destfile,MAX_PATH);
				 // if(strlen(destfile)==0)
				  //{
					  //strcat(resultFile,".encD.enc");//目的文件文本框中显示后缀
					  SetDlgItemText(IDC_destfile,resultFile);
				  //}
				  return;
			  }
		  }
		  else if(IsDlgButtonChecked(IDC_RADIOjiemi) == BST_CHECKED)//如果为解密
		  {  
			  if (IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如果为单一文件
			  {
				  CFileDialog filedlg(FALSE);//创建保存文件对话框
				  filedlg.m_ofn.lpstrTitle=(_T("保存解密文件"));//添加打开对话框名
				  filedlg.m_ofn.lpstrFilter=_T("All Files(*.*)\0*.*\0\0");//设置对话框中文件类型
				  if(IDOK==filedlg.DoModal())
				  {  
					  SetDlgItemText(IDC_srcfile,filedlg.GetPathName());
					  GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);//获得文件路径
					  GetDlgItemText(IDC_destfile,destfile,MAX_PATH);
					 
					  if(strlen(destfile)>4)
					  {
						  destfile[strlen(destfile)-4]=0;
						  if(resultFile!=destfile)
							  MessageBox("确定要重写源文件文件吗？");
					  }
				  }
				  return;
			  }
			  if (IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如果为文件夹解密
			  {

				  SetDlgItemText(IDC_destfile,folderoperate.openFloder());
				  GetDlgItemText(IDC_destfile,resultFile,MAX_PATH);
				  GetDlgItemText(IDC_srcfile,destfile,MAX_PATH);
				  if(strlen(destfile)==0)
				  {
					  //strcat(resultFile,".encD.enc");
					  SetDlgItemText(IDC_srcfile,resultFile);
				  }
				  return;
			  }
		  }

	  }

	return ;
}


//加解密
void CblowfishencryptionDlg::OnBnClickedBtnenorden()
{
	// TODO: Add your control notification handler code here
	//获得明文路径，密文路径和密码
	char source[MAX_PATH];
	GetDlgItemText(IDC_srcfile, source, MAX_PATH);
	char dest[MAX_PATH];
	GetDlgItemText(IDC_destfile, dest, MAX_PATH);

	char tempfile[MAX_PATH];
	GetDlgItemText(IDC_srcfile, tempfile, MAX_PATH);
	if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED && IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)
	{
		strcat(tempfile,".encD");//如果不进行判断，则会出现文件夹加密中后缀错误
	}
	/*
	if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED  && IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)
	{
		strcat(tempfile,".encD.enc");
	}
	*/
	char password[57];//密钥1
	GetDlgItemText(IDC_EDITmima, password, 56);
	password[56]=0;
    char passverify[57];//密钥2
	GetDlgItemText(IDC_EDITquerenmima, passverify, 56);
	passverify[56] = 0;

	//判断加密设置及路径是否正确
    strncpy(_password, password, 100);
	strncpy(_password1, passverify, 100);
	bool mark=true;//标志位，加密时为true，解密时为false
    run runing;//定义加密类的一个对象
	if (IsDlgButtonChecked(IDC_RADIOjimi) == BST_CHECKED)//如果为加密过程
	{
		if (!PathFileExists(source))
		{
			MessageBox("加密文件不存在.", "错误");
			wipePwds(password, passverify);
			return ;
		}

		strcpy(_readFile,source );
		strcpy(_writeFile, dest);
		const char*hashresultvalue;
		if(IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如为单一文件加密
		{
			//判断是否进行文件完整性检测
			//if(IsDlgButtonChecked(IDC_CHECKfile) == BST_CHECKED)
			//{
			//调用MD5函数产生hash值
			//MD5 iMD5;
			hashresult=iMD5.md5file(_readFile);
			hashresultvalue=(LPCTSTR)hashresult;
			//}
			if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
				runing.processing(mark,_readFile,_writeFile,password);//调用blowfish加密/解密函数
			if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
				runing.desprocess(mark,_readFile,_writeFile,password,passverify);//调用3DES加解密函数
			if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
			{					
				runing.desprocess(mark,_readFile,tempfile,password,passverify);//调用3DES加解密函数				
				runing.processing(mark,tempfile,_writeFile,password);//调用blowfish加密/解密函数
				runing.clearing(tempfile);
			}

			AfxMessageBox("加密完成");
			runing.clearing(_readFile);//调用删除文件函数，删除源文件			
			//将hash值写入到密文中
			//if(IsDlgButtonChecked(IDC_CHECKfile) == BST_CHECKED)
			//{

			//MD5 iMD5;
			iMD5.writehashtofile(_writeFile,hashresultvalue);
			//}
			//将密码写入到加密文件中
            runing.writemimatofile(_writeFile,password);//将密码（1）写入到密文中
			if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED||(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED))//如为3DES加密，要分开两个密钥，用；做标记
			{
			   char *str=";";
	           runing.writemimatofile(_writeFile,str);//用；分开两个密钥
			   runing.writemimatofile(_writeFile,passverify);//将密码2写入到密文中
			}
            wipePwds(password, passverify);
			return;
		}

		if(IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如为指定目录加密
		{
			if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
				folderoperate.EncDencFolder(mark,source,dest,password);//调用blowfish文件夹加解密函数
			if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
				folderoperate.EncDencDESFolder(mark,source,dest,password,passverify);//调用3des文件夹加解密函数
			if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
			{
				folderoperate.EncDencDESFolder(mark,source,tempfile,password,passverify);
				folderoperate.EncDencFolder(mark,tempfile,dest,password);
				//runing.clearing(tempfile);//前面已经删除，再次删除会报错
			}
			AfxMessageBox("加密完成");
			wipePwds(password, passverify);
			return;
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIOjiemi) == BST_CHECKED)//如为解密过程
	{
		if (!PathFileExists(dest))
		{
			MessageBox("要解密文件不存在.", "错误");
			wipePwds(password, passverify);
			return ;
		}
		mark=false;//解密标志
		strcpy(_readFile, dest);
		strcpy(_writeFile, source);
		//解密之前从密文中读取hash
		 CString readhash;
       if(IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如果为文件解密
	    {
			//if(IsDlgButtonChecked(IDC_CHECKfile) == BST_CHECKED)//如果进行文件检验
			//{
			if((IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED) ||(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED))//如为3DES
			{
				readmima1=runing.readmimafromfile(_readFile);//从密文中读取密码2
				readmima=runing.readmima1fromfile(_readFile,readmima1.GetLength());//从密文中读取密码1
			// runing.rebackencfile(_readFile,readmima1.GetLength()+1);//删除密码2和分号，还原密文
			}
			else if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
			{
				readmima=runing.readmimafromfile(_readFile);//从密文中读取密码
			}
			//密码输入判断必须放在这个位置，如果密码不对，不能对密文做任何处理，否则无法解密，判断完后再还原密文
			if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED||(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED))//如果为3DES判断密码输入
			{
               if((readmima!=password)&&(readmima1!=passverify))
			   { 
				   AfxMessageBox("输入密码错误，请重新输入密码");
			       return;
			   }
              runing.rebackencfile(_readFile,readmima.GetLength()+readmima1.GetLength()+2);//删除密码，还原密文,注意：必须在判断完密码后，才能删除密文中的密码
			}
			else if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
			{
				if(readmima!=password)//如果为blowfish判断密码输入
				{
					{
						AfxMessageBox("输入密码错误，请重新输入密码");
						return;
					}
				}
				runing.rebackencfile(_readFile,readmima.GetLength()+1);//删除密码，还原密文,注意：必须在判断完密码后，才能删除密文中的密码
			}
			readhash=iMD5.readhashfromfile(_readFile);//从密文中读取hash
			runing.rebackencfile(_readFile,32);//删除密文结尾的hash值，在进行解密
			// }
			if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
			{
				runing.processing(mark,_readFile,_writeFile,password);//调用blowfish加密/解密函数
				hashresult1=iMD5.md5file(_writeFile);
			}
			if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
			{
				runing.desprocess(mark,_readFile,_writeFile,password,passverify);//调用3DES加解密函数
				hashresult1=iMD5.md5file(_writeFile);
			}
			else if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
			{
				runing.processing(mark,_readFile,tempfile,password);//blowfish
				runing.desprocess(mark,tempfile,_writeFile,password,passverify);//3des
				runing.clearing(tempfile);//删除临时文件
				hashresult1=iMD5.md5file(_writeFile);
			}
			//runing.processing(mark,_readFile,_writeFile,password);//调用加密/解密函数
			AfxMessageBox("解密完成");
			runing.clearing(_readFile);//调用删除文件函数，删除密文
			wipePwds(password, passverify);

			//判断是否进行文件完整性检测
			// if(IsDlgButtonChecked(IDC_CHECKfile) == BST_CHECKED)
			// {
			//调用MD5函数产生hash值
			// MD5 iMD5;
			//hashresult1=iMD5.md5file(_writeFile);

			
			if(hashresult1==readhash)
			{
				MessageBox("加密解密后，文件完整性良好");
			}
			else if(hashresult1!=readhash)
			{
				MessageBox("加密解密后，文件被破坏");
			}
			
             return;
		 }
		  
	   
	   if(IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如为指定目录解密
	   {   
		   int mimamark;
		   if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
			    mimamark= folderoperate.EncDencFolder(mark,source,dest,password);//调用blowfish文件夹加密函数
		   if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
			    mimamark=folderoperate.EncDencDESFolder(mark,source,dest,password,passverify);//调用3des文件夹加密函数
		   if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
		   {
			    mimamark= folderoperate.EncDencFolder(mark,tempfile,dest,password);
				mimamark=folderoperate.EncDencDESFolder(mark,source,tempfile,password,passverify);
		   }
		  if(mimamark==1)
		  return;
		  AfxMessageBox("解密完成");
		  wipePwds(password, passverify);
          return ;
		}		
	}	
	else
	{
		MessageBox("请选择文件操作方式", "错误");
	}
	//wipePwds(password, passverify);
	return ;	
}

//密文路径选择
void CblowfishencryptionDlg::OnBnClickedBtnchoosedestfile()
{
	// TODO: Add your control notification handler code here
	char resultFile[MAX_PATH]; 
	char destfile[MAX_PATH];
	//CFileDialog filedlg(mark);//创建打开文件对话框
	if (IsDlgButtonChecked(IDC_RADIOjimi) == BST_CHECKED)//如果为加密
	{  
		if (IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如果为单一文件
		{
			CFileDialog filedlg(FALSE);//创建保存文件对话框
			filedlg.m_ofn.lpstrTitle=(_T("保存解密文件"));//添加打开对话框名
			if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
			{
				filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.enc)\0*.enc\0\0");//设置对话框中文件类型	
			}
            else if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
			{
				filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.encD)\0*.encD\0\0");//设置对话框中文件类型	
			}
			/*
			else if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
			{
				filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.enc.encD)\0*.enc.encD\0\0");
			}
			*/

			if(IDOK==filedlg.DoModal())
			{  
				SetDlgItemText(IDC_destfile,filedlg.GetPathName());
				GetDlgItemText(IDC_destfile,destfile,MAX_PATH);//获得文件路径
				GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);
				if(strlen(resultFile)!=0)
				{
					strcat(resultFile,".enc");
					if(resultFile!=destfile)
						MessageBox("确定要重写加密文件吗？");
				}
			}
			return;
		}
		if (IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如果为文件夹加密
		  {
            
			 SetDlgItemText(IDC_destfile,folderoperate.openFloder());
			 GetDlgItemText(IDC_destfile,destfile,MAX_PATH);
			 GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);
				 if(strlen(resultFile)==0)
				 {
					 //strcat(resultFile,".enc");
					 SetDlgItemText(IDC_srcfile,destfile);
				 }
			 return;
		  }

	} 
	else if(IsDlgButtonChecked(IDC_RADIOjiemi) == BST_CHECKED)//如果为解密
	{
		if (IsDlgButtonChecked(IDC_RADIOfileenc) == BST_CHECKED)//如果为单一文件
		{
			CFileDialog filedlg(true);//创建打开文件对话框
			filedlg.m_ofn.lpstrTitle=(_T("选择解密文件"));//添加打开对话框名
			if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)
            filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.enc)\0*.enc\0\0");//设置对话框中文件类型		  
            else if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)
            filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.encD)\0*.encD\0\0");//设置对话框中文件类型		               
			/*
			else if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
			filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.enc.encD)\0*.encD\0\0");
			*/	
			//filedlg.m_ofn.lpstrFilter=_T("Encrypted Files (*.enc)\0*.enc\0\0");//设置对话框中文件类型
			if(IDOK==filedlg.DoModal())
			{

				SetDlgItemText(IDC_destfile,filedlg.GetPathName());//获得文件路径
				GetDlgItemText(IDC_destfile,destfile,MAX_PATH);
				if(IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)//如为3DES+blowfish，还原明文路径
					destfile[strlen(destfile)-9]=0;
				else if(IsDlgButtonChecked(IDC_RADIOblowfish) == BST_CHECKED)//如为blowfish，还原明文路径
					destfile[strlen(destfile)-4]=0;
				else if(IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED)//如为3DES，还原明文路径
				{
					destfile[strlen(destfile)-5]=0;
					strcpy(resultFile,destfile);
					SetDlgItemText(IDC_srcfile,resultFile);
				}
			}
			return;
		}
		if (IsDlgButtonChecked(IDC_RADIOfolderenc) == BST_CHECKED)//如果为文件夹解密
		  {
            
			 SetDlgItemText(IDC_destfile,folderoperate.openFloder());
			 GetDlgItemText(IDC_destfile,destfile,MAX_PATH);
			// GetDlgItemText(IDC_srcfile,resultFile,MAX_PATH);
				 //if(strlen(resultFile)==0)
				 //{
					 //strcat(resultFile,".enc");
					 SetDlgItemText(IDC_srcfile,destfile);
				// }
			 return;
		  }
	}

	
	return ;


}

//将密码框设置为空
void CblowfishencryptionDlg::wipePwds(char *pwd, char *verify)
{
	if (pwd != 0)		ZeroMemory(pwd, 57);
	if (verify != 0)	ZeroMemory(verify, 57);
}

//界面更新
void CblowfishencryptionDlg::OnBnClickedBtnsuaxin()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_EDITmima,0);
	SetDlgItemText(IDC_EDITquerenmima,0);
	SetDlgItemText(IDC_srcfile,0);
	SetDlgItemText(IDC_destfile,0);

}

//如果选择加密文件，设置相应按钮
void CblowfishencryptionDlg::OnBnClickedRadiojimi()
{
	// TODO: Add your control notification handler code here
   GetDlgItem(IDC_Btnchosesrcfile)->EnableWindow(true);//使明文路径选择按钮有效
   GetDlgItem(IDC_Btnchoosedestfile)->EnableWindow(false);//使密文路径选择按钮无效

}

//如果选择解密文件，设置相应按钮
void CblowfishencryptionDlg::OnBnClickedRadiojiemi()
{
	// TODO: Add your control notification handler code here
	 GetDlgItem(IDC_Btnchosesrcfile)->EnableWindow(false);//使明文路径选择按钮无效
	 GetDlgItem(IDC_Btnchoosedestfile)->EnableWindow(true);//使密文路径选择按钮有效
}

//如为blowfish，密钥2输入框无效
void CblowfishencryptionDlg::OnBnClickedRadioblowfish()
{
	// TODO: Add your control notification handler code here
	 GetDlgItem(IDC_EDITquerenmima)->EnableWindow(false);//使明文路径选择按钮无效

}


//如为blowfish，两个密钥输入框都有效
void CblowfishencryptionDlg::OnBnClickedRadio3des()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDITquerenmima)->EnableWindow(true);//使明文路径选择按钮无效
}


void CblowfishencryptionDlg::OnBnClickedLoginbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	Screat dlg;
	dlg.DoModal();
}


void CblowfishencryptionDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LonginButton.ShowWindow(SW_SHOW);
	
	m_logoutButton.ShowWindow(SW_HIDE);
	m_changeButton.ShowWindow(SW_HIDE);
	m_static_adminName.ShowWindow(SW_HIDE);
}


void CblowfishencryptionDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	Change dlg;
	dlg.DoModal();
}


void CblowfishencryptionDlg::OnBnClickedTwice()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CblowfishencryptionDlg::OnBnClickedButtonKeys()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//如果界面密钥为空，则自动生成密钥并保存
	if( m_editmima == "")
	{
		CString szKey2;
		srand(time(NULL));
		char name[LEN_NAME + 2];
		CRandom random;
		szKey2 = random.rand_str(name,LEN_NAME);
		if (IsDlgButtonChecked(IDC_RADIO3des) == BST_CHECKED || IsDlgButtonChecked(IDC_TWICE) == BST_CHECKED)
		{
			m_editmima = szKey2;
			m_editmima1 = szKey2;
		} else {
			m_editmima = szKey2;
		}
	}

	if(m_editmima1 == "")
	{
		m_editmima1 = m_editmima;
	}

	UpdateData(FALSE);

	//由于直接拼接密码和时间会使字符串出错
	//重新跟新一下界面,从界面中读取就不会出现此错误
	UpdateData(TRUE);
	
	  

	UpdateData(FALSE);

	CTime time; 
	time =CTime::GetCurrentTime();//获得当前时间 
	CString timeStr = time.Format("\r\n %Y-%m-%d %H:%M:%S ");

	//将字符串保存为 时间+密码
	CString str = _T("【密码】：");
	str =  timeStr + str ;
	str += m_editmima;

	CFile file( KEYFILE_NAME, CFile::modeNoTruncate| CFile::modeWrite);
	file.SeekToEnd();
	file.Write(str,strlen(str));
	file.Close();
}


void CblowfishencryptionDlg::OnBnClickedButtonOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T("notepad.exe ");
	str += KEYFILE_NAME;
	::WinExec(str, SW_SHOW);
}


void CblowfishencryptionDlg::OnBnClickedButtonLog()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	CString str = _T("notepad.exe ");
	str += KEYFILE_NAME;
	::WinExec(str, SW_SHOW);
	*/
}


void CblowfishencryptionDlg::OnBnClickedButtonDriver()
{
	// TODO: 在此添加控件通知处理程序代码
/**
	ShellExecute(
		NULL,
		"open",
		"sc",
		"start encryptengine",
		NULL,
		SW_HIDE
		);

*/

	CString csCaption;
	GetDlgItemText(IDC_BUTTON_DRIVER,csCaption);

	if(csCaption == "开启驱动")
	{
		SetDlgItemText(IDC_BUTTON_DRIVER,"关闭驱动");



		ShellExecute(
			NULL,
			"open",
			"sc",
			"start encryptengine",
			NULL,
			SW_HIDE
			);

	}

	if(csCaption == "关闭驱动")
	{
		SetDlgItemText(IDC_BUTTON_DRIVER,"开启驱动");
		ShellExecute(
			NULL,
			"open",
			"sc",
			"stop encryptengine",
			NULL,
			SW_HIDE
			);
	}

}
