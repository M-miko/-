#pragma once
#include "Sys.h"
#include "Gunner.h"
#include "Player.h"

class CFoePlane
{
public:
	HBITMAP m_hBmpFoePlane;   //  �ɻ���ͼƬ
	int x;
	int y;
	int m_nBlood;    //  Ѫ��
	int m_nShowID;    //  ��ʾ��һ��
public:
	CFoePlane(void);
	virtual ~CFoePlane(void);
public:
	virtual bool IsGunnetHitFoePlane(CGunner* pGunner)=0;
	virtual bool IsHitPlayerPlane(CPlayer& player)=0;
	virtual void FoePlaneInit(HINSTANCE hIns)=0;
	virtual void FoePlaneMove()=0;
	virtual void FoePlaneShow(HDC hdc)=0;
public:
	bool IsBoom()       //  Ĭ�� �� inline������������
	{
		if(m_nBlood == 0)
			return true;
		return false;
	}
	void DownBlood()    //  ��Ѫ
	{
		m_nBlood--;
	}
};

