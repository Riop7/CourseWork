#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP
#include<iostream>

//  DoubleLinkedList.h - Дважды связный список целых чисел  
//
template < class T >
class DoubleLinkedList
{
private:
  // Тип  Node используется для описания элемента списка, связанного со 
  // следующим с помощью поля next_ и предшествующим с помощью поле prev_
	template < typename C >
  struct Node         // может использоваться  только в классе DoubleLinkedList
  {
    C item_;        // значение элемента списка
    Node* next_;      // указатель на следующий элемент списка
    Node* prev_;      // указатель на предшествующий элемент списка

    // Конструктор для создания нового элемента списка. 
    Node(C item, Node* next = nullptr, Node* prev = nullptr):
			item_(item),
			next_(next),
			prev_(prev)
		{}
  };

  int count_;         // счетчик числа элементов
  Node< T >* head_;        // первый элемент списка
  Node< T >* tail_;        // последний элемент списка

// Доступ к головному узлу списка
  Node< T >* head() const
	{
		return head_;
	}

  // Доступ к хвостовому узлу списка
  Node< T >* tail() const
	{ 
		return tail_;
	}

  // Всавить сформированный узел в хвост списка
  void insertTail(Node< T >* x);

  // Вставить сформированный узел в начало списка
  void insertHead(Node< T >* x); // (int item);

// Удаление заданного узла 
  void deleteNode(Node< T >* x);

  // Поиск узла (адрес) с заданным значением  
  Node< T >* searchNode(T item);

  // Замена информации узла на новое 
  Node< T >* replaceNode(Node< T >* x, T item);

public:

  // Конструктор "по умолчанию" - создание пустого списка
  DoubleLinkedList():
    count_(0),
    head_(nullptr),
    tail_(nullptr)
  {}

  // Конструктор "копирования" – создание копии имеющегося списка
  DoubleLinkedList(const DoubleLinkedList& src);

  // Конструктор перемещения
  DoubleLinkedList(DoubleLinkedList&& src)noexcept;

  //
  DoubleLinkedList& operator=(DoubleLinkedList&& x) noexcept;

  // количество элементов списка
  int count() const;

  // Доступ к информации головного узла списка
  T headItem() const;
	T& headItem();

  // Доступ к информации хвостового узла списка
	T tailItem() const;
	T& tailItem();

  // Вставить элемент в голову списка
  void insertHead(T item);

  // Вставить элемент в хвост списка
  void insertTail(T item);

  // Удалить элемент с головы списка
  bool deleteHead();

  // Удалить элемент из хвоста списка
  bool deleteTail();

  // Удаление узла с заданным значением  
  bool deleteItem(const T item);

  // Поиск записи с заданным значением  
  Node< T >* searchItem(T item);

  // Замена информации узла на новое 
  bool replaceItem(T itemOld, T itemNew);

  // Вывод элементов списка в текстовом виде в стандартный выходной поток 
  void outAll();

  //оператор копирующего присваивания
  DoubleLinkedList& operator =(const DoubleLinkedList& src);

  //swap
  void swap(DoubleLinkedList& src) noexcept;

  //перегруженный оператор вывода
  //friend std::ostream& operator<< (std::ostream& out, DoubleLinkedList& src);

	//Проверка на empty
	bool empty() const;
  // Деструктор списка	
  virtual ~DoubleLinkedList();
};

template < typename T >
bool DoubleLinkedList< T >::empty() const
{
	return !count_;
}

template< typename T >
DoubleLinkedList< T >::DoubleLinkedList(const DoubleLinkedList& src) :
	head_(nullptr),
	tail_(nullptr),
	count_(0)
{
	Node< T >* currentNode = src.head_;
	while (currentNode != nullptr)
	{
		this->insertTail(currentNode->item_);
		currentNode = currentNode->next_;
	}
}

// Вставить сформированный узел в хвост списка
template < typename T >
void DoubleLinkedList< T >::insertTail(Node< T >* x)
{
	x->prev_ = tail_;
	if (head_ != nullptr) {
		tail_->next_ = x;
	}
	else
	{
		head_ = x;
	}
	tail_ = x;
	count_++;
}

// Вставить сформированный узел в начало списка
template < typename T >
void DoubleLinkedList< T >::insertHead(Node< T >* x)
{
	x->next_ = head_;
	if (head_ != nullptr) {
		// список был НЕ пуст – новый элемент будет и первым, и последним
		head_->prev_ = x;
	}
	else {
		// список был пуст – новый элемент будет и первым, и последним
		tail_ = x;
	}
	head_ = x;
	count_++;  // число элементов списка увеличилось
}

// Удаление заданного узла 
template < typename T >
void DoubleLinkedList< T >::deleteNode(Node< T >* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
	}
	if (x->prev_ != nullptr)
	{
		// удаляется НЕ голова списка
		(x->prev_)->next_ = x->next_;
	}
	else
	{
		// удаляется голова списка,  второй элемент становится первым
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// удаляется НЕ хвост
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// удаляется хвост
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // число элементов списка уменьшилось
}

// Поиск узла (адрес) с заданным значением  
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::searchNode(T item)
{
	Node< T >* x = head_;
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// Замена информации узла на новое 
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::replaceNode(DoubleLinkedList< T >::Node< T >* x, T item)
{
	x->item_ = item;
	return x;
}

//количество элементов списка
template < typename T >
int DoubleLinkedList< T >::count()const { return count_; }

// Доступ к информации головного узла списка
template < typename T >
T DoubleLinkedList< T >::headItem() const
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - список пуст!");
}

template < typename T >
T& DoubleLinkedList< T >::headItem()
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - список пуст!");
}

