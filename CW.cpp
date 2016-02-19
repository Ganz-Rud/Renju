#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <ctime>

using namespace std;


int field(int f[15][15])
{
	system("cls");
	cout << " 1 2 3 4 5 6 7 8 9 A B C D E F" << endl;
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++){
			if (f[i][j] == 0)
			{
				cout << " +";
			}
			else {
				if (f[i][j] == 1){
					cout << " 1";
				}
				else
				{
					cout << " 2";
				};
			}
		}
		cout << endl;
	}
		
	return 0;
}

//======================================================
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
		cout << "Enter the pos of your turn (1-15) (1-15)" << endl;
		int turnX, turnY;
		cin >> turnX;
		cin >> turnY;
		COORD c = { (turnX*2)-1, turnY };
		SetConsoleCursorPosition(h, c);
		cin >> key;
		if (key == 1){
			f[turnY-1][turnX-1] = 1;
			break;
		}
	} while (true);
	return 0;
}

//======================================================
//======================================================

int comp(int f[15][15])
{
	int tempX, tempY;
	while (true)
	{
		srand(time(0));
		tempX = rand() % 15;
		tempY = rand() % 15;
		if (f[tempX][tempY] == 0)
		{
			f[tempY][tempX] = 2;
			return 0;
		}
	}
}

//======================================================
//======================================================

int check_for_win(int f[15][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)// проходим по массиву поля
		{
			if (f[i][j] != 0)	//если нашли элемент не равный 0 то начинаем проверять от него направления
			{
				int count = 0; 
				int check_point = f[i][j]; // сохраняем проверяемое значение
				
				//-----------------
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[i][j+temp] == check_point) { count++; }	else { break; } // проверяет выигрышная ли СТРОКА
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
					if (f[i+temp][j] == check_point) {count++;} else { break; }	//проверяет выигрышний ли СТОЛБЕЦ
				}
				if (count == 5)
				{
					return check_point;
				}
				//cout << "===2===" << endl;
				//system("pause");
				//----------------------

				count = 0;
				int tempY = i;
				int tempX = j;
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

				tempY = i;
				tempX = j;
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


int main()
{
	//----------------------------------------------------
	int field_mass[15][15];
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)		//создание поля
			field_mass[i][j] = 0;
	//----------------------------------------------------
	int winner =0;

	while (true)
	{
		field(field_mass);
		player(field_mass);
		winner = check_for_win(field_mass);

		comp(field_mass);
		winner = check_for_win(field_mass);
		if (winner == 1)
		{
			cout << "You WIN!";
			break;
		}
		else if (winner == 2)
		{
			cout << "Computer Win :c";
			break;
		}
	}
	cin.get();
	cout << endl << endl << endl;
	system("pause");
	return 0;
}
