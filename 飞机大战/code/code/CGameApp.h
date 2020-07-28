#pragma once 
#ifndef _GAMEAPP_H_
#define _GAMEAPP_H_
#include <windows.h>

class CGameApp;
CGameApp* CreateObject();    //  ��������

#define IMPLEMENT(ThisClass)\
	CGameApp* CreateObject()\
	{\
		return new ThisClass;\
	}


class CGameApp
{
protected:
	HINSTANCE m_hIns;    //  ʵ�����
	HWND m_hMainWnd;     //  ������
public:
	CGameApp()
	{
		m_hIns = 0;
		m_hMainWnd = 0;
	}
	virtual ~CGameApp()
	{
	
	}
public:
	void SetHandle(HINSTANCE hIns,HWND hMainWnd)
	{
		m_hIns = hIns;
		m_hMainWnd = hMainWnd;
	}
public:
	virtual void OnCreateGame(){}   // WM_CREATE:  ��Ϸ�ĳ�ʼ��
	virtual void OnGameDraw(){}       //  WM_PAINT   ��Ϸ��ͼ
	virtual void OnGameRun(WPARAM nTimerID){}         //  WM_TIMER
	virtual void OnKeyDown(WPARAM nKey){}
	virtual void OnKeyUp(WPARAM nKey){}
	virtual void OnLButtonDown(POINT point){}
	virtual void OnLButtonUp(POINT point){}
	virtual void OnMouseMove(POINT point){}
};


#endif//_GAMEAPP_H_