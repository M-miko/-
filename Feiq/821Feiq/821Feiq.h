
// 821Feiq.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "UDPMediator.h"

// CMy821FeiqApp:
// �йش����ʵ�֣������ 821Feiq.cpp
//

class CMy821FeiqApp : public CWinApp
{
public:
	CMy821FeiqApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	IMediator *m_pMediator;
	virtual int ExitInstance();
};

extern CMy821FeiqApp theApp;