#include "FoePlane.h"


CFoePlane::CFoePlane(void)
{
	m_hBmpFoePlane = 0;   //  �ɻ���ͼƬ
	x = 0;
	y = 0;
	m_nBlood = 0;    //  Ѫ��
	m_nShowID = 0;    //  ��ʾ��һ��
}


CFoePlane::~CFoePlane(void)
{
	::DeleteObject(m_hBmpFoePlane);
	m_hBmpFoePlane = 0;
}
