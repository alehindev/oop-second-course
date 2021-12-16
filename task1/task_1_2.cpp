#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

class facility
{
private:
	string adress;
	int type; //  тип: 1 - городской  дом, 2 - заго-родный  дом, 3 -  квартира,4 -  дача
	double squareUsefull;
	double price;
	double squareAll;

public:
	facility() {}

	facility(string adr, int tp, double sqrUs, double prc, double sqrAll)
	{
		adress = adr;
		type = tp; //  тип: 1 - городской  дом, 2 - заго-родный  дом, 3 -  квартира,4 -  дача
		squareUsefull = sqrUs;
		price = prc;
		squareAll = sqrAll;
	}

	~facility()
	{
	}

	string getAdress()
	{
		return adress;
	}
	int getType()
	{
		return type;
	}
	int getSquareUsefull()
	{
		return squareUsefull;
	}
	unsigned int getPrice()
	{
		return price;
	}
	unsigned int getSquareAll()
	{
		return squareAll;
	}
	void print()
	{
		cout << "Adress: " << adress << ", Type: " << type << ", SquareUsefull: " << squareUsefull << ", Price: " << price << ", SquareAll: " << squareAll << endl;
	}
};

template <typename T>
void insert(list<T> &lst, T element)
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		if (*p > element)
			break;
		p++;
	}
	lst.insert(p, element);
}

template <typename T>
list<T> filter(list<T> &lst, bool (&pr)(T))
{
	typename list<T>::iterator p = lst.begin();
	list<T> newLst;
	while (p != lst.end())
	{
		if (pr(*p))
		{
			newLst.push_back(*p);
		}
		p++;
	}
	return newLst;
}

bool facility_predicate(facility a, facility b)
{
	if (a.getPrice() > b.getPrice())
	{
		return true;
	}
	else
	{
		if (a.getPrice() == b.getPrice())
		{
			if (a.getAdress() > b.getAdress())
			{
				return true;
			}
			return false;
		}
		return false;
	}
}

template <typename T>
void insert(list<T> &lst, T element, bool (&pr)(T, T))
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		if (!pr(*p, element))
			break;
		p++;
	}
	lst.insert(p, element);
}

template <typename T>
void print(list<T> &lst)
{
	for (auto &i : lst)
	{
		i.print();
	}
}

template <typename T>
T pop(list<T> &lst)
{
	T a = lst.front();
	lst.pop_front();
	return a;
}

int main()
{
	vector<string> adress = {"Nahabino", "Petrushino", "Uglichi", "Rozdestvenno", "Sinicino", "Elan"};
	vector<int> type = {1, 4, 4, 3, 4, 2};
	vector<double> squareUsefull = {12321.2, 42342.1, 65645.12, 7675.32, 34.132, 0.312};
	vector<double> price = {45254, 542, 4547, 968, 78, 3};
	vector<double> squareAll = {31354, 4342, 22, 312, 324432, 1};
	list<facility> myFacility;

	for (int i = 0; i < 6; i++)
	{
		insert(myFacility, facility(adress[i], type[i], squareUsefull[i], price[i], squareAll[i]), facility_predicate);
	}

	print(myFacility);

	cout << endl;
	pop(myFacility).print();

	cout << endl;
	print(myFacility);

	return 0;
}
