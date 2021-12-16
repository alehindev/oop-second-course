#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <string>

using namespace std;


// 2.1
template<typename K, typename V>
V find_by_key(map<K, V> m, K key)
{
	if (m.count(key) != 0)
		return m.at(key); // возвращаем элемент, если найден соответствующий ключ
	else throw "key not found"; // если не найден - то кидаем исключение
}

template<typename K, typename V>
list<K> find_by_value(map<K, V> m, V val)
{
	list<K> result; // лист с ключами map, имеющие необходимые значения
	for (auto e : m)
	{
		if (e.second == val)
			result.push_back(e.first);
	}
	return result; // возвращаю найденные ключи
}

template<typename K, typename V>
map<K, V> filter(map<K, V> m, bool (*ptr_func)(V))
{
	map<K, V> result; // отфильтрованный список
	for (auto e : m)
	{
		if (ptr_func(e.second))
			result.insert(e);
	}
	return result; // возвращаю отфильтрованный список
}

template<typename K, typename V>
void print_map(map<K, V> m)
{
	for (auto e : m)
	{
		cout << e.first << ": " << e.second << ", ";
	}
	cout << "\n";
}

template <class T>
void print_list(list<T> lst)
{
	for (auto e : lst)
		cout << e << "; ";
	cout << "\n";
}

bool Predicate(int value) {
	return (value > 100000);
}

// 2.2
template<typename T>
void print_queue(T q) {
	while (!q.empty()) {
		cout << "Key: " << q.top().first << ", Value: " << q.top().second << "\n";
		q.pop();
	}
	std::cout << '\n';
}

// 2.3
template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}

	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
	}

	virtual void print()
	{
		cout << "\n" << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class T1> friend ostream& operator<< (ostream& stream, Node<T1>& N);
};

template<class T1>
ostream& operator<< (ostream& stream, Node<T1>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	~Tree<T>()
	{
		queue<Node<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			Node<T>* n = q.front();
			q.pop();
			if (n != NULL)
			{
				q.push(n->getLeft());
				q.push(n->getRight());
				delete n;
			}
		}
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}

	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL)
		{
			root = N;
			return N;
		}

		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())
			//нашли совпадение
			;
		//для несбалансированного дерева поиска
		return Current;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Add_R(N);
	}

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL) Current = root;
		while (Current->getLeft() != NULL) Current = Current->getLeft();
		return Current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;
		if (Current == NULL) Current = root;
		while (Current->getRight() != NULL) Current = Current->getRight();
		return Current;
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		if (root == NULL || Current == NULL) return NULL;
		if (Current->getData() > data) return Find(data, Current->getLeft());
		if (Current->getData() < data) return Find(data, Current->getRight());
		return Current;
	}

	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

//класс итератор по дереву
template<typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	TreeIterator() { ptr = NULL; T = NULL; }
	TreeIterator(Tree<ValueType>* t, Node<ValueType>* p) { ptr = p; T = t; }
	TreeIterator(const TreeIterator& it) { T = it.T; ptr = it.ptr; }

	TreeIterator& operator=(const TreeIterator& it) { T = it.T; ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<ValueType>* p)
	{
		ptr = p;
		return *this;
	}

	bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }
	Node<ValueType>& operator*()
	{
		return *ptr;
	}
	TreeIterator& operator++(int v)
	{
		// successor
		if (ptr == NULL || T->getRoot() == NULL) return *this;
		if (ptr->getRight() != NULL) { ptr = T->Min(ptr->getRight()); return *this; }
		if (ptr == T->Max()) return *this;
		Node<ValueType>* Current = ptr;
		while (true)
		{
			if (Current->getParent() == NULL) return *this;
			if (Current->getParent()->getLeft() == Current)
			{
				ptr = Current->getParent();
				return *this;
			}
			Current = Current->getParent();
		}
	}
	TreeIterator& operator--(int v)
	{
		// successor
		if (ptr == NULL || T->getRoot() == NULL) return *this;
		if (ptr->getLeft() != NULL) { ptr = T->Max(ptr->getLeft()); return *this; }
		if (ptr == T->Min()) return *this;
		Node<ValueType>* Current = ptr;
		while (true)
		{
			if (Current->getParent() == NULL) return *this;
			if (Current->getParent()->getRight() == Current)
			{
				ptr = Current->getParent();
				return *this;
			}
			Current = Current->getParent();
		}
	}
private:
	Node<ValueType>* ptr;
	Tree<ValueType>* T;
};

