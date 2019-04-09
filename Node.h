#pragma once

template <class ObjectType>
class Node
{
private:
	Node* ptr;//points to the next node
	ObjectType objectData;
public:

	Node(Node *nextPtr, ObjectType ot)
	{
		ptr = nextPtr;
		objectData = ot;
	}
	Node(ObjectType ot)
	{
		ptr = nullptr;
		objectData = ot;
	}
	
	void setNext(Node *next)
	{
		ptr = next;
	}
	Node *getNext()
	{
		return ptr;
	}
	void setData(ObjectType newData)
	{
		objectData = newData;
	}
	ObjectType getData()
	{
		return objectData;
	}
};
