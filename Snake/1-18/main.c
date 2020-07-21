#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

HBITMAP hBitmap_Background;
HBITMAP hBitmap_Apple;
HBITMAP hBitmap_SnakeBody;
HBITMAP hBitmap_SnakeHead_Up;
HBITMAP hBitmap_SnakeHead_Down;
HBITMAP hBitmap_SnakeHead_Left;
HBITMAP hBitmap_SnakeHead_Right;

typedef struct NODE
{
	int x;
	int y;
	struct NODE *pLast;
	struct NODE *pNext;
}Snake,Apple;

enum DIRECTION {UP,DOWN,LEFT,RIGHT};

Snake *pHead = NULL;
Snake *pTail = NULL;
Apple apple = {5,5,NULL,NULL};
BOOL g_Flag = TRUE;

enum DIRECTION Direction = UP;

void ShowBackGround(HDC hdc);
void AddNode(int x,int y);
void ShowSnake(HDC hdc);
void Move();
void ShowApple(HDC hdc);
BOOL IsEatApple();
void NewApple();
BOOL IsBumpWall();
BOOL IsEatItself();

int CALLBACK WinMain(
					 HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow
					 )
{
	WNDCLASSEX ex;
	HWND hWnd;
	MSG msg;
	int i;

	//����λͼ
	hBitmap_Background = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
	hBitmap_Apple = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
	hBitmap_SnakeBody = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
	hBitmap_SnakeHead_Up = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP5));
	hBitmap_SnakeHead_Down = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP7));
	hBitmap_SnakeHead_Left = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP6));
	hBitmap_SnakeHead_Right = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP4));

	//��ʼ����
	for(i=0;i<1000;i++)
	{
		AddNode(3,3);
		AddNode(3,4);
		AddNode(3,5);
	}

	//1.��ƴ���
	ex.style = CS_HREDRAW | CS_VREDRAW;
	ex.cbSize = sizeof(ex);
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hInstance;
	ex.hIcon = NULL;
	ex.hCursor = NULL;
	ex.hbrBackground = CreateSolidBrush(RGB(0,255,0));
	ex.hIconSm = NULL;
	ex.lpfnWndProc = &MyWNDPROC;   
	ex.lpszMenuName = NULL;
	ex.lpszClassName = "aaa";
	
	//2.ע�ᴰ��
	RegisterClassEx(&ex);

	//3.��������
	hWnd = CreateWindow(ex.lpszClassName,"̰����",WS_OVERLAPPEDWINDOW,50,50,615,638,NULL,NULL,hInstance,NULL);

	//4.��ʾ����
	ShowWindow(hWnd,SW_SHOW);


	//���ö�ʱ��
	SetTimer(hWnd,1,200,NULL);

	//���������
	srand((unsigned int)time(NULL));

	//��Ϣѭ��
	while(GetMessage(&msg,NULL,0,0))   // a   a != 0
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch(message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(g_Flag == TRUE)
		{
			switch(wParam)
			{
			case VK_UP:
				if(Direction != DOWN)
				{
					Direction = UP;
				}		
				break;
			case VK_DOWN:
				if(Direction != UP)
					Direction = DOWN;
				break;
			case VK_LEFT:
				if(Direction != RIGHT)
					Direction = LEFT;
				break;
			case VK_RIGHT:
				if(Direction != LEFT)
					Direction = RIGHT;
				break;
			}
			g_Flag = FALSE;
		}
		hdc = GetDC(hWnd);

		//��ʾ����
		ShowBackGround(hdc);
		//��ʾ��
		ShowSnake(hdc);
		//��ʾƻ��
		ShowApple(hdc);

		ReleaseDC(hWnd,hdc);
		break;
	case WM_PAINT:      //�ػ���Ϣ
		hdc = BeginPaint(hWnd,&ps);
		
		//��ʾ����
		ShowBackGround(hdc);
		//��ʾ��
		ShowSnake(hdc);
		//��ʾƻ��
		ShowApple(hdc);

		EndPaint(hWnd,&ps);
		break;
	case WM_TIMER:
		g_Flag = TRUE;
		hdc = GetDC(hWnd);
		//��
		Move();

		//�ж���Ϸ�Ƿ����
		//ײǽ  ��  ��ҧ
		/*if(IsBumpWall() || IsEatItself())
		{
			KillTimer(hWnd,1);
			MessageBox(hWnd,"��Ϸ����","��ʾ",MB_OK);
		}*/

		//�Ƿ�Ե�ƻ��
		if(IsEatApple())
		{
			//����
			AddNode(-10,-10);
			//��ƻ��
			NewApple();
		}

		//��ʾ����
		ShowBackGround(hdc);
		//��ʾ��
		ShowSnake(hdc);
		//��ʾƻ��
		ShowApple(hdc);

		ReleaseDC(hWnd,hdc);
		break;
	}


	return DefWindowProc(hWnd,message,wParam,lParam);
}

