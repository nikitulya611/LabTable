#pragma once

#include "BaseTable.h"
#include <exception>

template<class T>
class ScanTable : public BaseTable<T>
{
public:
	ScanTable(int maxSize = 10) : BaseTable<T>(maxSize)
	{
		this->data = new Record<T>[this->maxSize];
	}

	~ScanTable()
	{
		delete[] this->data;
	}

	void insert(Record<T>& rec)
	{
		if (this->isFull())
			throw std::exception("ScanTable is full");

		for (int i = 0; i < this->dataCount; i++)
		{
			if (this->data[i].getKey() == rec.getKey())
			{
				string problem = "Record with key \"" + rec.getKey() + "\" already exist";
				throw std::exception(problem.c_str());
			}
		}
		this->data[this->dataCount++] = rec;
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

		for (int i = 0; i < this->dataCount; i++)
		{
			if (this->data[i].getKey() == key)
			{
				this->data[i] = this->data[this->dataCount - 1];
				this->data[this->dataCount - 1].clear();
				this->dataCount--;
				return;
			}
		}

		throw std::exception("Erase: Wrong key");
	}

	T operator[](string key)
	{
		for (int i = 0; i < this->dataCount; i++)
		{
			if (this->data[i].getKey() == key)
				return this->data[i].getValue();
		}

		throw std::exception("Access: Wrong key");
	}
};
