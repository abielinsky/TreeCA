#pragma once
#include "DList.h"
#include <iostream>
#include <vector>

using namespace std;

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


// Define a TreeNode class to represent nodes in the tree
class TreeNode {
public:
	string data;
	int size;
	vector<TreeNode*> children;

    // Constructor to initialize a tree node with data and size
	TreeNode(const string& val, int fileSize) : data(val), size(fileSize) {}
};


// Define a Tree class to manage the tree structure
class Tree {

public:

    TreeNode* root;      // Pointer to the root of the tree
    int totalNode = 1;  // Total number of nodes in the tree

    // Constructor to initialize the Tree class
    Tree() : root(nullptr) {}

    // Function to set the root of the tree
    void setRoot(const string& val, int size = 0) {
        root = new TreeNode(val, size);
    }

    // Function to insert a node into the tree
    void insert(const string& parentVal, const string& val, int size = 0) {
        if (root == nullptr) {
            cout << "Root is not set. Use setRoot() to set the root node." << std::endl;
            return;
        }
        insertRec(root, parentVal, val, size);
    }

    // Function to display the tree structure
    void display() {
        if (root == nullptr) {
            cout << "Tree is empty." << std::endl;
        }
        else {
            display(root, " ");
        }
    }

    // Function to get the tree structure as a string
    string getTree() {
        if (root == nullptr) {
            return "Tree is empty.";
        }
        else {
            return display2(root, "");
        }
    }


private:

    // Helper function for recursive insertion
    void insertRec(TreeNode* node, const string& parentVal, const string& val, int size = 0) {
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

    // Helper function for recursive tree display
    void display(TreeNode* node, const string& prefix) {
        cout << prefix << "|-" << node->data << " - (" << node->size << ") bytes" << endl;
        for (size_t i = 0; i < node->children.size(); ++i) {
            display(node->children[i], prefix + "  |");
        }
    }


    string display2(TreeNode* node, const string& prefix) {
        string treeStructure = "";

        treeStructure += prefix + "|-" + node->data + "\n";

        for (size_t i = 0; i < node->children.size(); ++i) {
            treeStructure = treeStructure + display2(node->children[i], prefix + "  |");
        }

        return treeStructure;
    }




};

