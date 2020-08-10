
// customer-producerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "customer-producer.h"
#include "customer-producerDlg.h"
#include "afxdialogex.h"

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


// CcustomerproducerDlg 对话框



CcustomerproducerDlg::CcustomerproducerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcustomerproducerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bFlagQuit = true;
	InitializeCriticalSection(&m_cs);
	nNum = 0;
	m_Event = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_Semaphore = CreateSemaphore(NULL,0,100,NULL);

	
}

void CcustomerproducerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstcus);
	//DDX_Control(pDX, IDC_LIST2, m_lstpro);
}

BEGIN_MESSAGE_MAP(CcustomerproducerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcustomerproducerDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CcustomerproducerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CcustomerproducerDlg 消息处理程序

BOOL CcustomerproducerDlg::OnInitDialog()
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

void CcustomerproducerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcustomerproducerDlg::OnPaint()
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
HCURSOR CcustomerproducerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcustomerproducerDlg::OnBnClickedButton2()
{
	SetEvent(m_Event);
	// TODO: 在此添加控件通知处理程序代码
}

DWORD WINAPI CcustomerproducerDlg::ThreadProcProducer(LPVOID lpParameter)
{
	CcustomerproducerDlg *pthis = (CcustomerproducerDlg*)lpParameter;

	WaitForSingleObject(pthis->m_Event,INFINITE);
	while (1)
	{
		if (pthis->nNum<100)
		{
			if (!TryEnterCriticalSection(&pthis->m_cs))
			{
				continue; 
			}
			pthis->nNum++;
			pthis->Count.push(pthis->nNum);
			LeaveCriticalSection(&pthis->m_cs);
			ReleaseSemaphore(pthis->m_Semaphore,1,NULL);
		}
		else
		{
			break;
		}
	}
	return 0;
}

DWORD WINAPI CcustomerproducerDlg::ThreadProcCustemer(LPVOID lpParameter)
{
	CcustomerproducerDlg* pthis = (CcustomerproducerDlg*)lpParameter;
	CString str;
	int nCurretNo;
	while (1)
	{
		WaitForSingleObject(pthis->m_Semaphore,INFINITE);
		EnterCriticalSection(&pthis->m_cs);
		nCurretNo = pthis->Count.front();
		pthis->Count.pop();
		str.Format(_T("消费者%d正在消费%d"),GetCurrentThreadId(),nCurretNo);
		LeaveCriticalSection(&pthis->m_cs);
		pthis->m_lstcus.AddString(str);
	}
	return 0;
}

void CcustomerproducerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < 10; i++)
	{
		m_arrProducer[i] = CreateThread(NULL,0,&CcustomerproducerDlg::ThreadProcProducer,this,0,NULL);
		m_arrCustmer[i] = CreateThread(NULL,0,&CcustomerproducerDlg::ThreadProcCustemer,this,0,NULL);
	}
}


void CcustomerproducerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DeleteCriticalSection(&m_cs);
	CDialogEx::OnClose();
}



