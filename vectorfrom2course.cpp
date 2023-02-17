#include <string>
#include <iomanip>
#include <iostream>
#include<stdexcept>
using namespace std;


template <typename T>
class Vector
{
	int size;
	T* data;

	void rawCopy(const Vector& that)
	{
		this->size = that.size;
		this->data = new T[size];
		for (int i = 0; i < size; i++)
			this->data[i] = that.data[i];
	}

	void rawClean()
	{
		delete[] data;
	}

public:

	Vector()
	{
		size = 0;
		data = nullptr;
	}

	Vector(const Vector& that)
	{
		rawCopy(that);
	}

	Vector& operator = (const Vector& that)
	{
		if (this != &that)
		{
			this->rawClean();
			this->rawCopy(that);
		}
		return *this;
	}

	~Vector()
	{
		rawClean();
	}

	void add(T& that)
	{
		size += 1;
		T* temp = new T[size];
		for (int i = 0; i < size - 1; i++)
			temp[i] = data[i];
		temp[size - 1] = that;
		delete[] data;
		data = temp;
	}

	void rem(int index)
	{
		if (index < 0 || index >= size)
		{
			throw std::runtime_error("ERROR");
		}
		T* temp = new T[size - 1];
		for (int i = 0; i < index; i++)
			temp[i] = data[i];
		for (int i = index + 1; i < size; i++)
			temp[i - 1] = data[i];
		delete[] data;
		--size;
		data = temp;
	}

	T& operator [] (int r)
	{
		if (r < 0 || r >= size)
		{
			throw std::runtime_error("ERROR");
		}
		return data[r];
	}

	void print(int index)
	{
		if (index < 0 || index >= size)
		{
			throw std::runtime_error("ERROR");
		}
		cout << data[index] << endl;
	}

	void lsh(int r)
	{
		if (!size)
		{
			throw std::runtime_error("ERROR");
		}
		int t = size - (r % size);
		if (!t)
			return;
		T* temp = new T[size];
		for (int i = 0; i < size; i++)
			temp[(i + t) % size] = data[i];
		delete[] data;
		data = temp;
	}

	void rsh(int r)
	{
		if (!size)
		{
			throw std::runtime_error("ERROR");
		}
		int t = r % size;
		if (!t)
			return;
		T* temp = new T[size];
		for (int i = 0; i < size; i++)
			temp[(i + t) % size] = data[i];
		delete[] data;
		data = temp;

	}

	void printAll()
	{
		for (int i = 0; i < size; i++)
			cout << data[i] << endl;
	}
};

template <typename T>
void execute()
{
	Vector<T> v;
	int count;
	cin >> count;
	try {
		for (int i = 0; i < count; i++)
		{
			string c;
			cin >> c;
			if (c == "ADD")
			{
				T d;
				cin >> d;
				v.add(d);
			}
			if (c == "REMOVE")
			{
				int index; cin >> index;
				v.rem(index);
			}
			if (c == "PRINT")
			{
				int index; cin >> index;
				v.print(index);
			}
			if (c == "UPDATE")
			{
				int index;
				T d;
				cin >> index >> d;
				v[index] = d;
			}
			if (c == "LSH")
			{
				int p;
				cin >> p;
				v.lsh(p);
			}
			if (c == "RSH")
			{
				int p;
				cin >> p;
				v.rsh(p);
			}
		}
	}
	catch (...) {
		cout << "ERROR";
	}
	v.printAll();
}

int main()
{
	char t;
	cin >> t;
	switch (t)
	{
	case 'I':
		execute<int>();
		break;
	case 'D':
		cout << fixed << setprecision(2);
		execute<double>();
		break;
	case 'S':
		execute<string>();
		break;
	}

	return 0;
}