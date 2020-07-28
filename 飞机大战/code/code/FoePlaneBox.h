#pragma once
#include "FoePlane.h"

class CFoePlaneBox
{
public:
	CFoePlaneBox(void);
	~CFoePlaneBox(void);
public:
	list<CFoePlane*> m_lstFoePlane;    //  ×°µÐÈË·É»ú
public:
	void AllFoePlaneMove();
	void AllFoePlaneShow(HDC hdc);
	void CreateFoePlane(HINSTANCE hIns);
};

