#include "FoePlaneBox.h"
#include "BigFoePlane.h"
#include "MidFoePlane.h"
#include "SmallFoePlane.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	//  删除所有的敌人飞机
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  删除对象
		delete (*ite);
		//  删除节点
		ite = m_lstFoePlane.erase(ite);
	}
}
void CFoePlaneBox::AllFoePlaneMove()
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  删除  超出边界的飞机
		if((*ite)->y > 550)
		{
			//  删除对象
			delete (*ite);
			//  删除节点
			ite = m_lstFoePlane.erase(ite);			
		}
		else
		{
			(*ite)->FoePlaneMove();
			++ite;
		}
	}	
}
void CFoePlaneBox::AllFoePlaneShow(HDC hdc)
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->FoePlaneShow(hdc);
		++ite;
	}	
}
void CFoePlaneBox::CreateFoePlane(HINSTANCE hIns)
{
	//  创建一个敌人飞机对象
	int index = rand()%12;
	CFoePlane* pFoePlane = 0;
	if(index >= 0 && index <= 1)
		pFoePlane = new CBigFoePlane;
	else if(index >= 2 && index <= 5)
		pFoePlane = new CMidFoePlane;
	else
		pFoePlane = new CSmallFoePlane;
	//  初始化这个敌人飞机
	pFoePlane->FoePlaneInit(hIns);
	//  放到链表里
	m_lstFoePlane.push_back(pFoePlane);
}
