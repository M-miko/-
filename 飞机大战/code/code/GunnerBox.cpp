#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	// 删除 链表中所有的炮弹对象
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		delete(*ite);                 // 删除里面装的对象
		ite = m_lstGunner.erase(ite);   //  删除链表的节点
	}
}
void CGunnerBox::AllGunnerShow(HDC hdc)  //  所有炮弹的显示
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  显示炮弹
		(*ite)->GunnerShow(hdc);
		++ite;
	}	
}
void CGunnerBox::AllGunnerMove() //  所有炮弹的移动
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		//  判断炮弹是否超出边界
		if((*ite)->y < 0)
		{
			//  删除炮弹
			delete(*ite);
			ite = m_lstGunner.erase(ite);
		}
		else
		{
			//  炮弹移动
			(*ite)->GunnerMove();
			++ite;
		}
	}	
}