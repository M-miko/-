
// MySql.cDlg.h : ͷ�ļ�
//

#pragma once


// CMySqlcDlg �Ի���
class CMySqlcDlg : public CDialogEx
{
// ����
public:
	CMySqlcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYSQLC_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CString m_edtuser;
	afx_msg void OnEnChangeEdit2();
	CString m_edtpassword;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
};
