#pragma once
#include "Sys.h"
#include "GunnerBox.h"

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);
public:
	HBITMAP m_hBmpPlayer;
	int m_nGunnerStyle;
	int x;
	int y;
public:
	void PlayerInit(HINSTANCE hIns);
	void PlayerMove(int FX);
	void PlayerShow(HDC hdc);
	void SendGunner(HINSTANCE hIns, CGunnerBox& box);
};

