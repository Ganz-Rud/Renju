#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <ctime>

using namespace std;

//==отрисовка поля - готово=============================
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

//==игорок крестик (основной) - готово =================
int player(int f[15][15])
{
	int key;
	int i = 0;
	do{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD start = { 0, 16+i };
		SetConsoleCursorPosition(h, start);
		cout <<"!ПЕРВЫЙ ИГРОК (Х)!" << endl << "Введите позиции для хода (горизонталь 1-15) (вертикаль 1-15)" <<endl << "Для подтверждения введите <1>. Для отмены - любую другую клавишу" << endl;
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

//==игрок нолик (второй) - готов =======================
int player2(int f[15][15])
{
	int key;
	int i = 0;
	do{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD start = { 0, 16 + i };
		SetConsoleCursorPosition(h, start);
		cout << "!ВТОРОЙ ИГРОК (О)!" << endl << "Введите позиции для хода (горизонталь 1-15) (вертикаль 1-15)." << endl << "Для подтверждения введите <2>.Для отмены - любую другую клавишу" << endl;
		int turnX, turnY;
		while (true)			//===============защита ввода 
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY - 1][turnX - 1] != 0))
			{
				cout << "неверный ввод, возможно эта позиция занята, попробуйте ещё раз: \n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}						//===============защита ввода
		COORD c = { (turnX * 2) - 1, turnY };
		SetConsoleCursorPosition(h, c);
		cin.clear();
		cin >> key;
		if (key == 2){
			f[turnY - 1][turnX - 1] = 2;
			break;
		}
	} while (true);
	return 0;
}
//======================================================

