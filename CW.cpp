#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <ctime>

using namespace std;

//======================================================================
// � ��������� ����� �������� ���������� � ������� ������������ ��� "1"
// � ������ ����� ��� ��������� - ����� - ������������ ��� "2"
// ������ ������ �������������� "0"
//======================================================================

//=== ��� ��������� ����� ������ � cmd =================
void SetColor(int text, int background) 
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//======================================================

//========= ��������� ���� =============================
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

//==������ ������� (��������)===========================
int player(int f[15][15])
{
	int key;
	int i = 0;
	do
	{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD � = { 0, 17+i };					
		SetConsoleCursorPosition(h, �);		//������� ��� ������� ����� ������ ����
		cout <<"!������ ����� (�)!" << endl << "������� ������� ��� ���� (����������� 1-15) (��������� 1-15)" << endl << "��� ������������� ������� <1>. ��� ������ - ����� ������ �������" << endl;
		int turnX, turnY;
		
		//=======������ ����� 
		while (true)							
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY-1][turnX-1] != 0)) 
			{								//������� �� ����������� ������ ��� ���� ����� ����� �� 1 �� 15, � ��� ��������� �������
				cout << "�������� ���� (�������� ��� ������� ��� ������), ���������� ��� ���: \n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}										
		//======����� ������ �����

		COORD c = { (turnX*2)+1, turnY };			//���������� ������� ���� ������ �� ����
		SetConsoleCursorPosition(h, c);
		cin.clear();
		cin >> key;
		if (key == 1)
		{
			f[turnY-1][turnX-1] = 1;				//������������� ����
			break;
		}
	} while (true);
	return 0;
}
//======================================================

