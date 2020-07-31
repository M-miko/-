
// 821FeiqDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "821Feiq.h"
#include "821FeiqDlg.h"
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


// CMy821FeiqDlg 对话框



CMy821FeiqDlg::CMy821FeiqDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy821FeiqDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy821FeiqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstip);
}

BEGIN_MESSAGE_MAP(CMy821FeiqDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(UM_ONLINEMSG,&CMy821FeiqDlg::OnLineMsg)
	ON_MESSAGE(UM_OFFLINEMSG,&CMy821FeiqDlg::OffLineMsg)
	ON_MESSAGE(UM_DATAINFOMSG,&CMy821FeiqDlg::DataInfoMsg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMy821FeiqDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CMy821FeiqDlg 消息处理程序

LRESULT CMy821FeiqDlg::DataInfoMsg(WPARAM W,LPARAM L)
{
	char *szbuf = (char*)W;
	in_addr  addr;
	addr.S_un.S_addr = L;
	char *szip = inet_ntoa(addr);
	//判断Ip 有没有窗口，如果没有，创建窗口，
	CDlgChat *pDlg = GetDlg(szip);
	CString str = szip;
	 str += "Say:";
	pDlg->m_lstContent.AddString(str);
	pDlg->m_lstContent.AddString(szbuf);
	return 0;
}

LRESULT CMy821FeiqDlg::OffLineMsg(WPARAM W,LPARAM L)
{
	in_addr  addr;
	addr.S_un.S_addr = L;
	char *szip = inet_ntoa(addr);
	CString strip;
	for(int i =0 ;i < m_lstip.GetItemCount();i++)
	{
		strip = m_lstip.GetItemText(i,1);
		if(strip == szip)
		{
			m_lstip.DeleteItem(i);
			break;
		}
	}

	return 0;
}
LRESULT CMy821FeiqDlg::OnLineMsg(WPARAM W,LPARAM L)
{
	in_addr  addr;
	addr.S_un.S_addr = L;
	char *szname = (char*)W;
	char *szip = inet_ntoa(addr);
	//l --ip
	m_lstip.InsertItem(0,szname);
	m_lstip.SetItemText(0,1,szip);
	return 0;
}

BOOL CMy821FeiqDlg::OnInitDialog()
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

	m_lstip.InsertColumn(0,_T("计算机名"),0,150);
	m_lstip.InsertColumn(1,_T("IP"),0,150);

	m_lstip.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// TODO: 在此添加额外的初始化代码
	if(!theApp.m_pMediator->Open())
	{
		MessageBox(_T("服务器启动失败"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy821FeiqDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy821FeiqDlg::OnPaint()
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
HCURSOR CMy821FeiqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy821FeiqDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	theApp.m_pMediator->Close();
	CDialogEx::OnClose();
}


void CMy821FeiqDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: 在此添加控件通知处理程序代码
	//获取当前选择的ip
	int nIndex =   m_lstip.GetSelectionMark();
	if(nIndex == -1)return;

   CString  strip =	m_lstip.GetItemText(nIndex,1);

    GetDlg(strip);
	//弹出窗口
	


	*pResult = 0;
}

CDlgChat * CMy821FeiqDlg::GetDlg(CString strip)
{
	 CDlgChat *pDlgChat = m_mapIpToDlg[strip];
	if(!pDlgChat)
	{
		pDlgChat = new CDlgChat;
		pDlgChat->Create(IDD_DLG_CHAT);
		
		m_mapIpToDlg[strip] = pDlgChat;
		
		pDlgChat->SetWindowText(strip);
	}
	pDlgChat->ShowWindow(SW_SHOW);

	return pDlgChat;
}
