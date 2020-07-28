#pragma once
#include "sys.h"
class CGunner
{
public:
	CGunner(void);
	~CGunner(void);
public:
	HBITMAP m_hBmpGunner;
	int x;
	int y;
public:
	void GunnerInit(HINSTANCE hIns, int x1, int y2);
	void GunnerMove();
	void GunnerShow(HDC hdc);
};

