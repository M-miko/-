#pragma once
#include "FoePlane.h"

class CBlastFoePlane
{
public:
	CBlastFoePlane(void);
	~CBlastFoePlane(void);
public:
	list<CFoePlane*> m_lstBlastFoePlane;   //  װ��ը�ĵ��˷ɻ�
public:
	void ChangeShowID();
	void AllBlastFoePlaneShow(HDC hdc);

};

