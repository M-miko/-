
// 821FeiqDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "821Feiq.h"
#include "821FeiqDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy821FeiqDlg �Ի���



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


// CMy821FeiqDlg ��Ϣ�������

LRESULT CMy821FeiqDlg::DataInfoMsg(WPARAM W,LPARAM L)
{
	char *szbuf = (char*)W;
	in_addr  addr;
	addr.S_un.S_addr = L;
	char *szip = inet_ntoa(addr);
	//�ж�Ip ��û�д��ڣ����û�У��������ڣ�
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_lstip.InsertColumn(0,_T("�������"),0,150);
	m_lstip.InsertColumn(1,_T("IP"),0,150);

	m_lstip.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(!theApp.m_pMediator->Open())
	{
		MessageBox(_T("����������ʧ��"));
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy821FeiqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy821FeiqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy821FeiqDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	theApp.m_pMediator->Close();
	CDialogEx::OnClose();
}


void CMy821FeiqDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰѡ���ip
	int nIndex =   m_lstip.GetSelectionMark();
	if(nIndex == -1)return;

   CString  strip =	m_lstip.GetItemText(nIndex,1);

    GetDlg(strip);
	//��������
	


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
