#include "Gunner.h"


CGunner::CGunner(void)
{
	m_hBmpGunner = 0;
	x = 0;
	y = 0;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hBmpGunner);
	m_hBmpGunner = 0;
}
void CGunner::GunnerInit(HINSTANCE hIns, int x1, int y2)
{
	m_hBmpGunner = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GUNNER));
	//  初始化炮弹的位置
	x = x1;
	y = y2;
}
void CGunner::GunnerMove()
{
	y-=10;
}
void CGunner::GunnerShow(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpGunner);
	::BitBlt(hdc,x,y,6,9,hMemDC,0,0,SRCCOPY);
	::DeleteDC(hMemDC);
}