#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <ctime>

using namespace std;

//======================================================================
// в программе игрок играющий крестиками в массиве записывается как "1"
// а второй игрок или компьютер - нолик - записывается как "2"
// пустые клетки соответственно "0"
//======================================================================

//=== для изменения цвета текста в cmd =================
void SetColor(int text, int background) 
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//======================================================

//========= отрисовка поля =============================
int field(int f[15][15])
{
	system("cls");
	int count = 1;
	cout << "   1 2 3 4 5 6 7 8 9 A B C D E F" << endl;
	for (int Y = 0; Y < 15; Y++)
	{
		if (count < 10)
		{
			cout << count << " ";
		}
		else 
		{
			cout << count;
		}
			count++;
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 0)
			{
				cout << " .";
			}
			else {
				if (f[Y][X] == 1)
				{
					SetColor(4, 0);
					cout << " X";
					SetColor(15, 0);
				}
				else
				{
					SetColor(2, 0);
					cout << " O";
					SetColor(15, 0);
				}
			}
		}
		cout << endl;
	}
	cout << "   1 2 3 4 5 6 7 8 9 A B C D E F" << endl;
	return 0;
}
//======================================================

//==игорок крестик (основной)===========================
int player(int f[15][15])
{
	int key;
	int i = 0;
	do
	{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD с = { 0, 17+i };					
		SetConsoleCursorPosition(h, с);		//позиция для надписи после вывода поля
		cout <<"!ПЕРВЫЙ ИГРОК (Х)!" << endl << "Введите позиции для хода (горизонталь 1-15) (вертикаль 1-15)" << endl << "Для подтверждения введите <1>. Для отмены - любую другую клавишу" << endl;
		int turnX, turnY;
		
		//=======защита ввода 
		while (true)							
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY-1][turnX-1] != 0)) 
			{								//условие не позволяющее ввести что либо кроме чисел от 1 до 15, и уже введённыйх позиций
				cout << "НЕВЕРНЫЙ ВВОД (возможно эта позиция уже занята), попробуйте ещё раз: \n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}										
		//======конец защиты ввода

		COORD c = { (turnX*2)+1, turnY };			//показывает позицию хода игрока на поле
		SetConsoleCursorPosition(h, c);
		cin.clear();
		cin >> key;
		if (key == 1)
		{
			f[turnY-1][turnX-1] = 1;				//подтверждение хода
			break;
		}
	} while (true);
	return 0;
}
//======================================================

//==игрок нолик (второй)(копия первого)=================
int player2(int f[15][15])
{
	int key;
	int i = 0;
	do
	{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD с = { 0, 17 + i };
		SetConsoleCursorPosition(h, с);
		cout << "!ВТОРОЙ ИГРОК (О)!" << endl << "Введите позиции для хода (горизонталь 1-15) (вертикаль 1-15)." << endl << "Для подтверждения введите <2>.Для отмены - любую другую клавишу" << endl;
		int turnX, turnY;
		while (true)		
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY - 1][turnX - 1] != 0))
			{
				cout << "НЕВЕРНЫЙ ВВОД (возможно эта позиция уже занята), попробуйте ещё раз: \n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}						
		COORD c = { (turnX*2) + 1, turnY };
		SetConsoleCursorPosition(h, c);
		cin.clear();
		cin >> key;
		if (key == 2)
		{
			f[turnY - 1][turnX - 1] = 2;
			break;
		}
	} while (true);
	return 0;
}
//======================================================

