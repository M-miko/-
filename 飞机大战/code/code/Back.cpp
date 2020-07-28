#include "Back.h"


CBack::CBack(void)
{
	m_hBmpBackDown = 0;
	m_hBmpBackUp = 0;
	x = 0;
	y = 0;
}


CBack::~CBack(void)
{
	//  É¾³ýÍ¼Æ¬
	::DeleteObject(m_hBmpBackDown);
	m_hBmpBackDown = 0;
	::DeleteObject(m_hBmpBackUp);
	m_hBmpBackUp = 0;
}
void CBack::BackInit(HINSTANCE hIns)
{
	//  ¼ÓÔØ×ÊÔ´
	m_hBmpBackDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
	m_hBmpBackUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
}
void CBack::BackMove()
{
	if(y > 550)
		y = 0;
	else
		y++;
}
void CBack::BackShow(HDC hdc)
{
	// ÌùÍ¼
	HDC hMemDC = ::CreateCompatibleDC(hdc);

	::SelectObject(hMemDC,m_hBmpBackUp);
	::BitBlt(hdc,x,y-550,380,550,hMemDC,0,0,SRCCOPY);

	::SelectObject(hMemDC,m_hBmpBackDown);
	::BitBlt(hdc,x,y,380,550,hMemDC,0,0,SRCCOPY);

	::DeleteDC(hMemDC);
}