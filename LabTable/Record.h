#pragma once

#include <ostream>

using std::ostream;
using std::string;

template<class T>
class Record;

template<class T>
ostream& operator<< (ostream&, const Record<T>&);

template<class T>
ostream& operator<<(ostream& os, const Record<T>& rec)
{
	os << rec.getKey() << "\t\t" << rec.getValue();

	return os;
}


template<class T>
class Record
{
public:

	Record(string mKey = "", T mValue = 0) : key(mKey), value(mValue), isDeleted(false) {};
	Record(const Record<T>& rec)
	{
		key = rec.key;
		value = rec.value;
		isDeleted = false;
	}

	~Record() {};

	void setKey(string newKey)
	{
		key = newKey;
	}

	string getKey() const
	{
		return key;
	}

	void setValue(T newValue)
	{
		value = newValue;
	}

	T getValue() const
	{
		return value;
	}

	bool isDel()
	{
		return isDeleted;
	}

	void setDel(bool b)
	{
		isDeleted = b;
	}

	bool operator==(const Record<T>& rec)
	{
		return key == rec.key;
	}

	bool operator<(const Record<T>& rec)
	{
		return key < rec.key;
	}

	bool operator>(const Record<T>& rec)
	{
		return key > rec.key;
	}

	Record<T>& operator=(const Record<T>& rec)
	{
		key = rec.key;
		value = rec.value;
		return *this;
	}

	void clear()
	{
		key = "";
		value = 0;
	}

	friend  ostream& operator << <>(ostream&, const Record&);

private:
	string key;
	T value;
	bool isDeleted;
};
