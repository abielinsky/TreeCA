#pragma once
#include "tree.h"
#include <queue>

using namespace std;

// Function to calculate the memory used by a given folder using breadth-first search
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

        // Enqueue all children of the current node
        for (TreeNode* child : currentNode->children) {
            nodeQueue.push(child);
        }
    }
    return totalSize;
}

// Prune the tree to remove empty folders
void pruneEmptyFolder(TreeNode* node, Tree tree, const std::string& path = "") {

    if (node == nullptr) {
        return;
    }
    std::string newPath = path;
    if (!newPath.empty()) {
        newPath += "/";
    }
    newPath += node->data;
    if (node->children.empty()) {
        if (node->data.find('.') == std::string::npos) {
            tree.remove(node->data);
        }
    }
    for (TreeNode* child : node->children) {
        pruneEmptyFolder(child, tree, newPath);
    }
}



// Find a given file/folder given a partial or complete filename using Depth-First Search (DFS)
string findFileOrFolder(TreeNode* node, const string& target, const string& path = "") {
    // If the current node is null, return an empty string (not found)
    if (node == nullptr) {
        return "";
    }

    // Construct the new path by appending the current node's data to the given path
    string newPath = path + (path.empty() ? "" : "/") + node->data;

    // Check if the target string is found in the current node's data
    if (node->data.find(target) != string::npos) {
        return newPath;
    }

    
    for (TreeNode* child : node->children) {   // Recursively search in each child node
       
        string result = findFileOrFolder(child, target, newPath);   // Recursively search in the child node, updating the path
        if (!result.empty()) {     // If the result is not empty (file/folder found), return it
            return result;
        }
    }

    // If the target is not found in the current node or its children, return an empty string
    return "";
}






// Display the contents of a given folder
string folderContent(Tree tree, const string& targetFolder) {

    // Find the node corresponding to the target folder in the tree
    TreeNode* curNode = tree.find(targetFolder);

    // Check if the folder is not found
    if (curNode == nullptr) {
        return "Folder not found: " + targetFolder;
    }

    // Initialize a string to store the folder content information
    string contentString = "Content of Given Folder: " + targetFolder + "\n";

    // Iterate through each child of the target folder node
    for (TreeNode* child : curNode->children) {
        // Check if the child represents a subfolder or a file
        if (child->data.find('.') == std::string::npos) {
            contentString += "Folder: " + child->data + "\n";
        }
        else {
            contentString += "File: " + child->data + " - Size: " + std::to_string(child->size) + " bytes\n";
        }
    }

    return contentString;
}


