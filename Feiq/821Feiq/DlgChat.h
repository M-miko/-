#pragma once
#include "afxwin.h"


// CDlgChat �Ի���

class CDlgChat : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChat)

public:
	CDlgChat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChat();

// �Ի�������
	enum { IDD = IDD_DLG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstContent;
	CString m_edtSend;
	afx_msg void OnBnClickedButton1();
};
