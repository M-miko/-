#include "Player.h"


CPlayer::CPlayer(void)
{
	m_hBmpPlayer = 0;
	m_nGunnerStyle = 1;
	x = 160;
	y = 490;
}


CPlayer::~CPlayer(void)
{
	::DeleteObject(m_hBmpPlayer);
	m_hBmpPlayer = 0;
}
void CPlayer::PlayerInit(HINSTANCE hIns)
{
	//  加载图片
	m_hBmpPlayer = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER));
}
void CPlayer::PlayerMove(int FX)
{
	if(FX == VK_LEFT)
	{
		if(x > 0)
			x-=2;
	}
	if(FX == VK_RIGHT)
	{
		if(x < 320)
			x+=2;
	}
	if(FX == VK_UP)
	{
		if(y > 0)
			y-=2;
	}
	if(FX == VK_DOWN)
	{
		if(y < 490)
			y+=2;
	}
}
void CPlayer::PlayerShow(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpPlayer);
	::BitBlt(hdc,x,y,60,60,hMemDC,0,0,SRCAND);
	::DeleteDC(hMemDC);
}

void CPlayer::SendGunner(HINSTANCE hIns, CGunnerBox& box)
{
	//  创建一个炮弹的对象
	CGunner* pGunner = new CGunner;
	//  初始化炮弹
	pGunner->GunnerInit(hIns,x+27,y-9);
	//  把放到盒子里
	box.m_lstGunner.push_back(pGunner);
}