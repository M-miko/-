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
	CBack back;   //  游戏背景
	CPlayer plane;   //  玩家飞机

	CGunnerBox gunnerbox;   //  所有炮弹
	CFoePlaneBox foeplanebox;  //  所有敌人飞机
	CBlastFoePlane blastfoeplane;   //  装爆炸的人飞机
public:
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
public:
	void GunnerHitFoePlane();   // 炮弹打敌人飞机
	bool IsGameOver();  
};

