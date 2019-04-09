#pragma once
#include "List.h"

template <class ObjectType>
class Queue : protected List<ObjectType>
{
public:
	Node<ObjectType>* tail;
	Queue()
	{
		tail = nullptr;
	}

	void enqueue(ObjectType obj)
	{
		this->addFirst(obj);
	}

	ObjectType dequeue()
	{
		ObjectType temp = this->findSelect(this->listSize());
		this->removeSelect(this->listSize());
		return temp;
	}

	ObjectType front()
	{
		return this->findSelect(this->listSize());
	}

	ObjectType back()
	{
		return this->findSelect(0);
	}

	void empty()
	{
		this->clearList();
	}
};