//==== компьютер ход ===================================
int compRandAI(int f[15][15])
{
	int tempX = 0, tempY = 0;

	//=====================================проверка на 4 в ряд CВОИ ==============================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)	// проходим по массиву поля
		{
			if (f[Y][X] == 2)			//если нашли свой элемент равный 2 то проверяем возможность завершить ряд и победить
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 2) { count++; }
					else { break; }								// проверяет СТРОКУ
				}
				if (count == 4)	
				{
					if ((f[Y][X - 1] == 0) && (X > 0))
					{											//проверяем возможность поставить перед этим рядом (аналогично со всеми остальными подообными проверками)
						f[Y][X - 1] = 2;
						return 0;
					}
					else if ((f[Y][X + 4] == 0) && (X < 12))
					{											//проверяем возможнотьс поставить после этого ряда (аналогично со всеми остальными подообными проверками)
						f[Y][X + 4] = 2;
						return 0;
					}
				}

				//================================================
				
				count = 0;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y + temp][X] == 2) { count++; }
					else { break; }								//проверяет  СТОЛБЕЦ
				}
				if (count == 4)									
				{
					if ((f[Y - 1][X] == 0) && (Y > 0))
					{											//проверяем возможность поставить выше этого ряда (аналогично со всеми остальными подообными проверками)
						f[Y - 1][X] = 2;
						return 0;
					}
					else if ((f[Y + 4][X] == 0) && (Y < 12))
					{											//проверяем возможность поставить ниже этого ряда (аналогично со всеми остальными подообными проверками)
						f[Y + 4][X] = 2;
						return 0;
					}
				}

				//=================================================

				count = 0;
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 2)					//проверяет главную диагональ
					{
						count++;
						tempY++;
						tempX++;
					}
					else { break; }
				}
				if (count == 4)									
				{
					if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0))
					{  
						f[Y - 1][X - 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X + 4] == 0) && (X < 12) && (Y < 12))
					{
						f[Y + 4][X + 4] = 2;
						return 0;
					}
				}

				//=================================================

				count = 0;
				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 2)					//проверяет побочную диагональ
					{
						count++;
						tempY++;
						tempX--;
					}
					else { break; }
				}
				if (count == 4)											
				{
					if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0))
					{
						f[Y - 1][X + 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X - 4] == 0) && (X > 3) && (Y < 12))
					{
						f[Y + 4][X - 4] = 2;
						return 0;
					}
				}
			}
		}
	}

	//========================== проверка на 4 в ряд у соперника ===========================================

	tempX = 0;
	tempY = 0;
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 1)					//если нашли элемент равный 1 то начинаем проверять от него направления
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 1) { count++; }
					else { break; }								// проверяет СТРОКУ
				}
				if (count == 4)									
				{
					if ((f[Y][X - 1] == 0) && (X > 0))
					{
						f[Y][X - 1] = 2;
						return 0;
					}
					else if ((f[Y][X + 4] == 0) && (X < 12))
					{
						f[Y][X + 4] = 2;
						return 0;
					}
				}

				//===============================================

				count = 0;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y + temp][X] == 1) { count++; }
					else { break; }								//проверяет  СТОЛБЕЦ
				}
				if (count == 4)									
				{
					if ((f[Y - 1][X] == 0) && (Y > 0))
					{
						f[Y - 1][X] = 2;
						return 0;
					}
					else if ((f[Y + 4][X] == 0) && (Y < 12))
					{
						f[Y + 4][X] = 2;
						return 0;
					}
				}

				//===================================================

				count = 0;
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 1)					//проверяет главную диагональ
					{
						count++;
						tempY++;
						tempX++;
					}
					else { break; }
				}
				if (count == 4)								
				{
					if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0))
					{
						f[Y - 1][X - 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X + 4] == 0) && (X < 12) && (Y < 12))
					{
						f[Y + 4][X + 4] = 2;
						return 0;
					}
				}

				//=======================================================
				
				count = 0;
				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[tempY][tempX] == 1)						//проверяет побочную диагональ
					{
						count++;
						tempY++;
						tempX--;
					}
					else { break; }
				}
				if (count == 4)										
				{
					if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0))
					{
						f[Y - 1][X + 1] = 2;
						return 0;
					}
					else if ((f[Y + 4][X - 4] == 0) && (X > 3) && (Y < 12))
					{
						f[Y + 4][X - 4] = 2;
						return 0;
					}
				}
			}
		}
	}

	//================== проверка на ХХ_ХХ ====================================
		
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++) 
		{
			int count = 0;

			for (int temp = 0; temp < 5; temp++)			//проверка СТОКИ
			{
				if (f[Y][X + temp] == 1) { count++; }
			}
			if (count == 4)			
			{
				if (f[Y][X + 1] == 0)						// X_XXX
				{
					f[Y][X + 1] = 2;
					return 0;
				}
				else if (f[Y][X + 2] == 0)					// XX_XX
				{
					f[Y][X + 2] = 2;
					return 0;
				}
				else if (f[Y][X + 3] == 0)					// XXX_X 
				{
					f[Y][X + 3] = 2;
					return 0;
				}
			}

			//==================================================
			
			count = 0;
			for (int temp = 0; temp < 5; temp++)
			{
				if (f[Y + temp][X] == 1) { count++; }
														//проверяет  СТОЛБЕЦ
			}
			if (count == 4){
				if (f[Y + 1][X] == 0)					// X_XXX
				{
					f[Y + 1][X] = 2;
					return 0;
				}
				else if (f[Y + 2][X] == 0)				// XX_XX
				{
					f[Y + 2][X] = 2;
					return 0;
				}
				else if (f[Y + 3][X] == 0)				// XXX_X 
				{
					f[Y + 3][X] = 2;
					return 0;
				}
			}

			//===============================================

			count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 5; temp++)
			{
				if (f[tempY][tempX] == 1)				//проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
			}

			if (count == 4)
			{
				if (f[Y + 1][X + 1] == 0)
				{
					f[Y + 1][X + 1] = 2;
					return 0;
				}
				else if (f[Y + 2][X + 2] == 0)
				{
					f[Y + 2][X + 2] = 2;
					return 0;
				}
				else if (f[Y + 3][X + 3] == 0)
				{
					f[Y + 3][X + 3] = 2;
					return 0;
				}
			}

			//=========================================================
			
			count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 5; temp++)
			{
				if (f[tempY][tempX] == 1)			//проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}		
			}
			if (count == 4){

				if (f[Y - 1][X + 1] == 0)
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if (f[Y - 2][X + 2] == 0)
				{
					f[Y - 2][X + 2] = 2;
					return 0;
				}
				else if (f[Y - 3][X + 3] == 0)
				{
					f[Y - 3][X + 3] = 2;
					return 0;
				}
			}
		}
	}

	// ======================== проверка на 3 в ряд у соперника ==================================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			//======================================================
			
			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 1) { count++; }
				else { break; }								// проверяет СТРОКУ
			}
			if (count == 3)							
			{
				if ((f[Y][X - 1] == 0) && (X > 0))
				{
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 3] == 0) && (X < 13))
				{
					f[Y][X + 3] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y + temp][X] == 1) { count++; }
				else { break; }								//проверяет  СТОЛБЕЦ
			}
			if (count == 3)							
			{
				if ((f[Y - 1][X] == 0) && (Y > 0))
				{
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 3][X] == 0) && (Y < 13))
				{
					f[Y + 3][X] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 1)					//проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 3)										
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0))
				{
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X + 3] == 0) && (X < 13) && (Y < 13))
				{
					f[Y + 3][X + 3] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 1)					//проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 3)											
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0))
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X - 3] == 0) && (X > 2) && (Y < 13))
				{
					f[Y + 3][X - 3] = 2;
					return 0;
				}
			}
		}
	}

	//====================== если не надо защищаться то =========================

	// ============================== ищет 3 в ряд свои =========================
	
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{

			//======================================================

			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }								// проверяет СТРОКУ
			}
			if (count == 3)							
			{
				if ((f[Y][X - 1] == 0) && (X > 0))
				{
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 3] == 0) && (X < 13))
				{
					f[Y][X + 3] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y + temp][X] == 2) { count++; }
				else { break; }								//проверяет  СТОЛБЕЦ
			}
			if (count == 3)							
			{
				if ((f[Y - 1][X] == 0) && (Y > 0))
				{
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 3][X] == 0) && (Y < 13))
				{
					f[Y + 3][X] = 2;
					return 0;
				}
			}
			
			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 2)					//проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 3)									
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0))
				{
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X + 3] == 0) && (X < 13) && (Y < 13))
				{
					f[Y + 3][X + 3] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[tempY][tempX] == 2)						//проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 3)
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0))
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 3][X - 3] == 0) && (X > 2) && (Y < 13))
				{
					f[Y + 3][X - 3] = 2;
					return 0;
				}
			}
		}
	}

	// ======================== ищет 2 в ряд у себя ===================================
	
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			
			//======================================================

			int count = 0;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }									// проверяет СТРОКУ
			}
			if (count == 2)							
			{
				if ((f[Y][X - 1] == 0) && (X > 0))
				{
					f[Y][X - 1] = 2;
					return 0;
				}
				else if ((f[Y][X + 2] == 0) && (X < 14))
				{
					f[Y][X + 2] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[Y + temp][X] == 2) { count++; }
				else { break; }									//проверяет  СТОЛБЕЦ
			}
			if (count == 2)							
			{
				if ((f[Y - 1][X] == 0) && (Y > 0))
				{
					f[Y - 1][X] = 2;
					return 0;
				}
				else if ((f[Y + 2][X] == 0) && (Y < 14))
				{
					f[Y + 2][X] = 2;
					return 0;
				}
			}
			
			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[tempY][tempX] == 2)						 //проверяет главную диагональ
				{
					count++;
					tempY++;
					tempX++;
				}
				else { break; }
			}
			if (count == 2)											
			{
				if ((f[Y - 1][X - 1] == 0) && (X > 0) && (Y > 0))
				{
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if ((f[Y + 2][X + 2] == 0) && (X < 14) && (Y < 14))
				{
					f[Y + 2][X + 2] = 2;
					return 0;
				}
			}

			//======================================================

			int count = 0;
			tempY = Y;
			tempX = X;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[tempY][tempX] == 2)							//проверяет побочную диагональ
				{
					count++;
					tempY++;
					tempX--;
				}
				else { break; }
			}
			if (count == 2)											
			{
				if ((f[Y - 1][X + 1] == 0) && (X < 15) && (Y>0))
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
				else if ((f[Y + 2][X - 2] == 0) && (X > 1) && (Y < 14))
				{
					f[Y + 2][X - 2] = 2;
					return 0;
				}
			}
		}
	}

	// === если нет возможности поставить даже к 2м своим то ====

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 2)					//ищем CВОЮ точку и ходим в сторону от неё
			{
				if (f[Y][X + 1] == 0)
				{
					f[Y][X + 1] = 2;
					return 0;
				}
				else if (f[Y + 1][X + 1] == 0)
				{
					f[Y + 1][X + 1] = 2;
					return 0;
				}
				else if (f[Y + 1][X] == 0)
				{
					f[Y + 1][X] = 2;
					return 0;
				}
				else if (f[Y + 1][X - 1] == 0)
				{
					f[Y + 1][X - 1] = 2;
					return 0;
				}
				else if (f[Y][X - 1] == 0)
				{
					f[Y][X - 1] = 2;
					return 0;
				}
				else if (f[Y - 1][X - 1] == 0)
				{
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if (f[Y - 1][X] == 0)
				{
					f[Y - 1][X] = 2;
					return 0;
				}
				else if (f[Y - 1][X + 1] == 0)
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
			}
		}
	}

	// если вообще некуда ходить

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 1)			//ищем точку СОПЕРНИКА и ходим в сторону от неё
			{
				if (f[Y][X + 1] == 0)
				{
					f[Y][X + 1] = 2;
					return 0;
				}
				else if (f[Y + 1][X + 1] == 0)
				{
					f[Y + 1][X + 1] = 2;
					return 0;
				}
				else if (f[Y + 1][X] == 0)
				{
					f[Y + 1][X] = 2;
					return 0;
				}
				else if (f[Y + 1][X - 1] == 0)
				{
					f[Y + 1][X - 1] = 2;
					return 0;
				}
				else if (f[Y][X - 1] == 0)
				{
					f[Y][X - 1] = 2;
					return 0;
				}
				else if (f[Y - 1][X - 1] == 0)
				{
					f[Y - 1][X - 1] = 2;
					return 0;
				}
				else if (f[Y - 1][X] == 0)
				{
					f[Y - 1][X] = 2;
					return 0;
				}
				else if (f[Y - 1][X + 1] == 0)
				{
					f[Y - 1][X + 1] = 2;
					return 0;
				}
			}
		}
	}
}
//======================================================

