// Dlg3.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Dlg3.h"
#include "afxdialogex.h"
#include "mysql.h"
#include <string>
using namespace std;
// Dlg3 dialog
MYSQL sqlCon;
MYSQL_RES *res;
MYSQL_ROW newrow;
extern string Account;
IMPLEMENT_DYNAMIC(Dlg3, CDialogEx)

Dlg3::Dlg3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_data(_T(""))
	, name(_T(""))
	, grade(_T(""))
	, major(_T(""))
	, tel(_T(""))
{

}

Dlg3::~Dlg3()
{
}

void Dlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, my_list);
	DDX_Text(pDX, IDC_EDIT1, m_data);
	DDX_Text(pDX, IDC_EDIT2, name);
	DDX_Text(pDX, IDC_EDIT3, grade);
	DDX_Text(pDX, IDC_EDIT4, major);
	DDX_Text(pDX, IDC_EDIT5, tel);
}


BEGIN_MESSAGE_MAP(Dlg3, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Dlg3::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &Dlg3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dlg3::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg3::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Dlg3::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &Dlg3::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Dlg3::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT4, &Dlg3::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT2, &Dlg3::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &Dlg3::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, &Dlg3::OnEnChangeEdit5)
END_MESSAGE_MAP()


// Dlg3 message handlers


BOOL Dlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	my_list.GetClientRect(&rect);
	DWORD dwStyle = my_list.GetExtendedStyle();//添加网格线
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	my_list.SetExtendedStyle(dwStyle);
	my_list.ModifyStyle(0, LVS_REPORT);
	my_list.InsertColumn(0, _T("学号"), LVCFMT_LEFT, 110);//添加标签行
	my_list.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 110);
	my_list.InsertColumn(2, _T("年级"), LVCFMT_LEFT, 110);
	my_list.InsertColumn(3, _T("专业"), LVCFMT_LEFT, 110);
	my_list.InsertColumn(4, _T("电话"), LVCFMT_LEFT, 150);
	//my_list.InsertItem(0, _T("ja"));
	//my_list.SetItemText(0, 1, _T("电话"));
	mysql_init(&sqlCon);
	mysql_real_connect(&sqlCon, "localhost", "root", "", "test", 3306, NULL, 0);
	mysql_query(&sqlCon, "SET NAMES 'GB2312'");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Dlg3::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

}


void Dlg3::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	res = NULL;
	string s = "select * from student where id=";
	string data= CT2A(m_data.GetBuffer());
	s += data;
	const char *sql = s.data();
	mysql_real_query(&sqlCon, sql, (unsigned long)strlen(sql));
	res = mysql_store_result(&sqlCon);
	int i = 0;
	my_list.DeleteAllItems();
	while (newrow = mysql_fetch_row(res))
	{
		for (int j = 0; j < 5; j++)
		{
			CString mydata(newrow[j]);
			if(j==0) my_list.InsertItem(i, mydata);
			else my_list.SetItemText(i, j, mydata);
		}
		i++;
	}
	UpdateData(FALSE);
}


void Dlg3::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void Dlg3::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	res = NULL;
	string s = "select * from student where name='";
	string data = CT2A(m_data.GetBuffer());
	s += data+"'";
	const char *sql = s.data();
	if(!mysql_real_query(&sqlCon, sql, (unsigned long)strlen(sql)))
		res = mysql_store_result(&sqlCon);
	int i = 0;
	my_list.DeleteAllItems();
	while (newrow = mysql_fetch_row(res))
	{
		for (int j = 0; j < 5; j++)
		{
			CString mydata(newrow[j]);
			if (j == 0) my_list.InsertItem(i, mydata);
			else my_list.SetItemText(i, j, mydata);
		}
		i++;
	}
	UpdateData(FALSE);
}


void Dlg3::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dlg3::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	res = NULL;
	string s = "select * from student";
	const char *sql = s.data();
	if (!mysql_real_query(&sqlCon, sql, (unsigned long)strlen(sql)))
		res = mysql_store_result(&sqlCon);
	int i = 0;
	my_list.DeleteAllItems();
	while (newrow = mysql_fetch_row(res))
	{
		for (int j = 0; j < 5; j++)
		{
			CString mydata(newrow[j]);
			if (j == 0) my_list.InsertItem(i, mydata);
			else my_list.SetItemText(i, j, mydata);
		}
		i++;
	}
	UpdateData(FALSE);
}


void Dlg3::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	res = NULL;
	string s1 = "update student set name='";
	string s2 = "',grade ='";
	string s3 = "', major='";
	string s4 = "', tel='";
	string s5 = "' where id='";
	string sname = CT2A(name.GetBuffer());
	string sgrade= CT2A(grade.GetBuffer());
	string smajor= CT2A(major.GetBuffer());
	string stel= CT2A(tel.GetBuffer());
	s1 += sname + s2+sgrade+s3+smajor+s4+stel+s5+Account+"'";
	const char *sql = s1.data();
	if (!mysql_real_query(&sqlCon, sql, (unsigned long)strlen(sql)))
		res = mysql_store_result(&sqlCon);
	UpdateData(FALSE);
}


void Dlg3::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dlg3::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dlg3::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Dlg3::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
