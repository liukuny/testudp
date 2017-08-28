#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include "Stdio.h"
#include <iostream>

#define BUFSIZE     1024 //max size of incoming data buffer

#define DEFAULT_PORT			7125 

typedef struct
{
	OVERLAPPED	Overlapped;
	WSABUF		DataBuf;

	CHAR		Buffer[BUFSIZE];
	DWORD		nRecvLen;
	SOCKADDR_IN SAddr;
	//int			nFromAddrLen;
} stnIocpData, *pStnIocpData;

typedef struct
{
	u_short l_onoff;
	u_short l_linger;
}stnLinger;


////-----------------------------------------------------------------------------
//
//int main(int argc, char* argv[])
//{
//	InitWinsock2();
//
//	HANDLE hWait2Exit = CreateEvent(NULL, FALSE, TRUE, "MCLIENT");
//	ResetEvent(hWait2Exit);
//
//	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
//
//	if (!CreateNetSocket())
//	{
//		printf("Error condition @ CreateNetConnections  , exiting\n");
//		return 1;
//	}
//
//	SYSTEM_INFO SystemInfo;
//	GetSystemInfo(&SystemInfo);
//
//	if (!CreateWorkers(SystemInfo.dwNumberOfProcessors * 2))
//	{
//		printf("Error condition @CreateWorkers, exiting\n");
//		return 1;
//	}
//
//	WaitForSingleObject(hWait2Exit, INFINITE);
//
//	UnInitWinsock2();
//
//	return 1;
//}
//

// CMySocket ÃüÁîÄ¿±ê

typedef void (WINAPI *POnRecv)(char *pBuf, int nBufLen);

class CMySocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	bool Create(UINT16 nPort, CString strIp = L"0.0.0.0", POnRecv pOnRecv = 0, int nWorkTreadNum = 1);
	void Close();
private:
	SOCKET m_nSocket;
	HANDLE m_hIocp;
	pStnIocpData m_pPerIoData = 0;
	u_short m_nPort = 0;
	POnRecv m_pOnRecv;
	bool InitWinsock2();
	void UnInitWinsock2();
	bool CreateNetSocket(void);
	BOOL CreateWorkers(UINT uiCount);
	static UINT WorkerThreadT(LPVOID lpParam)
	{
		CMySocket *pThis = (CMySocket *)lpParam;
		return pThis->WorkerThread(pThis->m_hIocp);
	}	
	DWORD WorkerThread(LPVOID lpParam);
};


