#include "SmallFoePlane.h"

CSmallFoePlane::CSmallFoePlane(void)
{
	m_hBmpFoePlane = 0;
	x = rand()%(380-34);
	y = -28;
	m_nBlood = 1;
	m_nShowID = 1;
}


CSmallFoePlane::~CSmallFoePlane(void)
{
}
bool CSmallFoePlane::IsGunnetHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x >= this->x && pGunner->x <= this->x+34
		&& pGunner->y >= this->y && pGunner->y <= this->y+28)
		return true;
	return false;
}
bool CSmallFoePlane::IsHitPlayerPlane(CPlayer& player)
{
	//  x+30,y
	if(player.x+30 >= this->x && player.x+30 <= this->x+34
		&& player.y >= this->y && player.y <= this->y+28)
	{
		return true;
	}
	//  x+60,y+50
	if(player.x+60 >= this->x && player.x+60 <= this->x+34
		&& player.y+50 >= this->y && player.y+50 <= this->y+28)
	{
		return true;
	}
	//  x,y+50
	if(player.x >= this->x && player.x <= this->x+34
		&& player.y+50 >= this->y && player.y+50 <= this->y+28)
	{
		return true;
	}
	return false;
}
void CSmallFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SMALL));
}
void CSmallFoePlane::FoePlaneMove()
{
	y+=6;
}
void CSmallFoePlane::FoePlaneShow(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,34,28,hMemDC,0,(1-m_nShowID)*28,SRCAND);
	::DeleteDC(hMemDC);
}