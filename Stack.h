#pragma once
#include "List.h"

template <class ObjectType>
class Stack : protected List<ObjectType>
{
public:
	Stack() {}
	~Stack() {}
	void push(ObjectType ot)
	{
		this->addLast(ot);
	}
	bool pop()
	{
		return this->removeSelect(this->listSize());
	}
	ObjectType peek()
	{
		return this->findSelect(this->listSize());
	}
	bool isEmpty()
	{
		return this->listSize() == 0;
	}
};
