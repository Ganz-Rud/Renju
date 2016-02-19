#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <ctime>

using namespace std;

int field(int f[15][15])
{
	system("cls");
	cout << " 1 2 3 4 5 6 7 8 9 A B C D E F" << endl;
	for (int Y = 0; Y < 15; Y++){
		for (int X = 0; X < 15; X++){
			if (f[Y][X] == 0)
			{
				cout << " .";
			}
			else {
				if (f[Y][X] == 1)
				{
					cout << " X";
				}
				else
				{
					cout << " O";
				};
			}
		}
		cout << endl;
	}
		
	return 0;
}

//======================================================

int player(int f[15][15])
{
	int key;
	int i = 0;
	do{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD start = { 0, 16+i };
		SetConsoleCursorPosition(h, start);
		cout << "Введите позиции для хода (1-15) (1-15). Для подтверждения введите <1>. Для отмены - любую другую клавишу" << endl;
		int turnX, turnY;
		while (true)			//===============защита ввода 
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY-1][turnX-1] != 0))
			{
				cout << "неверный ввод, возможно эта позиция занята, попробуйте ещё раз: \n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}						//===============защита ввода
		COORD c = { (turnX*2)-1, turnY };
		SetConsoleCursorPosition(h, c);
		cin.clear();
		cin >> key;
		if (key == 1){
			f[turnY-1][turnX-1] = 1;
			break;
		}
	} while (true);
	return 0;
}

//======================================================

int compRand(int f[15][15])
{
	int tempX, tempY;
	while (true)
	{
		srand(time(0));
		tempX = rand() % 15;
		tempY = rand() % 15;
		if ((f[tempX][tempY] == 0) || (f[tempX][tempY] != 1))
		{
			f[tempY][tempX] = 2;
			return 0;
		}
	}
}

//======================================================

int check_for_win(int f[15][15])
{
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)// проходим по массиву поля
		{
			if (f[Y][X] != 0)	//если нашли элемент не равный 0 то начинаем проверять от него направления
			{
				int count = 0; 
				int check_point = f[Y][X]; // сохраняем проверяемое значение
				
				//-----------------
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y][X+temp] == check_point) { count++; }	else { break; } // проверяет выигрышная ли СТРОКА
				}
				if (count == 5)
				{
					return check_point;
				}
				//cout << "===1==="<< endl;
				//system("pause");
				// ---------------------

				count = 0;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y+temp][X] == check_point) {count++;} else { break; }	//проверяет выигрышний ли СТОЛБЕЦ
				}
				if (count == 5)
				{
					return check_point;
				}
				//cout << "===2===" << endl;
				//system("pause");
				//----------------------

				count = 0;
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[tempY][tempX] == check_point) //проверяет главную диагональ
					{ 
						count++; 
						tempY++;
						tempX++;
					} 
					else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				//cout << "===3===" << endl;
				//system("pause");
				// -----------------------

				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[tempY][tempX] == check_point) //проверяет побочную диагональ
					{
						count++;
						tempY++;
						tempX--;
					}
					else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				//cout << "===4===" << endl;
				//system("pause");
			}
		}
	}
	return 0;
}

//======================================================

int main()
{
	setlocale(LC_CTYPE, "Russian");
	//----------------------------------------------------
	int field_mass[15][15];
	for (int Y = 0; Y < 15;Y++)
		for (int X = 0; X < 15; X++)		//создание поля
			field_mass[Y][X] = 0;
	//----------------------------------------------------
	int winner =0;

	while (true)
	{
		field(field_mass);
		player(field_mass);
		winner = check_for_win(field_mass);
		if (winner == 1)
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD start = { 0, 21 };
			SetConsoleCursorPosition(h, start);
			cout << "====================== ";
			cout << "Вы победили!";
			cout << " ======================";
			break;
		}

		compRand(field_mass);
		winner = check_for_win(field_mass);
		if (winner == 2)
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD start = { 0, 21};
			SetConsoleCursorPosition(h, start);
			cout << "====================== ";
			cout << "Победил компьютер :c";
			cout << " ======================";
			break;
		}
	}
	cin.get();
	cout << endl << endl << endl;
	system("pause");
	return 0;
}
