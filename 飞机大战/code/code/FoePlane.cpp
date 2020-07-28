#include "FoePlane.h"


CFoePlane::CFoePlane(void)
{
	m_hBmpFoePlane = 0;   //  飞机的图片
	x = 0;
	y = 0;
	m_nBlood = 0;    //  血量
	m_nShowID = 0;    //  显示哪一块
}


CFoePlane::~CFoePlane(void)
{
	::DeleteObject(m_hBmpFoePlane);
	m_hBmpFoePlane = 0;
}
