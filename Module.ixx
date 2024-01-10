module;
#include <initializer_list>
#include <iterator>
#include <iostream>
export module Queue;

export namespace Qeeue {
	template <typename T>
	class QueueBasedOnBidirectionalCyclicLinkedList
	{
		using Iterator = T*;

		class CyclicLinkedList
		{
		public:
			CyclicLinkedList();
			CyclicLinkedList(const CyclicLinkedList&);
			CyclicLinkedList(const CyclicLinkedList&&);
			CyclicLinkedList(std::initializer_list<T>);
			~CyclicLinkedList();
			unsigned GetSize() const;
			void InsertAt(int value, int index);
			int RemoveAt(int index);


		private:
			T data;
			CyclicLinkedList* previous;
			CyclicLinkedList* next;
		};
		//CyclicLinkedList list;
		T* list;
		unsigned size;

	public:
		QueueBasedOnBidirectionalCyclicLinkedList();
		explicit QueueBasedOnBidirectionalCyclicLinkedList(unsigned);
		QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList&);
		QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&&);
		QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T>);
		~QueueBasedOnBidirectionalCyclicLinkedList();
		unsigned GetSize();
		QueueBasedOnBidirectionalCyclicLinkedList::Iterator begin();
		QueueBasedOnBidirectionalCyclicLinkedList::Iterator begin() const;
		QueueBasedOnBidirectionalCyclicLinkedList::Iterator end();
		QueueBasedOnBidirectionalCyclicLinkedList::Iterator end() const;
		const int& operator[](int) const;
		int& operator[](int);
		QueueBasedOnBidirectionalCyclicLinkedList& operator=(const QueueBasedOnBidirectionalCyclicLinkedList&);
		QueueBasedOnBidirectionalCyclicLinkedList& operator=(QueueBasedOnBidirectionalCyclicLinkedList&&);
		QueueBasedOnBidirectionalCyclicLinkedList& operator=(std::initializer_list<T>);
		bool Push(const T& element);
		bool Pop(T& element);
		bool Peek(T& element);
	};
















	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList()
		: list(nullptr), size(0)
	{
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(unsigned size)
		: QueueBasedOnBidirectionalCyclicLinkedList<T>()
	{
		this->size = size;
		list = new T[size];
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList<T>& obj)
		: QueueBasedOnBidirectionalCyclicLinkedList()
	{
		list = new T[obj.size];
		size = obj.size;
		for (auto i = 0; i < obj.size; i++)
		{
			list[i] = obj.list[i];
		}
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& obj)
		: QueueBasedOnBidirectionalCyclicLinkedList()
	{
		list = obj.list;
		size = obj.size;
		obj.list = nullptr;
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::~QueueBasedOnBidirectionalCyclicLinkedList()
	{
		delete[] list;
	}

	template <typename T>
	unsigned QueueBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
	{
		return size;
	}

	template<typename T>
	typename QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::begin()
	{
		return Iterator(list);
	}

	template<typename T>
	typename QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::begin() const
	{
		return Iterator(list);
	}

	template<typename T>
	typename QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::end()
	{
		return Iterator(list + size);
	}

	template<typename T>
	typename QueueBasedOnBidirectionalCyclicLinkedList<T>::Iterator QueueBasedOnBidirectionalCyclicLinkedList<T>::end() const
	{
		return Iterator(list + size);
	}

	template<typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist)
		: size(ilist.size())
	{
		list = new T[ilist.size()];
		unsigned i = 0;
		for (const auto& element : ilist)
		{
			list[i++] = element;
		}
	}

	template<typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist)
	{
		return (*this) = QueueBasedOnBidirectionalCyclicLinkedList<T>(ilist);
	}

	template<typename T>
	bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Push(const T& element)
	{
		try {
			QueueBasedOnBidirectionalCyclicLinkedList temp(this->size + 1);
			for (auto i = 0; i < size; i++)
			{
				temp.list[i] = list[i];
			}
			temp[size] = element;
			delete[] list;
			*this = temp;
			temp.list = nullptr;
			return true;
		}
		catch (...) {}
		return false;
	}

	template<typename T>
	bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Pop(T& element)
	{
		try {
			QueueBasedOnBidirectionalCyclicLinkedList temp(this->size - 1);
			for (auto i = 0; i < size; i++)
			{
				temp.list[i] = list[i + 1];
			}
			element = list[size - 1];
			delete[] list;
			*this = temp;
			temp.list = nullptr;
			return true;
		}
		catch (...) {}
		return false;
	}

	template<typename T>
	bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element)
	{
		try
		{
			element = list[0];
			return true;
		}
		catch (...) {}
		return false;
	}

	template <typename T>
	const int& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index) const
	{
		try
		{
			return list[index];
		}
		catch (const std::exception&)
		{

		}
		return NULL;
	}

	template <typename T>
	int& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index)
	{
		try
		{
			return list[index];
		}
		catch (const std::exception&)
		{

		}
	}
	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(const QueueBasedOnBidirectionalCyclicLinkedList& obj)
	{
		list = new T[obj.size];
		size = obj.size;
		for (auto i = 0; i < size; i++)
		{
			list[i] = obj.list[i];
		}
		return *this;
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(QueueBasedOnBidirectionalCyclicLinkedList&& obj)
	{
		size = obj.size;
		list = obj.list;
		obj.list = nullptr;
		return *this;
	}




















	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList()
		: previous(nullptr), data(NULL), next(nullptr)
	{
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(const CyclicLinkedList& obj)
	{
		data = obj.data;
		next = obj.next;
		previous = obj.previous;
	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(const CyclicLinkedList&& obj)
	{

	}

	template <typename T>
	QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::~CyclicLinkedList()
	{
		CyclicLinkedList* iterator = this;
		while (iterator != this)
			delete iterator->data;
		delete this->data;
	}

	template <typename T>
	unsigned QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::GetSize() const
	{
		unsigned size = 0;
		CyclicLinkedList* iterator = this;
		while (iterator != this)
			size++;
		return size;
	}

	//template <typename T>
	//void QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::InsertAt(int value, int index)
	//{
	//}

	//template <typename T>
	//int QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::RemoveAt(int index)
	//{
	//	return 0;
	//}

	//template<typename T>
	//QueueBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(std::initializer_list<T> ilist)
	//	: CyclicLinkedList()
	//{
	//	for each (auto element in ilist)
	//	{
	//		
	//	}
	//}














}