
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "winsock.h"  
#include "mysql.h" 
#include "Dlg3.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
MYSQL m_sqlCon;
MYSQL_RES *m_res;
MYSQL_ROW row;
bool isadmin;
string Account;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, account(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, account);
	DDX_Text(pDX, IDC_EDIT2, password);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LOGIN, &CMFCApplication1Dlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SIGN, &CMFCApplication1Dlg::OnBnClickedSign)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication1Dlg::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "", "test", 3306, NULL, 0))
	{
		MessageBox(_T("失败"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	mysql_init(&m_sqlCon);
	// localhost:服务器 root为账号 test为数据库名 3306为端口  
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "", "test", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		const char *e = mysql_error(&m_sqlCon);
		MessageBox(_T("失败"));
		return;
	}
	else
	{
		AfxMessageBox(_T("成功!"));
	}
}


void CMFCApplication1Dlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_res = NULL;
	mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");
	string s = "select * from regesiter";
	const char *newsql = s.data();
	mysql_real_query(&m_sqlCon, newsql, (unsigned long)strlen(newsql));
	m_res = mysql_store_result(&m_sqlCon);
	bool isLogin = false;
	while (row = mysql_fetch_row(m_res))
	{
		if (account == row[0] && password == row[1])
			isLogin = true;
	}
	if (isLogin)
	{
		Account = CT2A(account.GetBuffer());
		Dlg3 dlg3;
		dlg3.DoModal();
	}
	else
	{
		MessageBox(_T("错误！"));
	}
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//mysql_close(&m_sqlCon);
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnBnClickedSign()
{
	// TODO: Add your control notification handler code here
	mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");
	UpdateData(TRUE);
	string sql = "insert into regesiter values(";
	string a = CT2A(account.GetBuffer());
	string b = CT2A(password.GetBuffer());
	sql += a + "," + b + ")";
	const char *newsql = sql.data();
	string sql2 = "insert into student(id) value('";
	sql2 += a + "')";
	const char *newsql2 = sql2.data();
	if(!mysql_real_query(&m_sqlCon, newsql, (unsigned long)strlen(newsql)))
		if(!mysql_real_query(&m_sqlCon, newsql2, (unsigned long)strlen(newsql2)))
			MessageBox(_T("注册成功！"));
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplication1Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplication1Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
