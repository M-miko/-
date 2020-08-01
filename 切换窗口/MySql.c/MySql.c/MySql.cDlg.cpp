
// MySql.cDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySql.c.h"
#include "MySql.cDlg.h"
#include "afxdialogex.h"
#include"MyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMySqlcDlg 对话框



CMySqlcDlg::CMySqlcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySqlcDlg::IDD, pParent)
	, m_edtuser(_T("刘淼"))
	, m_edtpassword(_T("123521"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySqlcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edtuser);
	DDX_Text(pDX, IDC_EDIT2, m_edtpassword);
}

BEGIN_MESSAGE_MAP(CMySqlcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMySqlcDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CMySqlcDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMySqlcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMySqlcDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMySqlcDlg 消息处理程序

BOOL CMySqlcDlg::OnInitDialog()
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

void CMySqlcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMySqlcDlg::OnPaint()
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
HCURSOR CMySqlcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMySqlcDlg::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szsql[100] = {0};
	//WideCharToMultiByte();
	sprintf_s(szsql,"insert into user values('%s','%s');",m_edtuser,m_edtpassword);

	if(theApp.m_sql.UpdateMySql(szsql))
	{
		MessageBox("注册成功");
	}
}


void CMySqlcDlg::OnEnChangeEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szsql[100] = {0};
	list<string> lststr;
	sprintf_s(szsql,"select userpassword  from user where username = '%s';",m_edtuser);

	theApp.m_sql.SelectMySql(szsql,1,lststr);

	if(lststr.size() >0)
	{
		string  strpassword = lststr.front();
		lststr.pop_front();

		if(0 == strcmp(m_edtpassword,strpassword.c_str()))
		{
			//MessageBox("登录成功");
			
			EndDialog(IDOK);
			CMyDlg dlg;
			//dlg.m_duser = this->m_edtuser; //记录登录的用户名
			theApp.m_pMainWnd = &dlg;
			dlg.DoModal();
		}

	}
}


void CMySqlcDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szsql[100] = {0};
	list<string> lststr;
	sprintf_s(szsql,"select userpassword  from user where username = '%s';",m_edtuser);

	theApp.m_sql.SelectMySql(szsql,1,lststr);

	if(lststr.size() >0)
	{
		string  strpassword = lststr.front();
		lststr.pop_front();

		if(0 == strcmp(m_edtpassword,strpassword.c_str()))
		{
			//MessageBox("登录成功");
			
			EndDialog(IDOK);
			CMyDlg dlg;
			dlg.m_user = this->m_edtuser; //记录登录的用户名
			theApp.m_pMainWnd = &dlg;
			dlg.DoModal();
		}

	}
}


void CMySqlcDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
