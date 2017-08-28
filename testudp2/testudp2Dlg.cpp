
// testudp2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testudp2.h"
#include "testudp2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Ctestudp2Dlg *Ctestudp2Dlg::m_pThis = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctestudp2Dlg 对话框



Ctestudp2Dlg::Ctestudp2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctestudp2Dlg::IDD, pParent)
	, m_str1(_T("0"))
	, m_str2(_T("0"))
	, m_str3(_T("0"))
	, m_str4(_T("0"))
	, m_str5(_T(""))
	, m_str11(_T("0"))
	, m_str22(_T("0"))
	, m_str33(_T("0"))
	, m_str44(_T("0"))
	//, m_st(OnRecv)
	, m_strIp(_T("192.168.0.3"))
	, m_nPort(32768)
	, m_nInterval(0)
	, m_nListerPort(32768)
	, m_nSendNum(1000000)
{
	m_nNum = 0;
	m_nNum2 = 0;
	m_nData = 0;
	m_nData2 = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//InitializeCriticalSection(&m_lock);
}

void Ctestudp2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_1, m_str1);
	DDX_Text(pDX, IDC_STATIC_2, m_str2);
	DDX_Text(pDX, IDC_STATIC_3, m_str3);
	DDX_Text(pDX, IDC_STATIC_4, m_str4);
	DDX_Text(pDX, IDC_STATIC_5, m_str11);
	DDX_Text(pDX, IDC_STATIC_6, m_str22);
	DDX_Text(pDX, IDC_STATIC_7, m_str33);
	DDX_Text(pDX, IDC_STATIC_8, m_str44);
	DDX_Text(pDX, IDC_STATIC_9, m_str5);
	DDX_Text(pDX, IDC_EDIT1, m_strIp);
	DDX_Text(pDX, IDC_EDIT2, m_nPort);
	DDX_Text(pDX, IDC_EDIT3, m_nInterval);
	DDX_Text(pDX, IDC_EDIT4, m_nListerPort);
	DDX_Text(pDX, IDC_EDIT5, m_nSendNum);
}

BEGIN_MESSAGE_MAP(Ctestudp2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ctestudp2Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER + 10, OnUpdateInterface)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctestudp2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctestudp2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Ctestudp2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Ctestudp2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Ctestudp2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Ctestudp2Dlg::OnBnClickedButton7)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Ctestudp2Dlg 消息处理程序
LRESULT Ctestudp2Dlg::OnUpdateInterface(WPARAM wParam, LPARAM lParam)
{
	//CString strTmp;
	UpdateData();
	//if (0 == wParam)
	{
		m_str1.Format(L"%d", m_nNum);
		m_str2.Format(L"%d", m_nData);
		m_str5.Format(L"%d", m_nValue);
		m_str11.Format(L"%X", m_nNum);
		m_str22.Format(L"%X", m_nData);
		//GetDlgItem(IDC_STATIC_1)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str1) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_1)->SetWindowText(m_str1);
		//}
		//GetDlgItem(IDC_STATIC_2)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str2) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_2)->SetWindowText(m_str2);
		//}
		//GetDlgItem(IDC_STATIC_5)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str11) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_5)->SetWindowText(m_str11);
		//}
		//GetDlgItem(IDC_STATIC_6)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str22) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_6)->SetWindowText(m_str22);
		//}
		//GetDlgItem(IDC_STATIC_9)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str5) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_9)->SetWindowText(m_str5);
		//}

		//GetDlgItem(IDC_STATIC_2)->SetWindowText(m_str2);
		//GetDlgItem(IDC_STATIC_5)->SetWindowText(m_str11);
		//GetDlgItem(IDC_STATIC_6)->SetWindowText(m_str22);
		//GetDlgItem(IDC_STATIC_9)->SetWindowText(m_str5);
	}
	//else
	{
		m_str3.Format(L"%d", m_nNum2);
		m_str4.Format(L"%d", m_nData2);
		m_str33.Format(L"%X", m_nNum2);
		m_str44.Format(L"%X", m_nData2);
		//GetDlgItem(IDC_STATIC_3)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str3) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_3)->SetWindowText(m_str3);
		//}
		//GetDlgItem(IDC_STATIC_4)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str4) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_4)->SetWindowText(m_str4);
		//}
		//GetDlgItem(IDC_STATIC_7)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str33) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_7)->SetWindowText(m_str33);
		//}
		//GetDlgItem(IDC_STATIC_8)->GetWindowText(strTmp);
		//if (strTmp.Compare(m_str44) != 0)
		//{
		//	GetDlgItem(IDC_STATIC_8)->SetWindowText(m_str44);
		//}
		//GetDlgItem(IDC_STATIC_3)->SetWindowText(m_str3);
		//GetDlgItem(IDC_STATIC_4)->SetWindowText(m_str4);
		//GetDlgItem(IDC_STATIC_7)->SetWindowText(m_str33);
		//GetDlgItem(IDC_STATIC_8)->SetWindowText(m_str44);
}
	UpdateData(FALSE);
	return 1;
}

