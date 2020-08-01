// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySql.c.h"
#include "MyDlg.h"
#include "afxdialogex.h"


// CMyDlg 对话框

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


// CMyDlg 消息处理程序


void CMyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	char szsql[100] = {0};
	sprintf_s(szsql,"update user set username = '%s' where username = '%s';",m_edtuser,m_user);

	if(theApp.m_sql.UpdateMySql(szsql))
	{
		MessageBox("修改用户名 成功");
	}
}
