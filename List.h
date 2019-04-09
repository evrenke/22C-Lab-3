#pragma once
#include "Node.h"

template <class ObjectType>
class List
{
private:
	Node<ObjectType> *head;
protected:
	List()
	{
		head = nullptr;
	}
	
	~List()
	{
		clearList();
	}

	void addFirst(ObjectType ot)
	{
		Node<ObjectType> *newFirst;
		if (head == nullptr)
		{
			newFirst = new Node<ObjectType>(nullptr, ot);
			//the only thing in the list upon adding
		}
		else newFirst = new Node<ObjectType>(head, ot);
		head = newFirst;
	}

	void addLast(ObjectType ot)
	{
		Node<ObjectType> *last = head;
		if (head == nullptr)
		{
			addFirst(ot);
			return;
		}
		
		while (last->getNext() != nullptr)
		{
			last = last->getNext();
		}
		last->setNext(new Node<ObjectType>(nullptr, ot));
	}

	bool addSelect(ObjectType ot, int index)
	{
		if (head == nullptr)
		{
			addFirst(ot);
			return true;
		}
		Node<ObjectType> *newPrev = head;
		Node<ObjectType> *newNext = head->getNext();
		int ind;
		for (ind = 0; newNext != nullptr && ind < index; ind++)
		{
			newPrev = newPrev->getNext();
			newNext = newNext->getNext();
		}
		if (ind < index)
			return false;
		Node<ObjectType> *newNode = new Node<ObjectType>(newNext,ot);
		newPrev->setNext(newNode);
		return true;
	}

	ObjectType findSelect(int index)
	{
		Node<ObjectType> *next = head;
		for(int ind = 0; next != nullptr && ind < listSize() && ind < index; ind++)
		{
			if (ind == index - 1)
				return next->getData();
			next = next->getNext();
		}
		return next->getData();
	}

	bool setSelect(ObjectType ot, int setIndex)
	{
		int index = 0;
		Node<ObjectType> *next = head;
		while (index != setIndex && next != nullptr)
		{
			if (index == setIndex)
			{
				next->setData(ot);
				return true;
			}
			index++;
		}
		return false;
	}

	int listSize()
	{
		int size = 0;
		Node<ObjectType> *next = head;
 		while (next != nullptr)
		{
			size++;
			next = next->getNext();
		}
		return size;
	}

	bool removeSelect(int index)
	{
		if (index < 0 || index > listSize())
			return false;
		if (listSize() == 1 || listSize() == 0)
		{
			clearList();
			return true;
		}
		if (listSize() == 2)
		{
			if (index == 2)
			{
				delete head->getNext();
				head->setNext(nullptr);
				return true;
			}
			else
			{
				Node<ObjectType> *temp = head;
				delete head;
				head = temp;
				return true;
			}
		}
		
		Node<ObjectType> *prev = head;
		Node<ObjectType> *next = head->getNext()->getNext();
		int ind;
		for (ind = 0; next != nullptr && ind < index; ind++)
		{
			prev = prev->getNext();
			next = next->getNext();
		}
		delete prev->getNext();
		prev->setNext(next);
		return true;
	}

	void clearList()
	{
		while (head != nullptr)
		{
			Node<ObjectType> *nextOnList = head;
			head = head->getNext();
			delete nextOnList;
		}
		head = nullptr;
	}
};