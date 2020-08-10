
// customer-producerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "customer-producer.h"
#include "customer-producerDlg.h"
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


// CcustomerproducerDlg �Ի���



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


// CcustomerproducerDlg ��Ϣ�������

BOOL CcustomerproducerDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcustomerproducerDlg::OnPaint()
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
HCURSOR CcustomerproducerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcustomerproducerDlg::OnBnClickedButton2()
{
	SetEvent(m_Event);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		str.Format(_T("������%d��������%d"),GetCurrentThreadId(),nCurretNo);
		LeaveCriticalSection(&pthis->m_cs);
		pthis->m_lstcus.AddString(str);
	}
	return 0;
}

void CcustomerproducerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < 10; i++)
	{
		m_arrProducer[i] = CreateThread(NULL,0,&CcustomerproducerDlg::ThreadProcProducer,this,0,NULL);
		m_arrCustmer[i] = CreateThread(NULL,0,&CcustomerproducerDlg::ThreadProcCustemer,this,0,NULL);
	}
}


void CcustomerproducerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DeleteCriticalSection(&m_cs);
	CDialogEx::OnClose();
}



