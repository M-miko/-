
// MySql.c.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include"CMySql.h"
 
// CMySqlcApp:
// �йش����ʵ�֣������ MySql.c.cpp
//

class CMySqlcApp : public CWinApp
{
public:
	CMySqlcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CMySql m_sql;
	virtual int ExitInstance();
};

extern CMySqlcApp theApp;