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
	//  1.  ��ʼ������
	back.BackInit(m_hIns);
	//  2.  ��ʼ����ҷɻ�
	plane.PlayerInit(m_hIns);

	//  3.  �������еĶ�ʱ��
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);    //  ���Ʊ����ƶ�
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  ������ҷɻ��ƶ�
	::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);   //  ���Ʒ����ڵ�
	::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);     //  �����ڵ��ƶ�
	::SetTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID,1000,0);   //  ���ƴ������˷ɻ�
	::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,30,0);     //  ���Ƶ��˷ɻ��ƶ�
	::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID,150,0);       //  ����  ��ը��Ч��
}
void CPlaneApp::OnGameDraw()
{
	HDC dc = ::GetDC(m_hMainWnd);
	HDC hMemDC = ::CreateCompatibleDC(dc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(dc,380,550);
	::SelectObject(hMemDC,hBitmap);
	//-------------------��ʾ��Ϸ----------------------
	back.BackShow(hMemDC);      //  ��ʾ����
	plane.PlayerShow(hMemDC);    //  ��ʾ��ҷɻ�
	gunnerbox.AllGunnerShow(hMemDC);   //  ��ʾ�����ڵ�
	foeplanebox.AllFoePlaneShow(hMemDC);   //  ��ʾ���е��˷ɻ�
	blastfoeplane.AllBlastFoePlaneShow(hMemDC); //  ��ʾ���б�ը���˷ɻ�
	//-------------------��ʾ��Ϸ----------------------
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
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID);    //  ���Ʊ����ƶ�
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID);   //  ������ҷɻ��ƶ�
			::KillTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID);   //  ���Ʒ����ڵ�
			::KillTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID);     //  �����ڵ��ƶ�
			::KillTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID);   //  ���ƴ������˷ɻ�
			::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);     //  ���Ƶ��˷ɻ��ƶ�
			::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID);       //  ����  ��ը��Ч��
			if(::MessageBox(0,"GameOver","��ʾ",MB_OK)==IDOK)
			{
				::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0);    //  ���Ʊ����ƶ�
				::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);   //  ������ҷɻ��ƶ�
				::SetTimer(m_hMainWnd,SEND_GUNNER_TIMER_ID,350,0);   //  ���Ʒ����ڵ�
				::SetTimer(m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);     //  �����ڵ��ƶ�
				::SetTimer(m_hMainWnd,CREATE_FOEPLANE_TIMER_ID,1000,0);   //  ���ƴ������˷ɻ�
				::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,30,0);     //  ���Ƶ��˷ɻ��ƶ�
				::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIMER_ID,150,0);       //  ����  ��ը��Ч��

			}
		}
	}
	if(nTimerID == SEND_GUNNER_TIMER_ID)   //  ��ҷɻ������ڵ�
	{
		plane.SendGunner(m_hIns,gunnerbox);
	}

	if(nTimerID == GUNNER_MOVE_TIMER_ID)     //  �����ڵ��ƶ�
	{ 
		gunnerbox.AllGunnerMove(); 
		this->GunnerHitFoePlane();   // �ڵ�����˷ɻ�
	}

	//  ����ƶ�
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(::GetAsyncKeyState(VK_LEFT))   //  ��ȡ���̵�״̬
			plane.PlayerMove(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))   //  ��ȡ���̵�״̬
			plane.PlayerMove(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))   //  ��ȡ���̵�״̬
			plane.PlayerMove(VK_UP);
		if(::GetAsyncKeyState(VK_DOWN))   //  ��ȡ���̵�״̬
			plane.PlayerMove(VK_DOWN);
	}

	//  �����ƶ�
	if(nTimerID == BACK_MOVE_TIMER_ID)
		back.BackMove();            

	//  �ػ�
	this->OnGameDraw();
}
void CPlaneApp::OnKeyDown(WPARAM nKey)
{
	////  ��ҷɻ��ƶ�
	//plane.PlayerMove(nKey);
	////  �ػ�
	//this->OnGameDraw();
}
void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;   //  ��� �ڵ��Ƿ���е��˷ɻ�

	//  �������е��ڵ�
	list<CGunner*>::iterator iteGunner = gunnerbox.m_lstGunner.begin();
	while(iteGunner != gunnerbox.m_lstGunner.end())
	{
		//------------------------�������еĵ��˷ɻ�---------------------------
		list<CFoePlane*>::iterator iteFoePlane = foeplanebox.m_lstFoePlane.begin();
		while(iteFoePlane != foeplanebox.m_lstFoePlane.end())
		{
			//  �ж� iteGunner ����ڵ��Ƿ������iteFoePlane ���˷ɻ�
			if( (*iteFoePlane)->IsGunnetHitFoePlane(*iteGunner) == true)
			{
				bflag = true;
				//  ɾ���ڵ�
				delete(*iteGunner);
				iteGunner = gunnerbox.m_lstGunner.erase(iteGunner);
				//  ���˷ɻ���Ѫ
				(*iteFoePlane)->DownBlood();
				//  �ж�������˷ɻ��Ƿ�ը
				if((*iteFoePlane)->IsBoom() == true)
				{
					//  �ŵ���һ����������ʾ��ըЧ�� 
					blastfoeplane.m_lstBlastFoePlane.push_back(*iteFoePlane);
					//  ɾ������ڵ�
					iteFoePlane = foeplanebox.m_lstFoePlane.erase(iteFoePlane);
				}
				break;
			}
			++iteFoePlane;
		}
		//------------------------�������еĵ��˷ɻ�---------------------------
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