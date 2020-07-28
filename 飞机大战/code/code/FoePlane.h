#pragma once
#include "Sys.h"
#include "Gunner.h"
#include "Player.h"

class CFoePlane
{
public:
	HBITMAP m_hBmpFoePlane;   //  飞机的图片
	int x;
	int y;
	int m_nBlood;    //  血量
	int m_nShowID;    //  显示哪一块
public:
	CFoePlane(void);
	virtual ~CFoePlane(void);
public:
	virtual bool IsGunnetHitFoePlane(CGunner* pGunner)=0;
	virtual bool IsHitPlayerPlane(CPlayer& player)=0;
	virtual void FoePlaneInit(HINSTANCE hIns)=0;
	virtual void FoePlaneMove()=0;
	virtual void FoePlaneShow(HDC hdc)=0;
public:
	bool IsBoom()       //  默认 叫 inline（内联函数）
	{
		if(m_nBlood == 0)
			return true;
		return false;
	}
	void DownBlood()    //  掉血
	{
		m_nBlood--;
	}
};

