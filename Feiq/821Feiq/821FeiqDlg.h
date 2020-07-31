
// 821FeiqDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DlgChat.h"
#include <map>

// CMy821FeiqDlg �Ի���
class CMy821FeiqDlg : public CDialogEx
{
// ����
public:
	CMy821FeiqDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY821FEIQ_DIALOG };

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
	LRESULT OnLineMsg(WPARAM W,LPARAM L);
	LRESULT OffLineMsg(WPARAM W,LPARAM L);
	LRESULT DataInfoMsg(WPARAM W,LPARAM L);
	afx_msg void OnClose();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CDlgChat * GetDlg(CString strip);
	DECLARE_MESSAGE_MAP()

public:
	
	CListCtrl m_lstip;
	
	std::map<CString,CDlgChat*> m_mapIpToDlg;
};
