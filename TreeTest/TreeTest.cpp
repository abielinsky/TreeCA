#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/Tree.h"
#include "../Trees/FileProcess.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
    TEST_CLASS(TestTree)
    {
    public:

        TEST_METHOD(TestTreeNodeInitialization)
        {
            // Arrange
            string nodeData = "Node Data";
            int nodeSize = 422563;
            TreeNode treeNode(nodeData, nodeSize);
            // Assert
            Assert::AreEqual(nodeData, treeNode.data, L"Node data should match");
            Assert::AreEqual(nodeSize, treeNode.size, L"Node size should match");
            Assert::IsTrue(treeNode.children.empty(), L"Children vector should be initially empty");
        }

        TEST_METHOD(TestRootInsert)
        {
            Tree tree;
            string rootData = "Root Data";
            tree.setRoot(rootData);
            // Use Assert instead of ASSERT, and the correct syntax is Assert::IsNotNull
            Assert::IsNotNull(tree.root);
            // Use Assert::AreEqual for comparing values
            Assert::AreEqual(rootData, tree.root->data);
        }

        TEST_METHOD(TestInsert)
        {
            // Arrange
            Tree tree;
            string rootData = "Programming";
            tree.setRoot(rootData);

            string parentData = "Programming";
            string childData = "Software.doc";
            int childSize = 2000;

            tree.insert(parentData, childData, childSize);

            // Assert
            // Check if the child node is inserted under the parent
            TreeNode* parentNode = tree.find(parentData);
            Assert::IsNotNull(parentNode);
            Assert::AreEqual(childData, parentNode->children[0]->data);
            Assert::AreEqual(childSize, parentNode->children[0]->size);
        }

        TEST_METHOD(TestDisplay)
        {
            Tree fileSystemTree;
            string rootFolderName = "filesystem";
            fileSystemTree.setRoot(rootFolderName);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Insert nodes to create a sample tree based on your provided XML structure
            fileSystemTree.insert("filesystem", "Programming", 1000);
            fileSystemTree.insert("Programming", "Software", 2000);
            fileSystemTree.insert("Software", "Java.doc", 1000);       

            // Call the display function
            fileSystemTree.display();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Check if the output is not empty
            Assert::IsTrue(!capturedOutput.str().empty());
        }




        TEST_METHOD(TestGetTree)
        {
            // Arrange
            Tree fileSystemTree;
            string rootFolderName = "filesystem";
            fileSystemTree.setRoot(rootFolderName);

            // Add some nodes to the tree for testing
            fileSystemTree.insert("filesystem", "Programming", 1000);
            fileSystemTree.insert("Programming", "Software", 2000);
            fileSystemTree.insert("Software", "Java.doc", 1000);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the getTree function
            string treeStructure = fileSystemTree.getTree();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the output contains the expected content
            Assert::IsTrue(treeStructure.find("filesystem") != string::npos);
            Assert::IsTrue(treeStructure.find("Programming") != string::npos);
            Assert::IsTrue(treeStructure.find("Software") != string::npos);
        }


        TEST_METHOD(TestCountNode)
        {
            // Arrange
            Tree fileSystemTree;
            string rootFolderName = "Programming";
            fileSystemTree.setRoot(rootFolderName);

            // Add some nodes to the tree for testing
            fileSystemTree.insert("Programming", "Software", 2000);
            fileSystemTree.insert("Software", "Java.doc", 1000);
            fileSystemTree.insert("Software", "Python.doc", 3000);
            fileSystemTree.insert("Software", "Design", 1000);
            fileSystemTree.insert("Design", "Photoshop.jpg", 5000);
            fileSystemTree.insert("Design", "EmptyFolder1", 4000);
            fileSystemTree.insert("Design", "EmptyFolder2", 3000);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = std::cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the countNode function
            int nodeCount = fileSystemTree.countNode();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the node count is as expected (1 for the root node + added nodes)
            Assert::AreEqual(8, nodeCount);
        }


        TEST_METHOD(TestCountNodeInFolder)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Folder1");
            tree.insert("Root", "Folder2");
            tree.insert("Folder1", "Subfolder1");
            tree.insert("Folder1", "Subfolder2");
            tree.insert("Folder2", "File1");
            tree.insert("Subfolder1", "File2");

            // Act
            // Call the countNodeInFolder function
            int count = tree.countNodeInFolder("Folder1");

            // Assert
            // Check if the count is as expected
            Assert::AreEqual(4, count); // Including "Folder1", "Subfolder1", "Subfolder2", and their contents
        }


        TEST_METHOD(TestGetSizeOfFolder)
        {
            // Arrange
            Tree tree;
            tree.setRoot("filesystem");

            // Add some nodes to the tree for testing
            tree.insert("filesystem", "Programming", 1000);

            // Call the getSizeOfFolder function
            int programmingSize = tree.getSizeOfFolder("Programming");

            // Assert
            // Check if the folder size is as expected
            Assert::AreEqual(1000, programmingSize);  // Size of "Programming" folder
        
        }



        TEST_METHOD(TestRemoveNode)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Programming");
            tree.insert("Root", "Lectures");
            tree.insert("Lectures", "iot.doc");

            // Call the remove function to remove a node
            bool removed = tree.remove("iot.doc");

            // Assert
            // Check if the node is successfully removed
            Assert::IsTrue(removed);

            // Check if the removed node is not present in the tree
            TreeNode* removedNode = tree.find("iot.doc");
            Assert::IsNull(removedNode);
        }


        TEST_METHOD(TestFind)
        {
            // Arrange
            // Create a tree and set some nodes
            Tree tree;
            tree.setRoot("filesystem");

            // Add some nodes to the tree for testing
            tree.insert("filesystem", "Programming", 1000);
            tree.insert("Programming", "Software", 2000);
            tree.insert("Software", "Java.doc", 1000);
            tree.insert("Software", "Python.doc", 3000);
            tree.insert("Software", "Design", 1000);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the find function
            TreeNode* foundNode = tree.find("Programming");

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the foundNode is not nullptr
            Assert::IsNotNull(foundNode);

            // Check if the foundNode has the correct data
            Assert::AreEqual(string("Programming"), foundNode->data);
            Assert::AreEqual(1000, foundNode->size); // Adjust based on your data model
        }




        // Test for memory usage with small numbers
        TEST_METHOD(TestMemoryUsage)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Programming", 1000);
            tree.insert("Root", "Lectures", 2000);
            tree.insert("Lectures", "iot.doc", 1000);
         
            // Call the memoryUsage function
            int totalMemory = tree.memoryUsage(tree.root);

            // Assert
            // Check if the total memory is as expected
            Assert::AreEqual(4000, totalMemory); // Sum of sizes of all nodes in the tree
        }



        // Test for memory usage with the provided data
        TEST_METHOD(TestMemoryUsage2)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Programming", 1000);
            tree.insert("Root", "Lectures", 2000);
            tree.insert("Lectures", "iot.doc", 1000);

            // Call the memoryUsage function to calculate the memory usage
            int totalMemory = tree.memoryUsage(tree.root);

            // Assert
            // Check if the total memory is as expected
            Assert::AreEqual(4000, totalMemory); // Sum of sizes of all nodes in the tree
        }


        TEST_METHOD(TestPruneEmptyFolders)
        {
            // Arrange
            Tree tree;

            // Create a tree structure with empty folders
            tree.insert("Root", "Programming", 0);
            tree.insert("Root", "Lectures", 0);
            tree.insert("Lectures", "iot.doc", 0);

            tree.pruneEmptyFolders();

            // Assert
            // Check if the tree is empty after pruning empty folders
            Assert::IsNull(tree.root);
        }


        TEST_METHOD(TestFindFilePath)
        {
            // Arrange
            Tree tree;
           
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Programming", 1000);
            tree.insert("Root", "Lectures", 2000);
            tree.insert("Lectures", "iot.doc", 1000);
    
            // Call the findFilePath function
            string result = findFileOrFolder(tree.root, "iot.doc");

            // Assert
            // Check if the result is as expected
            Assert::AreEqual(string("Root/Lectures/iot.doc"), result);
        }


        TEST_METHOD(TestLecturesFolderContent)
        {
            // Create a tree and set some nodes based on the provided XML-like structure
            Tree tree;
            tree.setRoot("Lectures", 2000);
            tree.insert("Lectures", "Algorithms.doc", 2000);
            tree.insert("Lectures", "Data.doc", 3000);
            tree.insert("Lectures", "iot.doc", 5000);
            tree.insert("Lectures", "EmptyFolder1", 1000);
            tree.insert("Lectures", "EmptyFolder2", 4000);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = std::cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the folderContent function using the tree instance for the "Music" folder
            string result = folderContent(tree, "Lectures");

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Print the captured output for debugging
            cout << "Captured Output:\n" << capturedOutput.str() << endl;

            // Check if the output contains the expected content
            Assert::IsTrue(result.find("Algorithms.doc") != string::npos);
            Assert::IsTrue(result.find("Data.doc") != string::npos);
            Assert::IsTrue(result.find("iot.doc") != string::npos);
            Assert::IsTrue(result.find("EmptyFolder1") != string::npos);
            Assert::IsTrue(result.find("EmptyFolder2") != string::npos);
        }

       


    };
}
