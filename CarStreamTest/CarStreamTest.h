
// CarStreamTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCarStreamTestApp:
// �йش����ʵ�֣������ CarStreamTest.cpp
//

class CCarStreamTestApp : public CWinAppEx
{
public:
	CCarStreamTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCarStreamTestApp theApp;