#include "MidFoePlane.h"

CMidFoePlane::CMidFoePlane(void)
{
	m_hBmpFoePlane = 0;
	x = rand()%(380-70);
	y = -90;
	m_nBlood = 3;
	m_nShowID = 2;
}


CMidFoePlane::~CMidFoePlane(void)
{
}
bool CMidFoePlane::IsGunnetHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x >= this->x && pGunner->x <= this->x+70
		&& pGunner->y >= this->y && pGunner->y <= this->y+90)
		return true;
	return false;
}
bool CMidFoePlane::IsHitPlayerPlane(CPlayer& player)
{
	//  x+30,y
	if(player.x+30 >= this->x && player.x+30 <= this->x+70
		&& player.y >= this->y && player.y <= this->y+90)
	{
		return true;
	}
	//  x+60,y+50
	if(player.x+60 >= this->x && player.x+60 <= this->x+70
		&& player.y+50 >= this->y && player.y+50 <= this->y+90)
	{
		return true;
	}
	//  x,y+50
	if(player.x >= this->x && player.x <= this->x+70
		&& player.y+50 >= this->y && player.y+50 <= this->y+90)
	{
		return true;
	}
	return false;
}
void CMidFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MID));
}
void CMidFoePlane::FoePlaneMove()
{
	y+=4;
}
void CMidFoePlane::FoePlaneShow(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,70,90,hMemDC,0,(2-m_nShowID)*90,SRCAND);
	::DeleteDC(hMemDC);
}