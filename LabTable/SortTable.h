#pragma once

#include "BaseTable.h"
#include <exception>
#include <algorithm>

template <class T>
class SortTable;

template<class T>
int binarySearch(SortTable<T>& arr, string key)
{
	int left = 0, right = arr.dataCount - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr.data[mid].getKey() == key)
			return mid;
		if (arr.data[mid].getKey() < key)
			left = mid + 1;
		if (arr.data[mid].getKey() > key)
			right = mid - 1;
	}

	return -1;
}

template<class T>
class SortTable : public BaseTable<T>
{
public:
	SortTable(int maxSize = 10) : BaseTable<T>(maxSize)
	{
		this->data = new Record<T>[this->maxSize];
	}

	~SortTable()
	{
		delete[] this->data;
	}

	void insert(Record<T>& rec)
	{
		if (this->isFull())
			throw std::exception("SortTable is full");
		if (binarySearch<T>(*this, rec.getKey()) != -1)
		{
			string problem = "Record with key \"" + rec.getKey() + "\" already exist";
			throw std::exception(problem.c_str());
		}
		else {
			this->data[this->dataCount++] = rec;
			std::sort(this->data, this->data + this->dataCount, [](Record<T> r1, Record<T> r2) {return r1 > r2; });
		}
	}
	

	void insert(string key = "", T value = 0)
	{
		Record<T> rec(key, value);
		insert(rec);
	}

	void erase(string key)
	{
		if (this->isEmpty())
			throw std::exception("Erase from empty table");

		int index = binarySearch<T>(*this, key);
		if (index == -1)
			throw std::exception("Erase: Wrong key");
		else {
			this->data[index].clear();
			std::sort(this->data, this->data + this->dataCount, [](Record<T> r1, Record<T> r2) {return r1 > r2; });
			this->dataCount--;
		}

	}

	T operator[](string key)
	{
		int index = binarySearch<T>(*this, key);
		if (index == -1)
			throw std::exception("Access: Wrong key");
		else return this->data[index].getValue();
	}

	friend int binarySearch<T>(SortTable<T>& arr, string key);
};


