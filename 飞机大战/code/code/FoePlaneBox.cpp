#include "FoePlaneBox.h"
#include "BigFoePlane.h"
#include "MidFoePlane.h"
#include "SmallFoePlane.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	//  ɾ�����еĵ��˷ɻ�
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  ɾ������
		delete (*ite);
		//  ɾ���ڵ�
		ite = m_lstFoePlane.erase(ite);
	}
}
void CFoePlaneBox::AllFoePlaneMove()
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		//  ɾ��  �����߽�ķɻ�
		if((*ite)->y > 550)
		{
			//  ɾ������
			delete (*ite);
			//  ɾ���ڵ�
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
	//  ����һ�����˷ɻ�����
	int index = rand()%12;
	CFoePlane* pFoePlane = 0;
	if(index >= 0 && index <= 1)
		pFoePlane = new CBigFoePlane;
	else if(index >= 2 && index <= 5)
		pFoePlane = new CMidFoePlane;
	else
		pFoePlane = new CSmallFoePlane;
	//  ��ʼ��������˷ɻ�
	pFoePlane->FoePlaneInit(hIns);
	//  �ŵ�������
	m_lstFoePlane.push_back(pFoePlane);
}
