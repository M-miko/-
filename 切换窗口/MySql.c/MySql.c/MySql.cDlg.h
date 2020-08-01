
// MySql.cDlg.h : 头文件
//

#pragma once


// CMySqlcDlg 对话框
class CMySqlcDlg : public CDialogEx
{
// 构造
public:
	CMySqlcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSQLC_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CString m_edtuser;
	afx_msg void OnEnChangeEdit2();
	CString m_edtpassword;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
};
