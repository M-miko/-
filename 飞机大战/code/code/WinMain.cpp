// ���
// HDC        �����豸���            ��ͼ
// HINSTANCE  Ӧ�ó���ʵ���ľ��      ������Դ
// HWND       ���ھ��          

// ��Ϣ       WM_LBUTTONDOWN  WM_KEYDOWN  WM_TIMER   WM_CLOSE  WM_PAINT

#include<windows.h>
#include "CGameApp.h"
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hIns;
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nCmdShow)
{
	srand((unsigned int)time(0));
	hIns = hInstance;
	//  1.  ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = 0;
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;    //  �������ϵ�Сͼ��
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;   //  ���ڵ���Ϣ������
	wndclass.lpszClassName = "lele";  //  ע�ᴰ��������� 
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;

	//  2.  ע��
	if( ::RegisterClassEx(&wndclass) == FALSE)
	{
		::MessageBox(0,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}
	// 3. ����
	HWND hwnd = ::CreateWindow("lele","O(��_��)O����~",WS_OVERLAPPEDWINDOW,0,0,380+16,550+38,0,0,hInstance,0);
	if(hwnd == 0)
	{
		::MessageBox(0,"����ʧ��","��ʾ",MB_OK);
		return 0;
	}

	// 4. ��ʾ����
	::ShowWindow(hwnd,SW_SHOW);

	// 5. ��Ϣѭ��
	MSG msg;
	while(::GetMessage(&msg,0,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);   // �ַ��� ������Ϣ�Ĵ�����WndProc
	}


	return 0;
}



CGameApp* pApp = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			//  ���ú�����������
			pApp = CreateObject();
			
			if(pApp != 0)
			{
				//  ���þ��
				pApp->SetHandle(hIns,hwnd);
				//  ��ʼ����Ϸ
				pApp->OnCreateGame();
			}
		}
		break;
	case WM_PAINT:
		{
			if(pApp != 0)
				pApp->OnGameDraw();
		}
		break;
	case WM_TIMER:
		{
			if(pApp != 0)
				pApp->OnGameRun(wParam);
		}
		break;
	case WM_KEYDOWN:
		{
			if(pApp != 0)
				pApp->OnKeyDown(wParam);
		}
		break;
	case WM_KEYUP:
		{
			if(pApp != 0)
				pApp->OnKeyUp(wParam);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);

			if(pApp != 0)
				pApp->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);

			if(pApp != 0)
				pApp->OnLButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);

			if(pApp != 0)
				pApp->OnMouseMove(point);
		}
		break;
	case WM_CLOSE:  //  �ر�
		{
			delete pApp;
			pApp = 0;
			::PostQuitMessage(0);    //  ����һ���˳�����Ϣ
		}
		break;
	}
	return DefWindowProc( hwnd,  uMsg,  wParam,  lParam);
}