void ShowBackGround(HDC hdc)
{
	//����������hdc
	HDC hdcmen = CreateCompatibleDC(hdc);
	//ѡ��һ��λͼ
	SelectObject(hdcmen,hBitmap_Background);
	//����
	BitBlt(hdc,0,0,600,600,hdcmen,0,0,SRCCOPY);
	//ɾ��������hdc
	DeleteDC(hdcmen);

	return;
}

void AddNode(int x,int y)
{
	Snake *pTemp = (Snake*)malloc(sizeof(Snake));
	pTemp->x = x;
	pTemp->y = y;
	pTemp->pLast = NULL;
	pTemp->pNext = NULL;

	if(pHead == NULL)
	{
		pHead = pTemp;
	}
	else
	{
		pTail->pNext = pTemp;
		pTemp->pLast = pTail;
	}
	pTail = pTemp;

	return;
}

void ShowSnake(HDC hdc)
{
	Snake *pMark = pHead->pNext;
	HDC hdcmen = CreateCompatibleDC(hdc);	
	//1.����ͷ
	switch (Direction)
	{
	case UP:
		SelectObject(hdcmen,hBitmap_SnakeHead_Up);
		break;
	case DOWN:
		SelectObject(hdcmen,hBitmap_SnakeHead_Down);
		break;
	case LEFT:
		SelectObject(hdcmen,hBitmap_SnakeHead_Left);
		break;
	case RIGHT:
		SelectObject(hdcmen,hBitmap_SnakeHead_Right);
		break;
	default:
		break;
	}
	BitBlt(hdc,pHead->x*30,pHead->y*30,30,30,hdcmen,0,0,SRCCOPY);

	//2.������
	SelectObject(hdcmen,hBitmap_SnakeBody);
	while(pMark != NULL)
	{
		BitBlt(hdc,pMark->x*30,pMark->y*30,30,30,hdcmen,0,0,SRCCOPY);
		pMark = pMark->pNext;
	}

	DeleteDC(hdcmen);

	return;
}

void Move()
{
	Snake *pMark = pTail;
	//1.���ƶ�����
	while(pMark != pHead)
	{
		pMark->x = pMark->pLast->x;
		pMark->y = pMark->pLast->y;

		pMark = pMark->pLast;
	}
	//2.�ƶ���ͷ
	switch (Direction)
	{
	case UP:
		pHead->y--;
		break;
	case DOWN:
		pHead->y++;
		break;
	case LEFT:
		pHead->x--;
		break;
	case RIGHT:
		pHead->x++;
		break;
	default:
		break;
	}

	return;
}

void ShowApple(HDC hdc)
{
	HDC hdcmen =  CreateCompatibleDC(hdc);
	SelectObject(hdcmen,hBitmap_Apple);
	BitBlt(hdc,apple.x*30,apple.y*30,30,30,hdcmen,0,0,SRCCOPY);
	DeleteDC(hdcmen);

	return;
}

BOOL IsEatApple()
{
	if(pHead->x == apple.x && pHead->y == apple.y)
	{
		return TRUE;
	}

	return FALSE;
}

void NewApple()
{
	Snake *pMark = pHead;
	//1.�������x,y   1~18
	int x;
	int y;

	do
	{
		x = rand() % 18 + 1;
		y = rand() % 18 + 1;
		//2.�ж��Ƿ�������
		pMark = pHead;
		while(pMark != NULL)
		{
			if(pMark->x == x && pMark->y == y)
			{
				break;
			}
			pMark = pMark->pNext;
		}

	}while(pMark != NULL);

	apple.x = x;
	apple.y = y;

	return;
}

BOOL IsBumpWall()
{
	if(pHead->x == 0 || pHead->x == 19 || pHead->y == 0 || pHead->y == 19)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsEatItself()
{
	Snake *pMark = pHead->pNext;

	while(pMark != NULL)
	{
		if(pMark->x == pHead->x && pMark->y == pHead->y)
		{
			return TRUE;
		}
		pMark = pMark->pNext;
	}

	return FALSE;
}