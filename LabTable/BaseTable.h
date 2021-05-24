#pragma once

#include <string>
#include <iostream>
#include "Record.h"

using std::string;
using std::ostream;

/*template<class T>
class BaseTable;

template<class T>
ostream& operator<< (ostream&, const BaseTable<T>&);*/

template <class T>
class BaseTable
{
public:
	BaseTable(int size = 10)
	{
		dataCount = 0;
		efficiency = 0;
		maxSize = size;
	}

	BaseTable(BaseTable& bt)
	{
		dataCount = bt.dataCount;
		efficiency = bt.efficiency;
		maxSize = bt.maxSize;
		data = new Record<T>[maxSize];
		for (int i = 0; i < maxSize; i++)
			data[i] = bt.data[i];
	}

	virtual ~BaseTable()
	{

	}

	int getMaxSize()
	{
		return maxSize;
	}

	int getCountRecords()
	{
		return dataCount;
	}

	bool isEmpty()
	{
		return dataCount == 0;
	}

	bool isFull()
	{
		return dataCount == maxSize;
	}

	virtual void insert(Record<T>& rec) = 0;
	virtual void insert(string key = "", T value = 0) = 0;

	virtual void erase(string key) = 0;

	virtual T operator[](string key) = 0;

	//friend  ostream& operator << <>(ostream&, const BaseTable&);

	virtual void print(ostream& out = std::cout)
	{
		out << "Key\t\tValue\n";
		for (int i = 0; i < this->dataCount; i++)
		{
			out << this->data[i] <<"\n";
		}
	}


protected:
	int maxSize;
	int dataCount;
	int efficiency;
	Record<T>* data;
};

/*template<class T>
ostream& operator<<(ostream& os, const BaseTable<T>& table)
{
	for (int i = 0; i < table.dataCount; i++)
	{
		os << table.data[i] << "\n";
	}
	return os;
}*/