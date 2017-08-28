
// testudp2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"
#include <atomic> 


// Ctestudp2Dlg 对话框
class Ctestudp2Dlg : public CDialogEx
{
// 构造
public:
	Ctestudp2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTUDP2_DIALOG };

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
	afx_msg LRESULT OnUpdateInterface(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString m_str1;
	CString m_str2;
	CString m_str3;
	CString m_str4;
	CString m_str5;
	CString m_str11;
	CString m_str22;
	CString m_str33;
	CString m_str44;
	static void WINAPI OnRecv(char *pBuf, int nLen);
	static UINT RecvT(LPVOID pParam);
	static UINT SendT(LPVOID pParam);
private:
	static Ctestudp2Dlg *m_pThis;
	volatile bool m_bStop = false;
	std::atomic_int  m_nNum;
	std::atomic_int m_nData;
	std::atomic_int m_nNum2;
	std::atomic_int m_nData2;
	volatile unsigned int m_nValue = 0;
	CString m_strData;
	CMySocket m_st;
	void OnRecvI(char *pBuf, int nLen);
	void RecvI();
	void SendI();
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL DestroyWindow();
	CString m_strIp;
	UINT m_nPort;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	UINT m_nInterval;
	UINT m_nListerPort;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	UINT m_nSendNum;
public:
	void Lock(){ /*EnterCriticalSection(&m_lock); */}
	void UnLock(){/* LeaveCriticalSection(&m_lock); */}
private:
	// SRWLock的效率更高，但只有win7以上支持
	CRITICAL_SECTION m_lock;

	char m_buf[15];
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
