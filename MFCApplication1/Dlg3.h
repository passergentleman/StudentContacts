#pragma once
#include "afxcmn.h"


// Dlg3 dialog
//extern string Account;
class Dlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg3)

public:
	Dlg3(CWnd* pParent = NULL);   // standard constructor
	virtual ~Dlg3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl my_list;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CString m_data;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit5();
	CString name;
	CString grade;
	CString major;
	CString tel;
};
