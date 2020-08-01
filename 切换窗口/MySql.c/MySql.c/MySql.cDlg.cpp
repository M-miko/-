
// MySql.cDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySql.c.h"
#include "MySql.cDlg.h"
#include "afxdialogex.h"
#include"MyDlg.h"
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


// CMySqlcDlg �Ի���



CMySqlcDlg::CMySqlcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySqlcDlg::IDD, pParent)
	, m_edtuser(_T("���"))
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


// CMySqlcDlg ��Ϣ�������

BOOL CMySqlcDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMySqlcDlg::OnPaint()
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
HCURSOR CMySqlcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMySqlcDlg::OnBnClickedButton1()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char szsql[100] = {0};
	//WideCharToMultiByte();
	sprintf_s(szsql,"insert into user values('%s','%s');",m_edtuser,m_edtpassword);

	if(theApp.m_sql.UpdateMySql(szsql))
	{
		MessageBox("ע��ɹ�");
	}
}


void CMySqlcDlg::OnEnChangeEdit2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//MessageBox("��¼�ɹ�");
			
			EndDialog(IDOK);
			CMyDlg dlg;
			//dlg.m_duser = this->m_edtuser; //��¼��¼���û���
			theApp.m_pMainWnd = &dlg;
			dlg.DoModal();
		}

	}
}


void CMySqlcDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//MessageBox("��¼�ɹ�");
			
			EndDialog(IDOK);
			CMyDlg dlg;
			dlg.m_user = this->m_edtuser; //��¼��¼���û���
			theApp.m_pMainWnd = &dlg;
			dlg.DoModal();
		}

	}
}


void CMySqlcDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
