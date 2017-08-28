// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "testudp2.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
	Close();
	UnInitWinsock2();
}

// CMySocket 成员函数

bool CMySocket::Create(UINT16 nPort, CString strIp, POnRecv pOnRecv, int nWorkTreadNum)
{
	m_nPort = nPort;
	m_pOnRecv = pOnRecv;
	if (!InitWinsock2())
	{
		return false;
	}
	
	if (!CreateNetSocket())
	{
		return false;
	}
	
	if (!CreateWorkers(nWorkTreadNum))
	{
		return false;
	}
	
	return true;
}

void CMySocket::Close()
{
	CloseHandle(m_hIocp);
	m_hIocp = 0;
	closesocket(m_nSocket);
	m_nSocket = 0;
	if (m_pPerIoData)
	{
		delete m_pPerIoData;
		m_pPerIoData = 0;
	}
}


bool CMySocket::InitWinsock2()
{
	WSADATA data;
	WORD version;
	int ret = 0;

	version = (MAKEWORD(2, 2));
	ret = WSAStartup(version, &data);
	if (ret != 0)
	{
		ret = WSAGetLastError();
		if (ret == WSANOTINITIALISED)
		{
			return false;
		}
	}
	return true;
}

void CMySocket::UnInitWinsock2()
{
	WSACleanup();
}

bool CMySocket::CreateNetSocket(void)
{
	BOOL fFlag = TRUE;
	int nRet = 0;
	SOCKADDR_IN stLclAddr;

	m_nSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_nSocket == INVALID_SOCKET)
	{
		//printf("socket() failed, Err: %d\n", WSAGetLastError());
		return false;
	}


	//nRet = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&fFlag, sizeof(fFlag));
	//if (nRet == SOCKET_ERROR)
	//{
	//		printf("setsockopt() SO_REUSEADDR failed, Err: %d\n", WSAGetLastError());
	//}

	/*
	stnLinger Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;
	*/

	/*
	struct linger lng;
	lng.l_onoff = 0;

	nRet = setsockopt(g_hSocket,SOL_SOCKET,SO_LINGER, (char*)&lng, sizeof(lng));
	if (nRet == SOCKET_ERROR)
	{
	nRet = WSAGetLastError();
	printf ("setsockopt() SO_REUSEADDR failed, Err: %d\n",WSAGetLastError());
	}
	*/

	int iOptVal = 0;
	int iOptLen = sizeof(int);
	nRet = getsockopt(m_nSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iOptVal, &iOptLen);
	iOptVal = 20 * 1024 * 1024;
	nRet = setsockopt(m_nSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&iOptVal, iOptLen);
	iOptVal = 1 * 1024 * 1024;
	nRet = setsockopt(m_nSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&iOptVal, iOptLen);


	stLclAddr.sin_family = AF_INET;
	stLclAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	stLclAddr.sin_port = htons(m_nPort);
	nRet = bind(m_nSocket, (struct sockaddr*) &stLclAddr, sizeof(stLclAddr));
	if (nRet == SOCKET_ERROR)
	{
		//printf("bind() port: %d failed, Err: %d\n", m_nPort, WSAGetLastError());
		return false;
	}

	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 300000);
	if (!m_hIocp)
	{
		::AfxMessageBox(L"1");
		//fprintf(stdout, "g_hCompletionPort Create Failed\n");
		return false;
	}

	CreateIoCompletionPort((HANDLE)m_nSocket, m_hIocp, (DWORD)m_nSocket, 0);

	if ((m_pPerIoData = new stnIocpData()) == NULL)
	{
		//printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return false;
	}

	ZeroMemory(&(m_pPerIoData->Overlapped), sizeof(OVERLAPPED));
	m_pPerIoData->DataBuf.len = BUFSIZE;
	m_pPerIoData->DataBuf.buf = m_pPerIoData->Buffer;

	DWORD Flags = 0;
	DWORD RecvBytes;

	int iLen = sizeof(m_pPerIoData->SAddr);
	if (WSARecvFrom(m_nSocket, &(m_pPerIoData->DataBuf), 1, &m_pPerIoData->nRecvLen, &Flags, (sockaddr*)&(m_pPerIoData->SAddr), &iLen, (LPWSAOVERLAPPED)m_pPerIoData, NULL) == SOCKET_ERROR)
	{
		int nErr = WSAGetLastError();
		if (nErr != ERROR_IO_PENDING)
		{
			//printf("WSARecv() failed with error %d\n", WSAGetLastError());
			return false;
		}
	}

	return true;
}

BOOL CMySocket::CreateWorkers(UINT uiCount)
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	DWORD i;

	for (i = 0; i < uiCount; i++)
	{
		::AfxBeginThread(WorkerThreadT, this);
		//ThreadHandle = CreateThread(NULL, 0, WorkerThreadT, m_hIocp, 0, &ThreadId);
		//if (!ThreadHandle)
		//{
		//	fprintf(stdout, "Create Worker Thread Failed\n");
		//	return FALSE;
		//}

		//CloseHandle(ThreadHandle);
	}

	return TRUE;
}

DWORD CMySocket::WorkerThread(LPVOID lpParam)
{

	HANDLE CompletionPort = (HANDLE)lpParam;
	DWORD BytesTransferred;
	//LPOVERLAPPED Overlapped;
	//memset(&Overlapped, 0, sizeof(Overlapped));
	pStnIocpData PerIoData;
	DWORD RecvBytes;
	DWORD Flags;
	DWORD nSocket;
	DWORD nId;

	while (TRUE)
	{
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred, &nSocket, (LPOVERLAPPED *)&PerIoData, INFINITE) == 0)
		{
			//printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			//::AfxMessageBox(L"1");
			return 0;
		}
		nId = ::GetCurrentThreadId();
		if (BytesTransferred == 0)
		{
			//::AfxMessageBox(L"2");
			return 0;
		}
		if (BytesTransferred > 15)
		{
			//::AfxMessageBox(L"3");
			return 0;
		}

		/*
		BytesTransferred = 0;
		cout << "nSocket = " << nSocket << endl;

		cout << "接收的数据: " << PerIoData->DataBuf.buf
		<< "长度: " << PerIoData->DataBuf.len << endl;
		*/

		char		Buffer[BUFSIZE];
		memcpy(Buffer, PerIoData->DataBuf.buf, BUFSIZE);


		Flags = 0;
		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));

		PerIoData->DataBuf.len = BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;

		int iLen = sizeof(PerIoData->SAddr);
		//if (WSARecvFrom(nSocket, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags, (sockaddr*)&(PerIoData->SAddr), &iLen, &(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		if (WSARecvFrom(nSocket, &(PerIoData->DataBuf), 1, &PerIoData->nRecvLen, &Flags, (sockaddr*)&(PerIoData->SAddr), &iLen, (LPWSAOVERLAPPED)PerIoData, NULL) == SOCKET_ERROR)
		{
			int nErr = WSAGetLastError();
			if (nErr != ERROR_IO_PENDING)
			{
				::AfxMessageBox(L"4");
				//printf("WSARecv() failed with error %d\n", WSAGetLastError());
				return 0;
			}
			//if (WSAGetLastError() == 10054)
			//{
			//	WSARecvFrom(nSocket, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags, (sockaddr*)&(PerIoData->SAddr), &iLen, &(PerIoData->Overlapped), NULL);
			//}
		}

		if (m_pOnRecv)
		{
			m_pOnRecv(PerIoData->DataBuf.buf, BytesTransferred);
		}
	}

	return 0;

}
