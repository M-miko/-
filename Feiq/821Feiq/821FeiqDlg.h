
// 821FeiqDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgChat.h"
#include <map>

// CMy821FeiqDlg 对话框
class CMy821FeiqDlg : public CDialogEx
{
// 构造
public:
	CMy821FeiqDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY821FEIQ_DIALOG };

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
