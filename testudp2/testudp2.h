
// testudp2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctestudp2App: 
// �йش����ʵ�֣������ testudp2.cpp
//

class Ctestudp2App : public CWinApp
{
public:
	Ctestudp2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctestudp2App theApp;