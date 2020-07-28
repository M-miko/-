#pragma once
#include "foeplane.h"
class CSmallFoePlane :
	public CFoePlane
{
public:
	CSmallFoePlane(void);
	~CSmallFoePlane(void);
public:
	virtual bool IsGunnetHitFoePlane(CGunner* pGunner);
	virtual bool IsHitPlayerPlane(CPlayer& player);
	virtual void FoePlaneInit(HINSTANCE hIns);
	virtual void FoePlaneMove();
	virtual void FoePlaneShow(HDC hdc);
};

