
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton2();
	bool isAdmin;
	bool isStudent;
	CString account;
	CString password;
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSign();
	afx_msg void OnEnChangeEdit1();
	CListCtrl newlist;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString mydata;
	afx_msg void OnEnChangeEdit3();
	int newdata;
	int data2;
	int mm;
	CString new_data;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit2();
};
