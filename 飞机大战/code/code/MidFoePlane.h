#pragma once
#include "foeplane.h"
class CMidFoePlane :
	public CFoePlane
{
public:
	CMidFoePlane(void);
	~CMidFoePlane(void);
public:
	virtual bool IsGunnetHitFoePlane(CGunner* pGunner);
	virtual bool IsHitPlayerPlane(CPlayer& player);
	virtual void FoePlaneInit(HINSTANCE hIns);
	virtual void FoePlaneMove();
	virtual void FoePlaneShow(HDC hdc);
};

