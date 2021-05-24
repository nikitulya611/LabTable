#include <iostream>
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"
#include <random>
#include <ctime>
#include <conio.h>

using namespace std;

void workTable(BaseTable<int>* p)
{
	while (true)
	{
		int choose = -1;
		string key = "";
		int value = 0;

		system("cls");

		cout << "1. Вставить запись\n" << "2. Удалить запись\n" << "3. Найти запись\n" << "4. Вывести таблицу\n" << "0. Выход\n";
		do {
			cin >> choose;
		} while (choose < 0 || choose > 4);

		try {

			switch (choose)
			{
			case 0:
				return;
			case 1:
				cout << "Введите ключ:\n";
				cin.ignore();
				getline(cin, key);
				cout << "Введите значение:\n";
				cin >> value;
				p->insert(key, value);
				break;

			case 2:
				cout << "Введите ключ:\n";
				cin.ignore();
				getline(cin, key);
				p->erase(key);
				break;

			case 3:
				cout << "Введите ключ:\n";
				cin.ignore();
				getline(cin, key);
				cout << (*p)[key];
				break;

			case 4:
				p->print();
				break;

			default:
				break;
			}
		}
		catch (std::exception e)
		{
			cout << e.what();
		}

		_getch();
	}
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	int choose;

	BaseTable<int>* p = nullptr;

	cout << "С какой таблицей вы хотите работать:\n" << "1. ScanTable\n" << "2. SortTable\n" << "3. HashTable\n" << "0. Выход\n";
	do {
		cin >> choose;
	} while (choose < 0 || choose > 3);

	switch (choose)
	{
	case 0:
		exit(0);

	case 1:
		p = new ScanTable<int>;
		break;
	case 2:
		p = new SortTable<int>;
		break;
	case 3:
		p = new HashTable<int>;
		break;
	}

	workTable(p);

	return 0;
}
