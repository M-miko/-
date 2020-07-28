#pragma once
#include "cgameapp.h"
#include "Back.h"
#include "Player.h"
#include "FoePlaneBox.h"
#include "BlastFoePlane.h"

class CPlaneApp :
	public CGameApp
{
public:
	CPlaneApp(void);
	~CPlaneApp(void);
public:
	CBack back;   //  ��Ϸ����
	CPlayer plane;   //  ��ҷɻ�

	CGunnerBox gunnerbox;   //  �����ڵ�
	CFoePlaneBox foeplanebox;  //  ���е��˷ɻ�
	CBlastFoePlane blastfoeplane;   //  װ��ը���˷ɻ�
public:
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
public:
	void GunnerHitFoePlane();   // �ڵ�����˷ɻ�
	bool IsGameOver();  
};

