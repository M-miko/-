
// customer-producerDlg.h : ͷ�ļ�
//

#pragma once
#define MAXSIZE 10
#include<queue>
#include "afxwin.h"
// CcustomerproducerDlg �Ի���
class CcustomerproducerDlg : public CDialogEx
{
// ����
public:
	CcustomerproducerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUSTOMERPRODUCER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
