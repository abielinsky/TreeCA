#pragma once
#include "DList.h"
#include <iostream>
#include <vector>


/*
template<class T>
class Tree
{
public: 
	T data;
	Tree<T> *parent;
	DList<Tree<T>*> *children;
	Tree(T item);
	int count();
	T getData();
};
template <class T>
T Tree<T>::getData()
{
	return data;
}
template <class T>
Tree<T>::Tree(T item)
{

	data = item;
	children = new DList<Tree<T>*>();
	parent = nullptr;
}

template <class T>
int Tree<T>::count()
{
	int c = 1;
	DListIterator<Tree<T>*> iter = children->getIterator();
	while (iter.isValid())
	{
		c += iter.item()->count();
		iter.advance();
	}
	return c;
}
*/

class TreeNode {
public:
	std::string data;
	int size;
	std::vector<TreeNode*> children;

	TreeNode(const std::string& val, int fileSize) : data(val), size(fileSize) {}
};



class Tree {
public:


private:


};

