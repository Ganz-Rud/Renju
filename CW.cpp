#include "stdafx.h"
#include "iostream"
#include <windows.h>



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
					cout << " 0";
				}
				else
				{
					cout << " x";
				};
			}
		}
		cout << endl;
	}
		
	return 0;
}


int player(int f[15][15])
{
	char key;
	cout << "Enter the pos of your turn (1-15) (1-15)" << endl;
	int turnX, turnY;
	do
	{
		cin >> turnX;
		cin >> turnY;

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c = { turnX, turnY };
		SetConsoleCursorPosition(h, c);
		cin >> key;
	} while (key == 13);
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
	
	field(field_mass);

	player(field_mass);

	cin.get();
	cout << endl << endl << endl;
	system("pause");
	return 0;
}

