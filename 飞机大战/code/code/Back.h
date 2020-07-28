#pragma once
#include "Sys.h"

class CBack
{
public:
	HBITMAP m_hBmpBackDown;
	HBITMAP m_hBmpBackUp;
	int x;
	int y;
public:
	CBack(void);
	~CBack(void);
public:
	void BackInit(HINSTANCE hIns);
	void BackMove();
	void BackShow(HDC hdc);
};

