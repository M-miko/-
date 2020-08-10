
// customer-producerDlg.h : 头文件
//

#pragma once
#define MAXSIZE 10
#include<queue>
#include "afxwin.h"
// CcustomerproducerDlg 对话框
class CcustomerproducerDlg : public CDialogEx
{
// 构造
public:
	CcustomerproducerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CUSTOMERPRODUCER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	static DWORD WINAPI ThreadProcProducer(LPVOID lpParameter);
	static DWORD WINAPI ThreadProcCustemer(LPVOID lpParameter);
	afx_msg void OnBnClickedButton1();

	CRITICAL_SECTION m_cs;
	BOOL m_bFlagQuit;
	int nNum;
	HANDLE m_Event;
	HANDLE m_arrProducer[MAXSIZE];
	HANDLE m_arrCustmer[MAXSIZE];
	HANDLE m_Semaphore;
	std::queue<int>Count;
	afx_msg void OnClose();
	CListBox m_lstcus;
	CListBox m_lstpro;
	afx_msg void OnBnClickedButton2();
};
