#include <iostream>
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"
#include <random>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));

	try {
		HashTable<int> hash(101);
		hash.insert("Aba", 3);
		hash.print(cout);
		cout << endl << endl;
		for (int i = 0; i < 10; i++)
		{
			string key = to_string ((rand() % 32)) + to_string((rand() % 32));
			//cout << i << ' ' << key << endl;
			hash.insert(key, i * i);
		}

		hash.print(cout);

	}

	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}