// Доступ к информации хвостового узла списка
template < typename T >
T DoubleLinkedList< T >::tailItem() const
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - список пуст!");
}
template < typename T >
T& DoubleLinkedList< T >::tailItem()
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - список пуст!");
}

// Вставить элемент в голову списка
template < typename T >
void DoubleLinkedList< T >::insertHead(T item)
{   // создаем новый элемент списка и добавляем в голову 
	insertHead(new Node< T >(item));
}


// Вставить элемент в хвост списка
template < typename T >
void DoubleLinkedList< T >::insertTail(T item)
{   // создаем новый элемент списка и добавляем в хвост 
	insertTail(new Node< T >(item));
}

// Удалить элемент с головы списка
template < typename T >
bool DoubleLinkedList< T >::deleteHead()
{
	if (head_ == nullptr) {
		return 0;  // список пуст, удалений нет
	}
	deleteNode(head_);
	return 1;      // список был НЕ пуст, удаление головы
}

// Удалить элемент из хвоста списка
template < typename T >
bool DoubleLinkedList< T >::deleteTail()
{
	if (tail_ == nullptr) {
		return false;
	}
	deleteNode(tail_);
	return 1;
}

// Удаление узла с заданным значением
template < typename T >
bool DoubleLinkedList< T >::deleteItem(const T item)
{
	bool flag = 0;
	Node< T >* temp = head_;
	while (temp != nullptr)
	{
		if (temp->item_ == item)
		{
			temp = temp->next_;
			deleteNode(temp->prev_);
			flag = 1;
		}
		else
		{
			temp = temp->next_;
		}
	}
	return flag;
}

// Поиск записи с заданным значением
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::searchItem(T item)
{   // возвращаем объект
	return (searchNode(item));
}


// Замена информации узла на новое 
template < typename T >
bool DoubleLinkedList< T >::replaceItem(T itemOld, T itemNew)
{
	bool isReplace = 0;
	Node< T >* x = head_;
	while (x != nullptr) {
		if (x->item_ == itemOld)
		{
			x->item_ = itemNew;
			isReplace = true;
		}
		x = x->next_;
	}
	return isReplace;
}

// Вывод элементов списка в текстовом виде в стандартный выходной поток 
template < typename T >
void DoubleLinkedList< T >::outAll()
{
	Node< T >* current = head_;       // Указатель на элемент
	while (current != nullptr)
	{
		std::cout << current->item_ << ' ';
		current = current->next_;  // Переход к следующему элементу
	}
	std::cout << std::endl;
}

// Деструктор списка	
template < typename T >
DoubleLinkedList< T >::~DoubleLinkedList()
{
	Node< T >* current = nullptr;   // указатель на элемент, подлежащий удалению
	Node< T >* next = head_;        // указатель на следующий элемент
	while (next != nullptr) {  // пока есть еще элементы в списке
		current = next;
		next = next->next_;    // переход к следующему элементу
		delete current;        // освобождение памяти
	}
}

//оператор копирующего присваивания
template < typename T >
DoubleLinkedList< T >& DoubleLinkedList< T >::operator=(const DoubleLinkedList< T >& src)
{
	if (this != &src)
	{
		DoubleLinkedList(src).swap(*this);
	}
	return *this;
}

//swap
template < typename T >
void DoubleLinkedList< T >::swap(DoubleLinkedList& src) noexcept
{
	Node< T >* temp = nullptr;
	temp = head_;
	head_ = src.head_;
	src.head_ = temp;

	temp = tail_;
	tail_ = src.tail_;
	src.tail_ = temp;
	temp = nullptr;

	std::swap(count_, src.count_);
}

//конструктор перемещения
template < typename T >
DoubleLinkedList< T >::DoubleLinkedList(DoubleLinkedList< T >&& src) noexcept
{
	head_ = src.head_;
	tail_ = src.tail_;
	count_ = src.count_;
	src.head_ = nullptr;
	src.tail_ = nullptr;
	src.count_ = 0;
}

//оператор присвающего перемещения
template < typename T >
DoubleLinkedList< T >& DoubleLinkedList< T >::operator=(DoubleLinkedList< T >&& x) noexcept
{

	if (&x == this)
		return *this;
	while (head_ != nullptr)
	{
		deleteHead();
	}

	head_ = x.head_;
	tail_ = x.tail_;
	count_ = x.count_;

	x.head_ = nullptr;
	x.tail_ = nullptr;
	x.count_ = 0;

	return *this;
}

//std::ostream& operator<< (std::ostream& out, DoubleLinkedList& src) {
//	src.outAll();
//	return out;
//}
//
//
//bool DoubleLinkedList::operator==(const DoubleLinkedList& src) {
//	if (count_ != src.count_)
//		return false;
//	Node* left = head_;
//	Node* right = src.head_;
//	while (left != nullptr && right != nullptr) {
//		if (left->item_ == right->item_) {
//			left = left->next_;
//			right = right->next_;
//		}
//		else
//			return false;
//	}
//	if (left == nullptr && right == nullptr)
//		return true;
//	else
//		return false;
//}
//
//void DoubleLinkedList::addList(DoubleLinkedList& src) {
//  Node* x = src.head_;
//  if (src.head_ != nullptr)
//  {
//		while (x != nullptr)
//		{
//			this->insertTail(x);
//			x = x->next_;
//		}
//	}
//	src.head_ = nullptr;
//	src.tail_ = nullptr;
//	src.count_ = 0;
//}


#endif
//std::ostream& operator<< (std::ostream& out, DoubleLinkedList< T >& src);


