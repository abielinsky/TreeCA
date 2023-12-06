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

    TreeNode* root;
    int totalNode = 1;

    Tree() : root(nullptr) {}

    void setRoot(const std::string& val, int size = 0) {
        root = new TreeNode(val, size);
    }

    void insert(const std::string& parentVal, const std::string& val, int size = 0) {
        if (root == nullptr) {
            std::cout << "Root is not set. Use setRoot() to set the root node." << std::endl;
            return;
        }
        insertRec(root, parentVal, val, size);
    }

    void display() {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
        }
        else {
        //    display(root, " ");
        }
    }

    std::string getTree() {
        if (root == nullptr) {
            return "Tree is empty.";
        }
        else {
            return display2(root, "");
        }
    }


private:

    void insertRec(TreeNode* node, const std::string& parentVal, const std::string& val, int size = 0) {
        if (node->data == parentVal) {
            for (const auto& child : node->children) {
                if (child->data == val && root->data != parentVal) {
                    return;
                }
            }
            node->children.push_back(new TreeNode(val, size));
            return;
        }
        for (auto child : node->children) {
            insertRec(child, parentVal, val, size);
        }
    }


    std::string display2(TreeNode* node, const std::string& prefix) {
        std::string treeStructure = "";

        treeStructure += prefix + "|-" + node->data + "\n";

        for (size_t i = 0; i < node->children.size(); ++i) {
            treeStructure = treeStructure + display2(node->children[i], prefix + "  |");
        }

        return treeStructure;
    }




};