BOOL Ctestudp2Dlg::OnInitDialog()
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

	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	//::AfxBeginThread(RecvT, this);
	m_pThis = this;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctestudp2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctestudp2Dlg::OnPaint()
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
HCURSOR Ctestudp2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void WINAPI Ctestudp2Dlg::OnRecv(char *pBuf, int nLen)
{
	if (m_pThis)
	{
		m_pThis->OnRecvI(pBuf, nLen);
		//m_pThis->PostMessage(WM_USER + 10);
	}
	//((Ctestudp2Dlg *)::AfxGetApp()->GetMainWnd())->OnRecvI(nLen);
}

void Ctestudp2Dlg::OnRecvI(char *pBuf, int nLen)
{
	m_nNum += 1;
	m_nData += nLen;
	memcpy(m_buf, pBuf, 15);
	unsigned int nValue;// = (unsigned int)(*((unsigned int *)pBuf));
	memcpy(&nValue, m_buf, 4);
	if (nValue - m_nValue > 1)
	{
		// 丢包了
		//::MessageBeep(10);
	}
	m_nValue = nValue;
}

// 清零
void Ctestudp2Dlg::OnBnClickedButton1()
{
	UpdateData();
	m_nNum = 0;
	m_nData = 0;
	m_nValue = 0;
	m_str1.Format(L"%d", m_nNum);
	m_str2.Format(L"%d", m_nData);
	m_str5.Empty();
	m_str11.Format(L"%d", m_nNum);
	m_str22.Format(L"%d", m_nData);
	UpdateData(FALSE);
}

UINT Ctestudp2Dlg::RecvT(LPVOID pParam)
{
	Ctestudp2Dlg *pThis = (Ctestudp2Dlg *)pParam;
	pThis->RecvI();
	return 1;
}

UINT Ctestudp2Dlg::SendT(LPVOID pParam)
{
	Ctestudp2Dlg *pThis = (Ctestudp2Dlg *)pParam;
	pThis->SendI();
	return 1;
}

void Ctestudp2Dlg::RecvI()
{
	//AfxSocketInit();
	//if (!m_st.Create(32768, SOCK_DGRAM, 0))
	//{
	//	MessageBox(L"创建失败！！！");
	//	exit(1);
	//}
	//const int nLen = 1024;
	//CString strFromIp;
	//UINT nFromPort;
	//char buf[nLen] = { 0 };
	//while (1)
	//{
	//	int nRecv = m_st.ReceiveFrom(buf, nLen, strFromIp, nFromPort);
	//	if (nRecv > 0)
	//	{
	//		if (nRecv == 5)
	//		{
	//			if (buf[0] == 'c' && buf[1] == 'l' && buf[2] == 'o' && buf[3] == 's' && buf[4] == 'e')
	//			{
	//				break;
	//			}
	//		}
	//		m_nNum += 1;
	//		m_nData += nRecv;
	//		//SendMessage(WM_USER + 10);
	//		PostMessage(WM_USER + 10);
	//		Sleep(1);
	//		continue;
	//	}
	//	break;
	//}
	//m_st.Close();
}

