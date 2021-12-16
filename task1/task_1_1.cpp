#include <list>
#include <iostream>

using namespace std;

//Вариант 1 Алехин Артём КМБО-04-20

bool predicate_function(char a)
{
	if (a >= 'A' && a <= 'Z')
	{
		return true;
	}
	return false;
}

template <typename T>
void print_list(list<T> &lst)
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		cout << *p << " ";
		p++;
	}
	cout << endl;
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

int main()
{
	list<char> listOfChars;

	for (int i = 0; i < 11; i += 4)
	{
		listOfChars.push_back('a' + i);
		listOfChars.push_back('A' + i);
	}
	insert(listOfChars, 'a');

	list<char> newListOfChars = filter<char>(listOfChars, predicate_function);

	print_list(listOfChars);
	print_list(newListOfChars);

	int myChar;
	cin >> myChar;

	return 0;
}
