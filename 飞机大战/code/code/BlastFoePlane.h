#pragma once
#include "FoePlane.h"

class CBlastFoePlane
{
public:
	CBlastFoePlane(void);
	~CBlastFoePlane(void);
public:
	list<CFoePlane*> m_lstBlastFoePlane;   //  装爆炸的敌人飞机
public:
	void ChangeShowID();
	void AllBlastFoePlaneShow(HDC hdc);

};

