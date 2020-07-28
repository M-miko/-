#include "BlastFoePlane.h"


CBlastFoePlane::CBlastFoePlane(void)
{
}


CBlastFoePlane::~CBlastFoePlane(void)
{
	list<CFoePlane*>::iterator ite = m_lstBlastFoePlane.begin();
	while(ite != m_lstBlastFoePlane.end())
	{
		delete (*ite);
		ite = m_lstBlastFoePlane.erase(ite);
	}
}
void CBlastFoePlane::ChangeShowID()
{
	list<CFoePlane*>::iterator ite = m_lstBlastFoePlane.begin();
	while(ite != m_lstBlastFoePlane.end())
	{
		if((*ite)->m_nShowID == 0)   //  爆炸的效果显示完
		{
			delete (*ite);
			ite = m_lstBlastFoePlane.erase(ite);		
		}
		else
		{
			(*ite)->m_nShowID--;
			++ite;
		}
	}	
}
void CBlastFoePlane::AllBlastFoePlaneShow(HDC hdc)
{
	list<CFoePlane*>::iterator ite = m_lstBlastFoePlane.begin();
	while(ite != m_lstBlastFoePlane.end())
	{
		(*ite)->FoePlaneShow(hdc);
		++ite;
	}
}