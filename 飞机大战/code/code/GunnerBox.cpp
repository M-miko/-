#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	// ɾ�� ���������е��ڵ�����
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		delete(*ite);                 // ɾ������װ�Ķ���
		ite = m_lstGunner.erase(ite);   //  ɾ������Ľڵ�
	}
}
void CGunnerBox::AllGunnerShow(HDC hdc)  //  �����ڵ�����ʾ
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  ��ʾ�ڵ�
		(*ite)->GunnerShow(hdc);
		++ite;
	}	
}
void CGunnerBox::AllGunnerMove() //  �����ڵ����ƶ�
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  �ж��ڵ��Ƿ񳬳��߽�
		if((*ite)->y < 0)
		{
			//  ɾ���ڵ�
			delete(*ite);
			ite = m_lstGunner.erase(ite);
		}
		else
		{
			//  �ڵ��ƶ�
			(*ite)->GunnerMove();
			++ite;
		}
	}	
}