#include "PlaneApp.h"

IMPLEMENT(CPlaneApp)
	CPlaneApp::CPlaneApp(void)
{
}


CPlaneApp::~CPlaneApp(void)
{
}
void CPlaneApp::OnCreateGame()
{
	//  1.  初始化背景
	back.BackInit(m_hIns);
	//  2.  初始化玩家飞机
	plane.PlayerInit(m_hIns);

	//  3.  启动所有的定时器
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);    //  控制背景移动
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  控制玩家飞机移动
	::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);   //  控制发送炮弹
	::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);     //  控制炮弹移动
	::SetTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID,1000,0);   //  控制创建敌人飞机
	::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,30,0);     //  控制敌人飞机移动
	::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID,150,0);       //  控制  爆炸的效果
}
void CPlaneApp::OnGameDraw()
{
	HDC dc = ::GetDC(m_hMainWnd);
	HDC hMemDC = ::CreateCompatibleDC(dc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(dc,380,550);
	::SelectObject(hMemDC,hBitmap);
	//-------------------显示游戏----------------------
	back.BackShow(hMemDC);      //  显示背景
	plane.PlayerShow(hMemDC);    //  显示玩家飞机
	gunnerbox.AllGunnerShow(hMemDC);   //  显示所有炮弹
	foeplanebox.AllFoePlaneShow(hMemDC);   //  显示所有敌人飞机
	blastfoeplane.AllBlastFoePlaneShow(hMemDC); //  显示所有爆炸敌人飞机
	//-------------------显示游戏----------------------
	::BitBlt(dc,0,0,380,550,hMemDC,0,0,SRCCOPY);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hMainWnd,dc);
}
void CPlaneApp::OnGameRun(WPARAM nTimerID)
{
	if(nTimerID == CHANGE_SHOWID_TIMER_ID)
	{
		blastfoeplane.ChangeShowID();
	}

	if(nTimerID == CREATE_FOEPLANE_TIMER_ID)  
	{
		foeplanebox.CreateFoePlane(m_hIns);
	}

	if(nTimerID == FOEPLANE_MOVE_TIMER_ID) 
	{
		foeplanebox.AllFoePlaneMove();
		if(this->IsGameOver() == true)
		{
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID);    //  控制背景移动
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID);   //  控制玩家飞机移动
			::KillTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID);   //  控制发送炮弹
			::KillTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID);     //  控制炮弹移动
			::KillTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID);   //  控制创建敌人飞机
			::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);     //  控制敌人飞机移动
			::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID);       //  控制  爆炸的效果
			if(::MessageBox(0,"GameOver","提示",MB_OK)==IDOK)
			{
				::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);    //  控制背景移动
				::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  控制玩家飞机移动
				::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);   //  控制发送炮弹
				::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);     //  控制炮弹移动
				::SetTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID,1000,0);   //  控制创建敌人飞机
				::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,30,0);     //  控制敌人飞机移动
				::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID,150,0);       //  控制  爆炸的效果

			}
		}
	}
	if(nTimerID == SEND_GUNNER_TIMER_ID)   //  玩家飞机发送炮弹
	{
		plane.SendGunner(m_hIns,gunnerbox);
	}

	if(nTimerID == GUNNER_MOVE_TIMER_ID)     //  所有炮弹移动
	{ 
		gunnerbox.AllGunnerMove(); 
		this->GunnerHitFoePlane();   // 炮弹打敌人飞机
	}

	//  玩家移动
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(::GetAsyncKeyState(VK_LEFT))   //  获取键盘的状态
			plane.PlayerMove(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))   //  获取键盘的状态
			plane.PlayerMove(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))   //  获取键盘的状态
			plane.PlayerMove(VK_UP);
		if(::GetAsyncKeyState(VK_DOWN))   //  获取键盘的状态
			plane.PlayerMove(VK_DOWN);
	}

	//  背景移动
	if(nTimerID == BACK_MOVE_TIMER_ID)
		back.BackMove();            

	//  重绘
	this->OnGameDraw();
}
void CPlaneApp::OnKeyDown(WPARAM nKey)
{
	////  玩家飞机移动
	//plane.PlayerMove(nKey);
	////  重绘
	//this->OnGameDraw();
}
void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;   //  标记 炮弹是否打中敌人飞机

	//  遍历所有的炮弹
	list<CGunner*>::iterator iteGunner = gunnerbox.m_lstGunner.begin();
	while(iteGunner != gunnerbox.m_lstGunner.end())
	{
		//------------------------遍历所有的敌人飞机---------------------------
		list<CFoePlane*>::iterator iteFoePlane = foeplanebox.m_lstFoePlane.begin();
		while(iteFoePlane != foeplanebox.m_lstFoePlane.end())
		{
			//  判断 iteGunner 这个炮弹是否打中了iteFoePlane 敌人飞机
			if( (*iteFoePlane)->IsGunnetHitFoePlane(*iteGunner) == true)
			{
				bflag = true;
				//  删除炮弹
				delete(*iteGunner);
				iteGunner = gunnerbox.m_lstGunner.erase(iteGunner);
				//  敌人飞机掉血
				(*iteFoePlane)->DownBlood();
				//  判断这个敌人飞机是否爆炸
				if((*iteFoePlane)->IsBoom() == true)
				{
					//  放到另一个链表里显示爆炸效果 
					blastfoeplane.m_lstBlastFoePlane.push_back(*iteFoePlane);
					//  删除这个节点
					iteFoePlane = foeplanebox.m_lstFoePlane.erase(iteFoePlane);
				}
				break;
			}
			++iteFoePlane;
		}
		//------------------------遍历所有的敌人飞机---------------------------
		if(bflag == false)
			++iteGunner;
		else
			bflag = false;
	}
}

bool CPlaneApp::IsGameOver()
{
	list<CFoePlane*>::iterator ite = foeplanebox.m_lstFoePlane.begin();
	while(ite != foeplanebox.m_lstFoePlane.end())
	{
		if( (*ite)->IsHitPlayerPlane(plane) == true)
		{
			return true;
		}
		++ite;
	}

	return false;
}