// DlgChat.cpp : 实现文件
//

#include "stdafx.h"
#include "821Feiq.h"
#include "DlgChat.h"
#include "afxdialogex.h"


// CDlgChat 对话框

IMPLEMENT_DYNAMIC(CDlgChat, CDialogEx)

CDlgChat::CDlgChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChat::IDD, pParent)
	, m_edtSend(_T(""))
{

}

CDlgChat::~CDlgChat()
{
}

void CDlgChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstContent);
	DDX_Text(pDX, IDC_EDIT1, m_edtSend);
}


BEGIN_MESSAGE_MAP(CDlgChat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgChat::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgChat 消息处理程序


void CDlgChat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strip;
	GetWindowText(strip);
	UpdateData(); 
	STRU_DATAINFO_RQ sdr;
	sdr.m_nType = DEF_PROTOCOL_DATAINFO_RQ;
	strcpy_s(sdr.m_szBuffer,sizeof(sdr.m_szBuffer),m_edtSend);
	sdr.m_nSeq  =0;
	
	if(theApp.m_pMediator->SendData(inet_addr(strip),(char*)&sdr,sizeof(sdr)))
	{
		m_lstContent.AddString("I Say:");
		m_lstContent.AddString(m_edtSend);

		m_edtSend = "";
		UpdateData(FALSE);
	}

}
