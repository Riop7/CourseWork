#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP
#include<iostream>

//  DoubleLinkedList.h - ������ ������� ������ ����� �����  
//
template < class T >
class DoubleLinkedList
{
private:
  // ���  Node ������������ ��� �������� �������� ������, ���������� �� 
  // ��������� � ������� ���� next_ � �������������� � ������� ���� prev_
	template < typename C >
  struct Node         // ����� ��������������  ������ � ������ DoubleLinkedList
  {
    C item_;        // �������� �������� ������
    Node* next_;      // ��������� �� ��������� ������� ������
    Node* prev_;      // ��������� �� �������������� ������� ������

    // ����������� ��� �������� ������ �������� ������. 
    Node(C item, Node* next = nullptr, Node* prev = nullptr):
			item_(item),
			next_(next),
			prev_(prev)
		{}
  };

  int count_;         // ������� ����� ���������
  Node< T >* head_;        // ������ ������� ������
  Node< T >* tail_;        // ��������� ������� ������

// ������ � ��������� ���� ������
  Node< T >* head() const
	{
		return head_;
	}

  // ������ � ���������� ���� ������
  Node< T >* tail() const
	{ 
		return tail_;
	}

  // ������� �������������� ���� � ����� ������
  void insertTail(Node< T >* x);

  // �������� �������������� ���� � ������ ������
  void insertHead(Node< T >* x); // (int item);

// �������� ��������� ���� 
  void deleteNode(Node< T >* x);

  // ����� ���� (�����) � �������� ���������  
  Node< T >* searchNode(T item);

  // ������ ���������� ���� �� ����� 
  Node< T >* replaceNode(Node< T >* x, T item);

public:

  // ����������� "�� ���������" - �������� ������� ������
  DoubleLinkedList():
    count_(0),
    head_(nullptr),
    tail_(nullptr)
  {}

  // ����������� "�����������" � �������� ����� ���������� ������
  DoubleLinkedList(const DoubleLinkedList& src);

  // ����������� �����������
  DoubleLinkedList(DoubleLinkedList&& src)noexcept;

  //
  DoubleLinkedList& operator=(DoubleLinkedList&& x) noexcept;

  // ���������� ��������� ������
  int count() const;

  // ������ � ���������� ��������� ���� ������
  T headItem() const;
	T& headItem();

  // ������ � ���������� ���������� ���� ������
	T tailItem() const;
	T& tailItem();

  // �������� ������� � ������ ������
  void insertHead(T item);

  // �������� ������� � ����� ������
  void insertTail(T item);

  // ������� ������� � ������ ������
  bool deleteHead();

  // ������� ������� �� ������ ������
  bool deleteTail();

  // �������� ���� � �������� ���������  
  bool deleteItem(const T item);

  // ����� ������ � �������� ���������  
  Node< T >* searchItem(T item);

  // ������ ���������� ���� �� ����� 
  bool replaceItem(T itemOld, T itemNew);

  // ����� ��������� ������ � ��������� ���� � ����������� �������� ����� 
  void outAll();

  //�������� ����������� ������������
  DoubleLinkedList& operator =(const DoubleLinkedList& src);

  //swap
  void swap(DoubleLinkedList& src) noexcept;

  //������������� �������� ������
  //friend std::ostream& operator<< (std::ostream& out, DoubleLinkedList& src);

	//�������� �� empty
	bool empty() const;
  // ���������� ������	
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

// �������� �������������� ���� � ����� ������
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

// �������� �������������� ���� � ������ ������
template < typename T >
void DoubleLinkedList< T >::insertHead(Node< T >* x)
{
	x->next_ = head_;
	if (head_ != nullptr) {
		// ������ ��� �� ���� � ����� ������� ����� � ������, � ���������
		head_->prev_ = x;
	}
	else {
		// ������ ��� ���� � ����� ������� ����� � ������, � ���������
		tail_ = x;
	}
	head_ = x;
	count_++;  // ����� ��������� ������ �����������
}

// �������� ��������� ���� 
template < typename T >
void DoubleLinkedList< T >::deleteNode(Node< T >* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - ������� ����� ����� ���������� ����");
	}
	if (x->prev_ != nullptr)
	{
		// ��������� �� ������ ������
		(x->prev_)->next_ = x->next_;
	}
	else
	{
		// ��������� ������ ������,  ������ ������� ���������� ������
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// ��������� �� �����
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// ��������� �����
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // ����� ��������� ������ �����������
}

// ����� ���� (�����) � �������� ���������  
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::searchNode(T item)
{
	Node< T >* x = head_;
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// ������ ���������� ���� �� ����� 
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::replaceNode(DoubleLinkedList< T >::Node< T >* x, T item)
{
	x->item_ = item;
	return x;
}

//���������� ��������� ������
template < typename T >
int DoubleLinkedList< T >::count()const { return count_; }

// ������ � ���������� ��������� ���� ������
template < typename T >
T DoubleLinkedList< T >::headItem() const
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}

template < typename T >
T& DoubleLinkedList< T >::headItem()
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}

// ������ � ���������� ���������� ���� ������
template < typename T >
T DoubleLinkedList< T >::tailItem() const
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}
template < typename T >
T& DoubleLinkedList< T >::tailItem()
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}

// �������� ������� � ������ ������
template < typename T >
void DoubleLinkedList< T >::insertHead(T item)
{   // ������� ����� ������� ������ � ��������� � ������ 
	insertHead(new Node< T >(item));
}


// �������� ������� � ����� ������
template < typename T >
void DoubleLinkedList< T >::insertTail(T item)
{   // ������� ����� ������� ������ � ��������� � ����� 
	insertTail(new Node< T >(item));
}

// ������� ������� � ������ ������
template < typename T >
bool DoubleLinkedList< T >::deleteHead()
{
	if (head_ == nullptr) {
		return 0;  // ������ ����, �������� ���
	}
	deleteNode(head_);
	return 1;      // ������ ��� �� ����, �������� ������
}

// ������� ������� �� ������ ������
template < typename T >
bool DoubleLinkedList< T >::deleteTail()
{
	if (tail_ == nullptr) {
		return false;
	}
	deleteNode(tail_);
	return 1;
}

// �������� ���� � �������� ���������
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

// ����� ������ � �������� ���������
template < typename T >
DoubleLinkedList< T >::Node< T >* DoubleLinkedList< T >::searchItem(T item)
{   // ���������� ������
	return (searchNode(item));
}


// ������ ���������� ���� �� ����� 
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

// ����� ��������� ������ � ��������� ���� � ����������� �������� ����� 
template < typename T >
void DoubleLinkedList< T >::outAll()
{
	Node< T >* current = head_;       // ��������� �� �������
	while (current != nullptr)
	{
		std::cout << current->item_ << ' ';
		current = current->next_;  // ������� � ���������� ��������
	}
	std::cout << std::endl;
}

// ���������� ������	
template < typename T >
DoubleLinkedList< T >::~DoubleLinkedList()
{
	Node< T >* current = nullptr;   // ��������� �� �������, ���������� ��������
	Node< T >* next = head_;        // ��������� �� ��������� �������
	while (next != nullptr) {  // ���� ���� ��� �������� � ������
		current = next;
		next = next->next_;    // ������� � ���������� ��������
		delete current;        // ������������ ������
	}
}

//�������� ����������� ������������
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

//����������� �����������
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

//�������� ����������� �����������
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