//==����� ����� (������)(����� �������)=================
int player2(int f[15][15])
{
	int key;
	int i = 0;
	do
	{
		i++;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD � = { 0, 17 + i };
		SetConsoleCursorPosition(h, �);
		cout << "!������ ����� (�)!" << endl << "������� ������� ��� ���� (����������� 1-15) (��������� 1-15)." << endl << "��� ������������� ������� <2>.��� ������ - ����� ������ �������" << endl;
		int turnX, turnY;
		while (true)		
		{
			cin >> turnX;
			cin >> turnY;
			if (((!turnX) || (turnX < 1) || (turnX > 15) || (!turnY) || (turnY < 1) || (turnY > 15)) || (f[turnY - 1][turnX - 1] != 0))
			{
				cout << "�������� ���� (�������� ��� ������� ��� ������), ���������� ��� ���: \n";
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

//==== ��������� ��� ===================================
int compRandAI(int f[15][15])
{
	int tempX = 0, tempY = 0;

	//=====================================�������� �� 4 � ��� C��� ==============================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)	// �������� �� ������� ����
		{
			if (f[Y][X] == 2)			//���� ����� ���� ������� ������ 2 �� ��������� ����������� ��������� ��� � ��������
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 2) { count++; }
					else { break; }								// ��������� ������
				}
				if (count == 4)	
				{
					if ((f[Y][X - 1] == 0) && (X > 0))
					{											//��������� ����������� ��������� ����� ���� ����� (���������� �� ����� ���������� ���������� ����������)
						f[Y][X - 1] = 2;
						return 0;
					}
					else if ((f[Y][X + 4] == 0) && (X < 12))
					{											//��������� ����������� ��������� ����� ����� ���� (���������� �� ����� ���������� ���������� ����������)
						f[Y][X + 4] = 2;
						return 0;
					}
				}

				//================================================
				
				count = 0;
				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y + temp][X] == 2) { count++; }
					else { break; }								//���������  �������
				}
				if (count == 4)									
				{
					if ((f[Y - 1][X] == 0) && (Y > 0))
					{											//��������� ����������� ��������� ���� ����� ���� (���������� �� ����� ���������� ���������� ����������)
						f[Y - 1][X] = 2;
						return 0;
					}
					else if ((f[Y + 4][X] == 0) && (Y < 12))
					{											//��������� ����������� ��������� ���� ����� ���� (���������� �� ����� ���������� ���������� ����������)
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
					if (f[tempY][tempX] == 2)					//��������� ������� ���������
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
					if (f[tempY][tempX] == 2)					//��������� �������� ���������
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

	//========================== �������� �� 4 � ��� � ��������� ===========================================

	tempX = 0;
	tempY = 0;
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 1)					//���� ����� ������� ������ 1 �� �������� ��������� �� ���� �����������
			{
				int count = 0;

				for (int temp = 0; temp < 4; temp++)
				{
					if (f[Y][X + temp] == 1) { count++; }
					else { break; }								// ��������� ������
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
					else { break; }								//���������  �������
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
					if (f[tempY][tempX] == 1)					//��������� ������� ���������
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
					if (f[tempY][tempX] == 1)						//��������� �������� ���������
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

	//================== �������� �� ��_�� ====================================
		
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++) 
		{
			int count = 0;

			for (int temp = 0; temp < 5; temp++)			//�������� �����
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
														//���������  �������
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
				if (f[tempY][tempX] == 1)				//��������� ������� ���������
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
				if (f[tempY][tempX] == 1)			//��������� �������� ���������
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

	// ======================== �������� �� 3 � ��� � ��������� ==================================

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			//======================================================
			
			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 1) { count++; }
				else { break; }								// ��������� ������
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
				else { break; }								//���������  �������
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
				if (f[tempY][tempX] == 1)					//��������� ������� ���������
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
				if (f[tempY][tempX] == 1)					//��������� �������� ���������
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

	//====================== ���� �� ���� ���������� �� =========================

	// ============================== ���� 3 � ��� ���� =========================
	
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{

			//======================================================

			int count = 0;
			for (int temp = 0; temp < 3; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }								// ��������� ������
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
				else { break; }								//���������  �������
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
				if (f[tempY][tempX] == 2)					//��������� ������� ���������
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
				if (f[tempY][tempX] == 2)						//��������� �������� ���������
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

	// ======================== ���� 2 � ��� � ���� ===================================
	
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			
			//======================================================

			int count = 0;
			for (int temp = 0; temp < 2; temp++)
			{
				if (f[Y][X + temp] == 2) { count++; }
				else { break; }									// ��������� ������
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
				else { break; }									//���������  �������
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
				if (f[tempY][tempX] == 2)						 //��������� ������� ���������
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
				if (f[tempY][tempX] == 2)							//��������� �������� ���������
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

	// === ���� ��� ����������� ��������� ���� � 2� ����� �� ====

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 2)					//���� C��� ����� � ����� � ������� �� ��
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

	// ���� ������ ������ ������

	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (f[Y][X] == 1)			//���� ����� ��������� � ����� � ������� �� ��
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

//==========�������� �� �������=========================
int check_for_win(int f[15][15])
{
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 15; X++)			// �������� �� ����
		{
			if (f[Y][X] != 0)					// ���� ����� ������� �� ������ 0 �� �������� ��������� �� ���� �����������
			{
				int check_point = f[Y][X];		// ��������� ����������� ��������
				
				//-----------------��������� ���������� �� ������--------------------
				
				int count = 0;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y][X+temp] == check_point) { count++; }	else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				
				// ---------------------��������� ���������� �� �������--------------

				count = 0;
				for (int temp = 0; temp < 5; temp++)
				{
					if (f[Y+temp][X] == check_point) {count++;} else { break; }
				}
				if (count == 5)
				{
					return check_point;
				}
				
				//----------------------��������� ������� ���������------------------

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
				
				// ------------------��������� �������� ���������---------------------

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
		for (int X = 0; X < 15; X++)	   //�������� ����
			field_mass[Y][X] = 0;
	//----------------------------------------------------
	int winner = 0;
	int menu_key;
	while (true)
	{
		system("cls");
		cout << "=================================== ������ =====================================" << endl << endl;
		cout << "������ ���� ������?" << endl;
		std::cout << "1 :����� ������ ����������" << std::endl;
		std::cout << "2 :��� ������" << std::endl;
		std::cout << ">";

		//=========������ ����� ������ � ��� ������============
		while (true)			
		{
			std::cin >> menu_key;
			if ((!menu_key) || (menu_key < 1) || (menu_key > 2))
			{
				cout << "�������� ������ ��� ������ �����" << endl << ">";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cin.sync();
			}
			else{ break; };
		}
		//=========������ ����� ������ � ��� ������============

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
				if (winner == 1)					//�������� ������� �� ����� ������ ����
				{
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD � = { 0, 21 };
					SetConsoleCursorPosition(h, �);
					SetColor(4, 0);
					cout << "====================== ";
					cout << "�� ��������!";
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
					cout << "������� ��������� :c";
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
					cout << "������� ������ ������ (�)!!";
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
					cout << "������� ������ ����� (�)!!";
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
