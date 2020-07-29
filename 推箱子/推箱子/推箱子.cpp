#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int map[7][10] = {

{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0 },

{ 0, 1, 1, 1, 0, 0, 0, 0, 1, 0 },

{ 1, 1, 3, 0, 4, 1, 1, 0, 1, 1 },

{ 1, 3, 3, 4, 0, 4, 0, 0, 0, 1 },

{ 1, 3, 3, 0, 4, 0, 4, 0, 1, 1 },

{ 1, 1, 1, 1, 1, 1, 0, 5, 1, 0 },

{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 } };

void DrawMap()
{

	for (int i = 0; i < 7; i ++)
	{
		for (int j = 0; j < 10; j ++)
		{
			switch (map[i][j])
			{
			case 0:
				cout <<"  ";
				break;
			case 1:
				cout <<"■";
				break;
			case 3:
				cout <<"☆";
				break;
			case 4:
				cout <<"□";
				break;
			case 5:
				cout <<"▲";
				break;
			case 7: //4+3 箱子+目的地
				cout << "★";
				break;
			case 8: //5+3 人+目的地
				cout << "▲";
				break;
			}
		}
		cout << endl;
	}
}

void PlayGame()
{
	int row, col; //人的行 和 列
	for (int i = 0; i < 7; i ++) 
	{
		for (int j = 0; j < 10; j ++) 
		{
			if (map[i][j] == 5 || map[i][j] == 8)
			{
				row = i; //i 0-6
				col = j; //j 0-9
			}
		}
	}

	cout << "坐标 (" << row + 1 << "," << col + 1 << ")" << endl;

	//wasd 字符  char
	char input; 
	input = _getch(); 
	switch (input)
	{
		//人能走的情况:
		//1.人的前面是空地.
		//2.人的前面是目的地.
		//3.人的前面是箱子,箱子的前面是空地.
		//4.人的前面是箱子,箱子的前面是目的地.
		
	case 'w': //上
		if (map[row - 1][col] == 0 || map[row - 1][col] == 3) //如果人的前面是空地或者目的地
		{
			map[row][col] -= 5; //人的ID有可能是5 也有可能是8
			map[row - 1][col] += 5;
		}

		else if (map[row - 1][col] == 4 || map[row - 1][col] == 7)//人的前面是箱子
		{
			if (map[row - 2][col] == 0 || map[row - 2][col] == 3)//箱子的前面是空地
			{
				map[row - 2][col] += 4;
				map[row - 1][col] += 1;
				map[row][col] -= 5;
			}
		}
		break;

	case 's': //下
		if (map[row + 1][col] == 0 || map[row + 1][col] == 3) //如果人的前面是空地或者目的地
		{
			map[row][col] -= 5; //人的ID有可能是5 也有可能是8
			map[row + 1][col] += 5;
		}

		else if (map[row + 1][col] == 4 || map[row + 1][col] == 7)//人的前面是箱子
		{
			if (map[row + 2][col] == 0 || map[row + 2][col] == 3)//箱子的前面是空地
			{
				map[row + 2][col] += 4;
				map[row + 1][col] += 1;
				map[row][col] -= 5;
			}
		}
		break;
	case 'a': //左
		if (map[row][col - 1] == 0 || map[row][col - 1] == 3) //如果人的前面是空地或者目的地
		{
			map[row][col] -= 5; //人的ID有可能是5 也有可能是8
			map[row][col - 1] += 5;
		}

		else if (map[row][col - 1] == 4 || map[row][col - 1] == 7)//人的前面是箱子
		{
			if (map[row][col - 2] == 0 || map[row][col - 2] == 3)//箱子的前面是空地
			{
				map[row][col - 2] += 4;
				map[row][col - 1] += 1;
				map[row][col] -= 5;
			}
		}
		break;
	case 'd': //右
		if (map[row][col + 1] == 0 || map[row][col + 1] == 3) //如果人的前面是空地或者目的地
		{
			map[row][col] -= 5; //人的ID有可能是5 也有可能是8
			map[row][col + 1] += 5;
		}
		else if (map[row][col + 1] == 4 || map[row][col + 1] == 7)//人的前面是箱子
		{
			if (map[row][col + 2] == 0 || map[row][col + 2] == 3)//箱子的前面是空地
			{
				map[row][col + 2] += 4;
				map[row][col + 1] += 1;
				map[row][col] -= 5;
			}
		}
		break;
		break;
	}

}

int main()
{

	//system("mode con cols=40 lines=20");

	while (1)
	{
		system("cls");

		DrawMap();

		PlayGame();
	}
	return 0;
}
