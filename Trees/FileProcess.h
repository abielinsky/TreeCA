#pragma once
#include "tree.h"
#include <queue>

// Memory used by a given folder using a breadth first algorithm.
int memoryUsage(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int totalSize = 0;
    std::queue<TreeNode*> nodeQueue;
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

// Prune the tree to remove empty folders
void pruneEmptyFolder(TreeNode* node, Tree tree, const std::string& path = "") {

    if (node == nullptr) {
        return;
    }
    std::string newPath = path;
    if (!newPath.empty()) {
        newPath += "/";
    }
   




    for (TreeNode* child : node->children) {
        pruneEmptyFolder(child, tree, newPath);
    }
}

// Given a partial or complete filename (no path). Generate the path for the given file / folder (Depth first Search)
std::string findFileOrFolder(TreeNode* node, const std::string& target, const std::string& path = "") {
    if (node == nullptr) {
        return "";
    }
    std::string newPath = path;
    if (!newPath.empty()) {
        newPath += "/";
    }
    newPath += node->data;
    if (node->data.find(target) != std::string::npos) {
        return newPath;
    }
    for (TreeNode* child : node->children) {
        std::string result = findFileOrFolder(child, target, newPath);
        if (!result.empty()) {
            return result;
        }
    }
    return "";
}

// Display the contents of a given folder
std::string folderContent(Tree tree, const std::string& targetFolder) {
  
   


    std::string contentString = "Content of Given Folder: " + targetFolder + "\n";


    return contentString;
}


