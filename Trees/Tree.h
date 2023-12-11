#pragma once
#include "DList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "fstream"

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

    // -------------->  TEST_METHOD(TestTreeNodeInitialization) <----------------------
	string data;
	int size;
	vector<TreeNode*> children;

    // Constructor to initialize a tree node with data and size
	TreeNode(const string& val, int fileSize) : data(val), size(fileSize) {}


    // Recursive function to prune empty folders
    bool pruneEmptyFolders() {
        for (auto it = children.begin(); it != children.end(); ) {
            if ((*it)->pruneEmptyFolders()) {
                delete* it;
                it = children.erase(it);
            }
            else {
                ++it;
            }
        }

        // Return true if this folder is empty and has been pruned
        return size == 0 && children.empty();
    }

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
            cout << "Root is not set. Use setRoot() to set the root node." << endl;
            return;
        }
        insertRec(root, parentVal, val, size);
    }

    // Function to display the tree structure
    void display() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
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

    // Returns the count, including the root node
    int countNode() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
        }
        else {
            totalNode = 0;
            countNode(root);
        }
        return totalNode + 1;

    }

    // Count the number of nodes inside the specified folder and its subfolders
    int countNodeInFolder(const string& targetFolder) {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return 0;
        }
        return countNodeInFolder(root, targetFolder);
    }


    // Determine the amount of memory used by a given folder using a breadth-first algorithm
    int memoryUsage(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int totalSize = 0;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            TreeNode* currentNode = nodeQueue.front();
            nodeQueue.pop();

            totalSize += currentNode->size;

            for (TreeNode* child : currentNode->children) {
                nodeQueue.push(child);
            }
        }
        return totalSize;
    }

    // Get the size of the specified folder (excluding subfolders)
    int getSizeOfFolder(const string& targetFolder) {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return 0;
        }
        return getSizeOfFolder(root, targetFolder);
    }


    
    // Prune empty folders from the tree
    void pruneEmptyFolders() {
        if (root != nullptr) {
            root->pruneEmptyFolders();
            if (root->size == 0 && root->children.empty()) {
                delete root;
                root = nullptr;
            }
        }
    }



    bool remove(const string& val) {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return false;
        }

        if (root->data == val) {
            cout << "Cannot remove the root node using this method." << endl;
            return false;
        }

        return removeRec(root, val);
    }


    // Find a node with a specific value in the tree
    TreeNode* find(const string& val) {
        // Check if the tree is empty
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return nullptr;
        }

        return findRec(root, val);
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

    // Private recursive function to traverse the tree and count nodes
    void countNode(TreeNode* node) {
        // Increment the totalNode count by the number of children the current node has
        totalNode += node->children.size();
        for (size_t i = 0; i < node->children.size(); i++) {
            countNode(node->children[i]);
        }
    }


    // Recursive helper function to count the number of nodes inside the specified folder and its subfolders
    int countNodeInFolder(TreeNode* node, const string& targetFolder) {
        if (node->data == targetFolder) {
            return countAllNodes(node); // Count all nodes starting from the target folder
        }

        int count = 0;
        for (size_t i = 0; i < node->children.size(); ++i) {
            count += countNodeInFolder(node->children[i], targetFolder);
        }

        return count;
    }

    // Recursive helper function to count all nodes starting from a given node
    int countAllNodes(TreeNode* node) {
        int count = 1; // Count the current node

        for (size_t i = 0; i < node->children.size(); ++i) {
            count += countAllNodes(node->children[i]);
        }

        return count;
    }




    // Recursive helper function to get the size of the specified folder (excluding subfolders)
    int getSizeOfFolder(TreeNode* node, const string& targetFolder) {
        if (node->data == targetFolder) {
            return node->size; // Return the size of the specified folder
        }

        int size = 0;
        for (size_t i = 0; i < node->children.size(); ++i) {
            size += getSizeOfFolder(node->children[i], targetFolder);
        }

        return size;
    }


    bool removeRec(TreeNode* parent, const std::string& val) {
        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
            if ((*it)->data == val) {
                delete (*it);
                parent->children.erase(it);
                return true;
            }
            else {
                if (removeRec(*it, val)) {
                    return true;
                }
            }
        }

        return false;
    }



    // Recursive helper function to find a node with a specific value in the tree
    TreeNode* findRec(TreeNode* node, const std::string& val) {
        // Check if the current node's data matches the target value
        if (node->data == val) {
            return node;
        }

        // Recursively search in each child node
        for (auto child : node->children) {
            TreeNode* found = findRec(child, val);

            // If the node is found in the current subtree, return it
            if (found != nullptr) {
                return found;
            }
        }

        return nullptr;
    }


};