//==========проверка на выигрыш=========================
int check_for_win(int f[15][15])
{
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)			// проходим по полю
		{
			if (f[Y][X] != 0)					// если нашли элемент не равный 0 то начинаем проверять от него направления
			{
				int check_point = f[Y][X];		// сохраняем проверяемое значение
				
				//-----------------проверяет выигрышная ли СТРОКА--------------------
				
				int count = 0;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y][X+temp] == check_point) { count++; }	else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				
				// ---------------------проверяет выигрышний ли СТОЛБЕЦ--------------

				count = 0;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y+temp][X] == check_point) {count++;} else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				
				//----------------------проверяет ГЛАВНУЮ диагональ------------------

				count = 0;
				int tempY = Y;
				int tempX = X;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[tempY][tempX] == check_point) 
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
				
				// ------------------проверяет ПОБОЧНУЮ ДИАГОНАЛЬ---------------------

				count = 0;
				tempY = Y;
				tempX = X;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[tempY][tempX] == check_point) 
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
		for (int X = 0; X < 15; X++)	   //создание поля
			field_mass[Y][X] = 0;
	//----------------------------------------------------
	int winner = 0;
	int menu_key;
	while (true)
	{
		system("cls");
		cout << "=================================== РЕНДЗЮ =====================================" << endl << endl;
		cout << "против кого играем?" << endl;
		std::cout << "1 :игрок против компьютера" << std::endl;
		std::cout << "2 :два игрока" << std::endl;
		std::cout << ">";

		//=========защита ввода выбора с кем играть============
		while (true)			
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
		//=========защита ввода выбора с кем играть============

		switch (menu_key)
		{
		case 1:
		{
			while (true)
			{
				field(field_mass);
				player(field_mass);
				field(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 1)					//проверка выиграл ли после своего хода
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD с = { 0, 21 };
					SetConsoleCursorPosition(h, с);
					SetColor(4, 0);
					cout << "====================== ";
					cout << "Вы победили!";
					cout << " ======================";
					break;
				}
				compRandAI(field_mass);
				field(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 2)
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD c = { 0, 21 };
					SetConsoleCursorPosition(h, c);
					SetColor(2, 0);
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
				field(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 1)
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD c = { 0, 21 };
					SetConsoleCursorPosition(h, c);
					SetColor(4, 0);
					cout << "====================== ";
					cout << "Победил первый игорок (Х)!!";
					cout << " ======================";
					break;

				}
				field(field_mass);
				player2(field_mass);
				field(field_mass);
				winner = check_for_win(field_mass);
				if (winner == 2)
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD c = { 0, 21 };
					SetConsoleCursorPosition(h, c);
					SetColor(2, 0);
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
