#pragma once

#include "BaseTable.h"
#include <exception>
#include <iostream>

using std::string;
using std::ostream;

/*template <class T>
class HashTable;

template <class T>
class HashRecord : public Record<T>
{
public:
	HashRecord(string mKey = "", T mValue = 0) : Record<T>(mKey, mValue), isDeleted(false) {};
private:
	bool isDeleted;
	friend class HashTable<T>;
};*/

template<class T>
class HashTable : public BaseTable<T>
{
public:
	HashTable(int maxSize = 101) : BaseTable<T>(maxSize)
	{
		//this->data = static_cast<HashRecord<T>*>(this->data);
		this->data = new Record<T>[maxSize];
	}

	~HashTable()
	{
		delete[] this->data;
	}

	int hash(string key)
	{
		unsigned int hash, i;
		for (hash = i = 0; i < key.size(); ++i)
		{
			hash += key[i];
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash % this->maxSize;

	}
	HashTable& resize(int newSize)
	{
		HashTable result(newSize);
		for (int i = 0; i < this->dataCount; i++)
		{
			if (this->data[i].getKey() != "")
				result.insert(this->data[i]);
		}

		*this = result;
		return *this;
	}

	void insert(Record<T>& rec)
	{
		//если таблица заполнена > 75% -> resize(maxSize * 2)
		if (double(this->dataCount) / this->maxSize > 0.75)
			resize(this->maxSize * 2);

		int index = hash(rec.getKey());


		while (this->data[index].getKey() != "")
		{
			if (this->data[index].getKey() == rec.getKey())
			{
				string problem = "Record with key \"" + rec.getKey() + "\" already exist";
				throw std::exception(problem.c_str());
			}

			index += prime;
		}

		this->data[index] = rec;
		this->data[index].setDel(false);
		this->dataCount++;
		return;
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

		int index = hash(key);
		while (this->data[index].getKey() != key)
		{
			if (this->data[index].getKey() == "")
				throw std::exception("Erase: Wrong key");
			index += prime;
		}

		this->data[index].clear();
		this->data[index].setDel(true);
		this->dataCount--;

	}

	T operator[](string key)
	{
		int index = hash(key);
		while (this->data[index].getKey() != key)
		{
			if (this->data[index].getKey() == "" && !this->data[index].isDel())
				throw std::exception("Access: Wrong key");

			index += prime;
		}

		return this->data[index].getValue();

	}

	void print(ostream& out)
	{
		out << "Key\t\tHash\t\tValue\n";
		for (int i = 0; i < this->maxSize; i++)
		{
			if (this->data[i].getKey() != "")
			{
				out << this->data[i].getKey() << "\t\t" << hash(this->data[i].getKey()) << "\t\t" << this->data[i].getValue() << "\n";
			}
		}
	}

private:
	static const int prime = 1;

};