//класс итерируемое дерево поиска
template<class T>
class IteratedTree : public Tree<T>
{
public:
	using Tree<T>::Min;
	using Tree<T>::Max;
	IteratedTree<T>() : Tree<T>() {}

	TreeIterator<T> begin() { return TreeIterator<T>(this, Min()); }
	TreeIterator<T> end() { return TreeIterator<T>(this, Max()); }
};

//AVL_Tree - потомок класса Tree, АВЛ-дерево (сбалансированное дерево поиска)
template<class T>
class AVL_Tree : public IteratedTree<T>
{
	using Tree<T>::root;
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();

		q->setParent(p->getParent());
		if (p->getParent() != NULL)
		{
			if (p->getParent()->getLeft() == p)
			{
				p->getParent()->setLeft(q);
			}
			else
			{
				p->getParent()->setRight(q);
			}
		}
		p->setParent(q);
		if (p == root) root = q;


		p->setLeft(q->getRight());
		if (q->getRight() != NULL) q->getRight()->setParent(p);
		q->setRight(p);


		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();

		p->setParent(q->getParent());
		if (q->getParent() != NULL)
		{
			if (q->getParent()->getLeft() == p)
			{
				q->getParent()->setLeft(p);
			}
			else
			{
				q->getParent()->setRight(p);
			}
		}
		q->setParent(p);
		if (q == root) root = p;

		q->setRight(p->getLeft());
		if (p->getLeft() != NULL) p->getLeft()->setParent(q);
		p->setLeft(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0)
			{
				p->setRight(RotateRight(p->getRight()));
				p->getRight()->setParent(p);
			}
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)
			{
				p->setLeft(RotateLeft(p->getLeft()));
				p->getLeft()->setParent(p);
			}
			return RotateRight(p);
		}

		return p; // балансировка не нужна
	}

public:
	using Tree<T>::Min;
	using Tree<T>::Max;
	using IteratedTree<T>::begin;
	using IteratedTree<T>::end;

	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : IteratedTree<T>() {}

	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию Add_R из базового класса
		Node<T>* AddedNode = Tree<T>::Add_R(N, Current);
		//применяем к добавленному узлу балансировку
		return Balance(AddedNode);
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Add_R(N);
	}

	void Print_increment()
	{
		TreeIterator<T> it = begin();
		while (it != end())
		{
			cout << *it << " ";
			it++;
		}
		cout << *it << " ";
	}

	void Print_decrement()
	{
		TreeIterator<T> it = end();
		while (it != begin())
		{
			cout << *it << " ";
			it--;
		}
		cout << *it << " ";
	}
};

class Locality {
private:
	string name;
	string locality_type;
	int zip_code;
	int people;
	int square;
public:
	Locality(string name = "",
		string locality_type = "",
		int zip_code = 0,
		int people = 0,
		int square = 0)
	{
		this->name = name;
		this->locality_type = locality_type;
		this->zip_code = zip_code;
		this->people = people;
		this->square = square;
	}

	bool operator>(Locality obj)
	{
		if (name > obj.name) return true;
		else {
			if (name == obj.name) {
				if (locality_type > obj.locality_type) return true;
			}
		}
		return false;
	}

	bool operator<(Locality obj)
	{
		if (name < obj.name) return true;
		else {
			if (name == obj.name) {
				if (locality_type < obj.locality_type) return true;
			}
		}
		return false;
	}

	bool operator==(Locality obj)
	{
		if (name == obj.name) {
			if (locality_type == obj.locality_type) return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream& ustream, const Locality& obj);
};

ostream& operator<< (ostream& ustream, const Locality& obj)
{
	ustream << "Name: " + obj.name << " Type: " + obj.locality_type << " ";
	ustream << "People: " << obj.people << " ";
	ustream << "Zip-code: " << obj.zip_code << " Square: " << obj.square << "\n";
	return ustream;
}

template <class T>
class HeapNode
{
private:
	T value;
public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//сравнение узлов
	int operator<(HeapNode N)
	{
		return (value < N.getValue());
	}

	int operator>(HeapNode N)
	{
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};

template <class T>
void printHeapNode(HeapNode<T>* N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap
{
private:
	//массив
	HeapNode<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	HeapNode<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?

		return arr[index];
	}

	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new HeapNode<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}

