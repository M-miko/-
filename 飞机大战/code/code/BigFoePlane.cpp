#include "BigFoePlane.h"


CBigFoePlane::CBigFoePlane(void)
{
	m_hBmpFoePlane = 0;
	x = rand()%(380-108);
	y = -128;
	m_nBlood = 5;
	m_nShowID = 3;
}


CBigFoePlane::~CBigFoePlane(void)
{
}
bool CBigFoePlane::IsGunnetHitFoePlane(CGunner* pGunner)
{
	if(pGunner->x >= this->x && pGunner->x <= this->x+108
		&& pGunner->y >= this->y && pGunner->y <= this->y+128)
		return true;
	return false;
}
bool CBigFoePlane::IsHitPlayerPlane(CPlayer& player)
{
	//  x+30,y
	if(player.x+30 >= this->x && player.x+30 <= this->x+108
		&& player.y >= this->y && player.y <= this->y+128)
	{
		return true;
	}
	//  x+60,y+50
	if(player.x+60 >= this->x && player.x+60 <= this->x+108
		&& player.y+50 >= this->y && player.y+50 <= this->y+128)
	{
		return true;
	}
	//  x,y+50
	if(player.x >= this->x && player.x <= this->x+108
		&& player.y+50 >= this->y && player.y+50 <= this->y+128)
	{
		return true;
	}
	return false;
}
void CBigFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BIG));
}
void CBigFoePlane::FoePlaneMove()
{
	y+=2;
}
void CBigFoePlane::FoePlaneShow(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	::SelectObject(hMemDC,m_hBmpFoePlane);
	::BitBlt(hdc,x,y,108,128,hMemDC,0,(3-m_nShowID)*128,SRCAND);
	::DeleteDC(hMemDC);
}