void Ctestudp2Dlg::SendI()
{
	CString strIp = m_strIp;
	UINT nPort = m_nPort;
	UINT nInterval = m_nInterval;
	UINT nSendNum = m_nSendNum;
	AfxSocketInit();
	CSocket st;
	if (!st.Create(0, SOCK_DGRAM))
	{
		MessageBox(L"监听失败！！！");
		exit(1);
	}
	const int nLen = 15;
	UINT nSeri = 1;
	char buf[nLen] = { 0 };
	if (nSendNum == 0)
	{
		nSendNum = 0xFFFFFFFF;
	}
	for (int i = 0; i < nSendNum; i++)
	{
		if (m_bStop)
		{
			break;
		}
		memcpy(buf, &nSeri, sizeof(nSeri));
		int nSend = st.SendTo(buf, nLen, nPort, strIp);
		if (nSend > 0)
		{
			m_nNum2 += 1;
			m_nData2 += nSend;
			//SendMessage(WM_USER + 10);
			//PostMessage(WM_USER + 10, 1);
			if (m_nInterval > 0)
			{
				Sleep(m_nInterval);
			}
		}
		nSeri++;
	}
	st.Close();
}


BOOL Ctestudp2Dlg::DestroyWindow()
{
	OnBnClickedButton4();
	// TODO:  在此添加专用代码和/或调用基类
	//CSocket st;
	//if (st.Create(0, SOCK_DGRAM))
	//{
	//	st.SendTo("close", 5, 32768, L"127.0.0.1");
	//	Sleep(100);
	//}
	//st.Close();
	//DeleteCriticalSection(&m_lock);
	return CDialogEx::DestroyWindow();
}

// 发送一次
void Ctestudp2Dlg::OnBnClickedButton2()
{
	UpdateData();
	// TODO:  在此添加专用代码和/或调用基类
	CSocket st;
	if (st.Create(0, SOCK_DGRAM))
	{
		st.SendTo("000000000000000", 15, m_nPort, m_strIp);
	}
	st.Close();
}


// 连续发送
void Ctestudp2Dlg::OnBnClickedButton3()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
	m_bStop = false;
	::AfxBeginThread(SendT, this);
}

// 停止
void Ctestudp2Dlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_bStop = true;
}

// 清空
void Ctestudp2Dlg::OnBnClickedButton5()
{
	m_nNum2 = 0;
	m_nData2 = 0;
	PostMessage(WM_USER + 10, 1);
	// TODO:  在此添加控件通知处理程序代码
}

// 监听
void Ctestudp2Dlg::OnBnClickedButton6()
{
	// TODO:  在此添加额外的初始化代码32768
	UpdateData();
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	int nCpu = SystemInfo.dwNumberOfProcessors;// *2;
	
	CString strTitle;
	CString strTitle2;
	GetWindowText(strTitle);
	strTitle2.Format(L"%s - %d", strTitle.GetBuffer(), nCpu);
	SetWindowText(strTitle2);
	if (!m_st.Create(m_nListerPort, L"0.0.0.0", OnRecv, nCpu))
	{
		MessageBox(L"监听失败！！！");
		//exit(1);
	}
	else
	{
		GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
		SetTimer(1, 20, 0);
	}

}


void Ctestudp2Dlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	m_st.Close();
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
}


void Ctestudp2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	KillTimer(nIDEvent);
	if (nIDEvent == 1)
	{
		PostMessage(WM_USER + 10);
	}
	SetTimer(1, 20, 0);
	CDialogEx::OnTimer(nIDEvent);
}