	~Heap<T>()
	{
		delete[] arr;
		len = 0;
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;

		HeapNode<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(HeapNode<T>* dest, HeapNode<T>* source)
	{
		dest->setValue(source->getValue());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	HeapNode<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}

	HeapNode<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return &arr[index * 2 + 2];
	}

	HeapNode<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int index = 0)
	{
		//то же, что и SiftDown
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largestChild = index;

		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (leftChild < len && arr[leftChild] > arr[largestChild])
		{
			largestChild = leftChild;
		}
		if (rightChild < len && arr[rightChild] > arr[largestChild])
		{
			largestChild = rightChild;
		}
		if (largestChild != index) {
			Swap(largestChild, index);
			Heapify(largestChild);
		}
	}

	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		if (index <= 0) return;

		//нужно сравнить элементы и при необходимости произвести просеивание вверх
		int parent = GetParentIndex(index);
		if (arr[parent] < arr[index])
		{
			Swap(parent, index);
			SiftUp(parent);
		}
	}

	//удобный интерфейс для пользователя 
	void Push(T v)
	{
		HeapNode<T>* N = new HeapNode<T>;
		N->setValue(v);
		Push(N);
	}

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	void Push(HeapNode<T>* N)
	{
		if (len < size)
		{
			len++;
			Copy(&arr[len - 1], N);
			SiftUp();
		}
	}

	HeapNode<T>* ExtractMax()
	{
		//исключить максимум и запустить просеивание кучи
		HeapNode<T>* res = new HeapNode<T>();
		Copy(res, &arr[0]);

		Swap(0, len - 1);
		len--;
		Heapify();

		return res;
	}

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(HeapNode<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*f)(HeapNode<T>*), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(HeapNode<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(HeapNode<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
	}
};

int main() {
	// 2.1
	map<string, int> locality_people;
	locality_people["Konstantinsk"] = 463728;
	locality_people["Rechnaya"] = 1553;
	locality_people["Erevanensk"] = 95857331;
	locality_people["Loskutki"] = 5457;


	cout << "Map:\n";
	print_map(locality_people);

	cout << "\nFind by artist and albom (Loskutki):\n";
	cout << find_by_key(locality_people, string("Loskutki")) << "\n";

	cout << "\nFind by value (5457):\n";
	print_list(find_by_value(locality_people, 5457));

	cout << "\nFilter:\n";
	bool (*ptr)(int); ptr = Predicate;
	print_map(filter(locality_people, ptr));

	// 2.2
	auto cmp_map = [](const pair<string, int>& a, const pair<string, int>& b) {
		return a.second < b.second;
	};
	priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp_map)> pq(locality_people.begin(), locality_people.end(), cmp_map);
	cout << "\nPriority queue:" << endl;
	print_queue(pq);


	 //2.3
	AVL_Tree<Locality> Locality_tree;
	Locality_tree.Add(Locality("Konstantinsk", "City", 789642, 463728, 111227));
	Locality_tree.Add(Locality("Rechnaya", "Village", 987332, 1553, 222));
	Locality_tree.Add(Locality("Erevanensk", "City", 664511, 95857331, 352998));
	Locality_tree.Add(Locality("Loskutki", "Small town", 111321, 5457, 881));

	Node<Locality>* min_Locality = Locality_tree.Min();
	Node<Locality>* target = Locality_tree.Find(Locality("Loskutki", "Small town"), Locality_tree.getRoot());

	cout << "\nMin = " << min_Locality->getData();
	if (target != NULL)
		cout << "Find : " << target->getData();
	else
		cout << "Not found";

	cout << "\n\nIncreasing order:";
	Locality_tree.Print_increment();
	cout << "\n\nDecreasing order:";
	Locality_tree.Print_decrement();

	// 2.4
	Heap<int> priority_heap;

	priority_heap.Push(1);
	priority_heap.Push(-1);
	priority_heap.Push(-3);
	priority_heap.Push(3);
	priority_heap.Push(7);
	priority_heap.Push(8);
	priority_heap.Push(-9);
	priority_heap.Push(9);
	priority_heap.Push(4);
	priority_heap.Push(-4);

	cout << "\n-----\nStraight:\n";
	void(*f_ptr)(HeapNode<int>*); f_ptr = printHeapNode;
	priority_heap.Straight(f_ptr);

	cout << "\n-----\nExtractMax:\n";
	int i = 0;
	while (i < priority_heap.getCount())
	{
		HeapNode<int>* N = priority_heap.ExtractMax();
		N->print();
		delete N;
		cout << "\n";
	}

	return 0;
}