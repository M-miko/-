// MyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySql.c.h"
#include "MyDlg.h"
#include "afxdialogex.h"


// CMyDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDlg, CDialogEx)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlg::IDD, pParent)
	, m_edtuser(_T(""))
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edtuser);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyDlg ��Ϣ�������


void CMyDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	char szsql[100] = {0};
	sprintf_s(szsql,"update user set username = '%s' where username = '%s';",m_edtuser,m_user);

	if(theApp.m_sql.UpdateMySql(szsql))
	{
		MessageBox("�޸��û��� �ɹ�");
	}
}