//====компьютер ход (нолик) ============================
int compRandAI(int f[15][15])
{
	int tempX = 0, tempY = 0;

	//=====================================проверка на 4 в ряд свои==============================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)// проходим по массиву поля
		{
			if (f[Y][X] == 2)	//если нашли элемент равный 1 то начинаем проверять от него направления
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 2) { count++; }
					else { break; }							// проверяет СТРОКУ
				}
				if (count == 4)									//строка. 4
				{
					if ((f[Y][X - 1] == 0) && (X > 0)){
						f[Y][X - 1] = 2;
						return 0;
					}
					else if ((f[Y][X + 4] == 0) && (X < 12)){
						f[Y][X + 4] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y + temp][X] == 2) { count++; }
					else { break; }	//проверяет  СТОЛБЕЦ
				}
				if (count == 4)									//столбец 4
				{
					if ((f[Y - 1][X] == 0) && (Y > 0)){
						f[Y - 1][X] = 2;
						return 0;
					}
					else if ((f[Y + 4][X] == 0) && (Y < 12)){
						f[Y + 4][X] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 2) //проверяет главную диагональ
					{
						count++;
						tempY++;
						tempX++;
					}
					else { break; }
				}
				if (count == 4)											//главная 4
				{
					if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0)){
						f[Y - 1][X - 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X + 4] == 0) && (X < 12) && (Y < 12)){
						f[Y + 4][X + 4] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 2) //проверяет побочную диагональ
					{
						count++;
						tempY++;
						tempX--;
					}
					else { break; }
				}
				if (count == 4)											//побочная 4
				{
					if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0)){
						f[Y - 1][X + 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X - 4] == 0) && (X > 3) && (Y < 12)){
						f[Y + 4][X - 4] = 2;
						return 0;
					}
				}
			}
		}
	}
	tempX = 0;
	tempY = 0;
	//==========================проверка на 4 противника ===========================================
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)// проходим по массиву поля
		{
			if (f[Y][X] == 1)	//если нашли элемент равный 1 то начинаем проверять от него направления
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 1) { count++; }
					else { break; }							// проверяет СТРОКУ
				}
				if (count == 4)									//строка. 4
				{
					if ((f[Y][X - 1] == 0) && (X > 0)){
						f[Y][X - 1] = 2;
						return 0;
					}
					else if ((f[Y][X + 4] == 0) && (X < 12)){
						f[Y][X + 4] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y + temp][X] == 1) { count++; }
					else { break; }	//проверяет  СТОЛБЕЦ
				}
				if (count == 4)									//столбец 4
				{
					if ((f[Y - 1][X] == 0) && (Y > 0)){
						f[Y - 1][X] = 2;
						return 0;
					}
					else if ((f[Y + 4][X] == 0) && (Y < 12)){
						f[Y + 4][X] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 1) //проверяет главную диагональ
					{
						count++;
						tempY++;
						tempX++;
					}
					else { break; }
				}
				if (count == 4)											//главная 4
				{
					if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0)){
						f[Y - 1][X - 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X + 4] == 0) && (X < 12) && (Y < 12)){
						f[Y + 4][X + 4] = 2;
						return 0;
					}
				}
				//===============
				count = 0;
				//===============
				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 1) //проверяет побочную диагональ
					{
						count++;
						tempY++;
						tempX--;
					}
					else { break; }
				}
				if (count == 4)											//побочная 4
				{
					if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0)){
						f[Y - 1][X + 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X - 4] == 0) && (X > 3) && (Y < 12)){
						f[Y + 4][X - 4] = 2;
						return 0;
					}
				}
			}
		}
	}

	//======================== проверка на 3 ==================================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++) // проходим по массиву поля
		{
			//===============
			int count = 0;
			//===============
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 1) { count++; }
				else { break; }							// проверяет СТРОКУ
			}
			if (count == 3)							//строка 3
			{
				if ((f[Y][X - 1] == 0) && (X > 0)){
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 3] == 0) && (X < 13)){
					f[Y][X + 3] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y + temp][X] == 1) { count++; }
				else { break; }	//проверяет  СТОЛБЕЦ
			}
			if (count == 3)							//столбец 3
			{
				if ((f[Y - 1][X] == 0) && (Y > 0)){
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 3][X] == 0) && (Y < 13)){
					f[Y + 3][X] = 2;
					return 0;
				}
			}
			//===============
			count = 0;
			//===============
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 1) //проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 3)											//главная 3
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0)){
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X + 3] == 0) && (X < 13) && (Y < 13)){
					f[Y + 3][X + 3] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============

			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 1) //проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 3)											//побочная 3
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0)){
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X - 3] == 0) && (X > 2) && (Y < 13)){
					f[Y + 3][X - 3] = 2;
					return 0;
				}
			}
		}
	}

	//============если не надо защищаться то=====================================
	// ========== ищет 3 в ряд свои==========================
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++) // проходим по массиву поля
		{
			//===============
			int count = 0;
			//===============
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }							// проверяет СТРОКУ
			}
			if (count == 3)							//строка 3
			{
				if ((f[Y][X - 1] == 0) && (X > 0)){
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 3] == 0) && (X < 13)){
					f[Y][X + 3] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y + temp][X] == 2) { count++; }
				else { break; }	//проверяет  СТОЛБЕЦ
			}
			if (count == 3)							//столбец 3
			{
				if ((f[Y - 1][X] == 0) && (Y > 0)){
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 3][X] == 0) && (Y < 13)){
					f[Y + 3][X] = 2;
					return 0;
				}
			}
			//===============
			count = 0;
			//===============
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 2) //проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 3)											//главная 3
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0)){
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X + 3] == 0) && (X < 13) && (Y < 13)){
					f[Y + 3][X + 3] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============

			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 2) //проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 3)											//побочная 3
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0)){
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X - 3] == 0) && (X > 2) && (Y < 13)){
					f[Y + 3][X - 3] = 2;
					return 0;
				}
			}
		}
	}
	// ======================== ищет 2 в ряд у себя ===================================
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++) // проходим по массиву поля
		{
			//===============
			int count = 0;
			//===============
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }							// проверяет СТРОКУ
			}
			if (count == 2)							//строка 2
			{
				if ((f[Y][X - 1] == 0) && (X > 0)){
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 2] == 0) && (X < 14)){
					f[Y][X + 2] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[Y + temp][X] == 2) { count++; }
				else { break; }	//проверяет  СТОЛБЕЦ
			}
			if (count == 2)							//столбец 2
			{
				if ((f[Y - 1][X] == 0) && (Y > 0)){
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 2][X] == 0) && (Y < 14)){
					f[Y + 2][X] = 2;
					return 0;
				}
			}
			//===============
			count = 0;
			//===============
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[tempY][tempX] == 2) //проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 2)											//главная 2
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0)){
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 2][X + 2] == 0) && (X < 14) && (Y < 14)){
					f[Y + 2][X + 2] = 2;
					return 0;
				}
			}

			//===============
			count = 0;
			//===============

			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[tempY][tempX] == 2) //проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 2)											//побочная 2
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0)){
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 2][X - 2] == 0) && (X > 1) && (Y < 14)){
					f[Y + 2][X - 2] = 2;
					return 0;
				}
			}
		}
	}

	// === если нет и на 2 то ====
	int count = 0;
	for (int R = 0; R < 15; R++){
		for (int Q = 0; Q < 15; Q++){
			if (f[R][Q] == 2)		//посчитаем сколько у нас уже стоит точек
			{
				count++;
			}
		}
	}
	if (count == 0) //если ноль то рандомно тыкаем в любую часть поля
	{
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
	else 
	{												//если не ноль то ходим куда ниубудь рядом
		for (int Z = 0; Z < 15; Z++){
			for (int V = 0; V < 15; V++){
				if ((f[Z][V] == 2) && (f[Z+1][V] == 0))
				{
					f[Z+1][V] = 2;
					return 0;
				}
				else if ((f[Z][V] == 2) && (f[Z - 1][V] == 0))
				{
					f[Z-1][V] = 2;
					return 0;
				}
				else if ((f[Z][V] == 2) && (f[Z][V-1] == 0))
				{
					f[Z][V - 1] = 2;
					return 0;
				}
				else if ((f[Z][V] == 2) && (f[Z][V+1] == 0))
				{
					f[Z][V + 1] = 2;
					return 0;
				}
			}
		}
	}
}
//======================================================


//отрисовка поля готова=================================
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
				
				// -----------------------
				count = 0;
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
	int winner = 0;
	cout << "против кого играем?" <<endl;
	int counter;
	int menu_key;
	while (1)
	{
		system("cls");
		std::cout << "1 :игрок против компьютера" << std::endl;
		std::cout << "2 :два игрока" << std::endl;
		std::cout << ">";
		while (true)			//===============защита ввода выбор с кем играть
		{
			std::cin >> menu_key;
			if ((!menu_key) || (menu_key < 1) || (menu_key > 2))
			{
				cout << "выберете первый или второй пункт" << endl << ">";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}
		
		switch (menu_key)
		{
		case 1:
		{
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
				compRandAI(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 2)
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD start = { 0, 21 };
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
		case 2:
		{
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
					cout << "Победил первый игорок (Х)!!";
					cout << " ======================";
					break;

				}
				field(field_mass);
				player2(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 2)
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD start = { 0, 21 };
					SetConsoleCursorPosition(h, start);
					cout << "====================== ";
					cout << "Победил второй игрок (О)!!";
					cout << " ======================";
					break;
				}
			}
			cin.get();
			cout << endl << endl << endl;
			system("pause");
			return 0;
		}
		}
	}
}
