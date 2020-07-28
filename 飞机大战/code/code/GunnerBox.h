#pragma once
#include "Gunner.h"

class CGunnerBox
{
public:
	CGunnerBox(void);
	~CGunnerBox(void);
public:
	list<CGunner*> m_lstGunner;   // 装炮弹的链表
public:
	void AllGunnerShow(HDC hdc);   //  所有炮弹的显示
	void AllGunnerMove(); //  所有炮弹的移动
};

