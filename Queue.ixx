module;
#include <initializer_list>
#include <iterator>
#include <iostream>
export module Queue;

export namespace Queue {
	template <typename T>
	class QueueBasedOnBidirectionalCyclicLinkedList
	{
		using Iterator = T*;

		class CyclicLinkedList
		{
		public:
			CyclicLinkedList() : data(0), previous(this), next(this) {};
			explicit CyclicLinkedList(T data = T(), CyclicLinkedList* previous = nullptr , CyclicLinkedList* next = nullptr)
				: data(data), previous(previous), next(next)
			{
				if (!this->previous)
					this->previous = this;
				if (!this->next)
					this->next = this;
			};
			CyclicLinkedList* Last() { return previous; };
			CyclicLinkedList* Next() { return this->next; };
			void changePrevious(CyclicLinkedList* previous) { this->previous = previous; }
			T operator++();
			T& Value() { return this->data; };
			CyclicLinkedList(const CyclicLinkedList&);
			CyclicLinkedList(CyclicLinkedList&&);
			explicit CyclicLinkedList(std::initializer_list<T>);
			unsigned GetSize() const;
			void InsertAt(T value, int index) 
			{
				if (!index)
					throw NULL;
				CyclicLinkedList* temp = this;
				if (index < 0)
					for (auto i = index; i < 0; i++)
						temp = temp->previous;
				else
					for (auto i = 0; i > index; i++)
						temp = temp->next;
				temp->next = new CyclicLinkedList(value, temp, temp->next);
				temp->next->next->previous = temp->next;
			};
			T RemoveAt(int index) 
			{
				try {
					CyclicLinkedList* temp = this;
					T data;
					if (index < 0)
						for (auto i = index; i < 0; i++)
							temp = temp->previous;
					else
						for (auto i = 0; i > index; i++)
							temp = temp->next;
					CyclicLinkedList* onDelete = temp;
					temp->next->previous = temp->previous;
					temp->previous->next = temp->next;
					data = onDelete->data;
					delete onDelete;
					return data;
				}
				catch (...) {}
				return T();
			};


		private:
			T data;
			CyclicLinkedList* previous;
			CyclicLinkedList* next;
		};
		CyclicLinkedList* list;
		unsigned size;

	public:
		QueueBasedOnBidirectionalCyclicLinkedList();
		explicit QueueBasedOnBidirectionalCyclicLinkedList(unsigned);
		QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList&);
		QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&&);
		QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T>);
		~QueueBasedOnBidirectionalCyclicLinkedList();
		unsigned GetSize();
		
		Iterator begin();
		Iterator begin() const;
		Iterator end();
		Iterator end() const;
		const T& operator[](int) const;
		T& operator[](int);
		QueueBasedOnBidirectionalCyclicLinkedList<T>& operator=(const QueueBasedOnBidirectionalCyclicLinkedList&);
		QueueBasedOnBidirectionalCyclicLinkedList<T>& operator=(QueueBasedOnBidirectionalCyclicLinkedList&&);
		QueueBasedOnBidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T>);
		bool Push(const T& element);
		bool Pop(T& element);
		bool Peek(T& element);
	};
	





	


template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList()
	: size(0), list(nullptr)
{
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(unsigned size)
{
	if (size <= 0)
		throw 0;
	list = new CyclicLinkedList(T());
	for (auto i = 1; i < size; i++)
		this->Push(0);
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& obj)
{
	list = new CyclicLinkedList(obj.list->Value());
	CyclicLinkedList* iterator = obj.list->Next();
	while (iterator != obj.list)
	{
		Push(iterator->Value());
		iterator = iterator->Next();
	}
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& obj)
{
	list = obj.list;
	size = obj.size;
	obj.list = nullptr;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist)
{
	for (const auto& element : ilist)
	{
		Push(element);
	}
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::~QueueBasedOnBidirectionalCyclicLinkedList()
{
	T temp;
	for (auto i = 0; i < size; i++)
	{
		Pop(temp);
	}
}

template<typename T>
unsigned QueueBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
{
	return size;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::begin()
{
	return Iterator(list);
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::begin() const
{
	return Iterator(list);
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::end()
{
	return Iterator(list->Last());
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::end() const
{
	return Iterator(list->Last());
}

template<typename T>
const T& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index) const
{
	CyclicLinkedList* iterator = this;
	for (auto i = 0; i < index; i++)
		iterator = iterator->Next();
	return iterator->Value();
}

template<typename T>
T& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index)
{
	CyclicLinkedList* iterator = this->list;
	for (auto i = 0; i < index; i++)
		iterator = iterator->Next();
	return iterator->Value();
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(const QueueBasedOnBidirectionalCyclicLinkedList& obj)
{
	*list = *obj.list;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(QueueBasedOnBidirectionalCyclicLinkedList&& obj)
{
	list = obj.list;
	size = obj.size;
	obj.list = nullptr;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist)
{
	for (const auto& element : ilist)
		Push(element);
	return *this;
}

template<typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Push(const T& element)
{
	try {
		if (!list) {
			list = new CyclicLinkedList(element);
			size++;
			return true;
		}
		list->InsertAt(element, -1);
		size++;
		return true;
	}
	catch (...) {}
	return false;
}

template<typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Pop(T& element)
{
	try
	{
		element = list->Value();
		CyclicLinkedList* temp = list;
		list->Last()->changePrevious(list->Next());
		list = list->Next();
		delete temp;
		--size;
		return true;
	}
	catch (...)
	{

	}
	return false;
}

template<typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element)
{
	if (list)
	{
		element = list->Value();
		return true;
	}
	return false;
}




template<typename T>
T QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::operator++()
{
	return list->Next()->Value();
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(const CyclicLinkedList& obj)
{
	const CyclicLinkedList* iterator = obj.next;
	CyclicLinkedList onDelete = this->next;
	this = new CyclicLinkedList(obj.data, this, this);
	while (iterator != obj.previous)
	{
		InsertAt(iterator, -1);
		iterator = iterator->next;
	}
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(CyclicLinkedList&& obj)
{
	next = obj.next;
	previous = obj.previous;
	data = obj.data;
	obj.next = nullptr;
	obj.previous = nullptr;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(std::initializer_list<T> ilist)
{
	CyclicLinkedList* temp = new CyclicLinkedList(T());
	unsigned i = 1;
	for (const auto& element : ilist)
		(*temp).InsertAt(element, i++);
}

template<typename T>
unsigned QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::GetSize() const
{
	CyclicLinkedList* iterator = this->next;
	if (!this->next)
		return 0;
	unsigned count = 1;
	while (iterator != this)
		count++;
	return count;
}
}



