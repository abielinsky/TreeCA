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
            string rootData = "Vacation";
            tree.setRoot(rootData);

            string parentData = "Vacation";
            string childData = "Beach.jpg";
            int childSize = 23456;

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
            // Arrange
            Tree tree;
            string rootData = "Pictures";
            tree.setRoot(rootData);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Insert nodes to create a sample tree
            tree.insert("Pictures", "Vacation");
            tree.insert("Vacation", "Beach.jpg", 23456);
            tree.insert("Vacation", "Mountains.jpg", 34567);
            tree.insert("Vacation", "Wife");
            tree.insert("Wife", "Love.jpg", 23456);
            tree.insert("Pictures", "Family.jpg", 98765);

            // Call the display function
            tree.display();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Check if the output is not empty
            Assert::IsTrue(!capturedOutput.str().empty());
        }



        TEST_METHOD(TestGetTree)
        {
            // Arrange
            Tree tree;
            string rootData = "Pictures";
            tree.setRoot(rootData);

            // Add some nodes to the tree for testing
            tree.insert("Pictures", "Vacation");
            tree.insert("Vacation", "Beach.jpg", 23456);
            tree.insert("Vacation", "Mountains.jpg", 34567);
            tree.insert("Vacation", "Wife");
            tree.insert("Wife", "Love.jpg", 23456);
            tree.insert("Pictures", "Family.jpg", 98765);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the getTree function
            string treeStructure = tree.getTree();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the output contains the expected content
            Assert::IsTrue(treeStructure.find("Pictures") != string::npos);
            Assert::IsTrue(treeStructure.find("Vacation") != string::npos);
            Assert::IsTrue(treeStructure.find("Beach.jpg") != string::npos);
            Assert::IsTrue(treeStructure.find("Mountains.jpg") != string::npos);
            Assert::IsTrue(treeStructure.find("Wife") != string::npos);
            Assert::IsTrue(treeStructure.find("Love.jpg") != string::npos);
            Assert::IsTrue(treeStructure.find("Family.jpg") != string::npos);
        }

        TEST_METHOD(TestCountNode)
        {
            // Arrange
            Tree tree;
            string rootData = "Pictures";
            tree.setRoot(rootData);

            // Add some nodes to the tree for testing
            tree.insert("Pictures", "Vacation");
            tree.insert("Vacation", "Beach.jpg", 23456);
            tree.insert("Vacation", "Mountains.jpg", 34567);
            tree.insert("Vacation", "Wife");
            tree.insert("Wife", "Love.jpg", 23456);
            tree.insert("Pictures", "Family.jpg", 98765);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = std::cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the countNode function
            int nodeCount = tree.countNode();

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the node count is as expected (1 for the root node + added nodes)
            Assert::AreEqual(7, nodeCount);
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
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Pictures", 3);
            tree.insert("Pictures", "Vacation", 1);
            tree.insert("Vacation", "Beach.jpg", 2);
            tree.insert("Vacation", "Mountains.jpg", 3);
            tree.insert("Vacation", "Wife", 2);
            tree.insert("Wife", "Love.jpg", 2);
            tree.insert("Pictures", "Family.jpg", 2);

            tree.insert("Root", "Music", 5);
            tree.insert("Music", "Song1.mp3", 2);
            tree.insert("Music", "Song2.mp3", 1);
            tree.insert("Music", "Song3.mp3", 2);
            tree.insert("Music", "NewFolder2", 1);

            // Act
            // Call the getSizeOfFolder function
            int picturesSize = tree.getSizeOfFolder("Pictures");
            int musicSize = tree.getSizeOfFolder("Music");

            // Assert
            // Check if the folder size is as expected
            Assert::AreEqual(3, picturesSize); // Size of "Pictures" folder
            Assert::AreEqual(5, musicSize);    // Size of "Music" folder
        }


        TEST_METHOD(TestRemoveNode)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Pictures");
            tree.insert("Pictures", "Vacation");
            tree.insert("Vacation", "Beach.jpg");
            tree.insert("Vacation", "Mountains.jpg");
            tree.insert("Vacation", "Wife");
            tree.insert("Wife", "Love.jpg");
            tree.insert("Pictures", "Family.jpg");

            // Call the remove function to remove a node
            bool removed = tree.remove("Wife");

            // Assert
            // Check if the node is successfully removed
            Assert::IsTrue(removed);

            // Check if the removed node is not present in the tree
            TreeNode* removedNode = tree.find("Wife");
            Assert::IsNull(removedNode);
        }


        TEST_METHOD(TestFind)
        {
            // Arrange
            // Create a tree and set some nodes
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Pictures", 456789);
            tree.insert("Pictures", "Vacation", 123456);
            tree.insert("Vacation", "Beach.jpg", 23456);
            tree.insert("Vacation", "Mountains.jpg", 34567);
            tree.insert("Vacation", "Wife", 123456);
            tree.insert("Wife", "Love.jpg", 23456);
            tree.insert("Pictures", "Family.jpg", 98765);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the find function
            TreeNode* foundNode = tree.find("Vacation");

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Assert
            // Check if the foundNode is not nullptr
            Assert::IsNotNull(foundNode);

            // Check if the foundNode has the correct data
            Assert::AreEqual(string("Vacation"), foundNode->data);
            Assert::AreEqual(123456, foundNode->size); // Adjust based on your data model
        }



        // Test for memory usage with small numbers
        TEST_METHOD(TestMemoryUsage)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Pictures", 1);
            tree.insert("Pictures", "Vacation", 2);
            tree.insert("Vacation", "Beach.jpg", 3);
            tree.insert("Vacation", "Mountains.jpg", 4);
            tree.insert("Vacation", "Wife", 2);
            tree.insert("Wife", "Love.jpg", 3);
            tree.insert("Pictures", "Family.jpg", 2);

            tree.insert("Root", "Music", 5);
            tree.insert("Music", "Song1.mp3", 1);
            tree.insert("Music", "Song2.mp3", 2);
            tree.insert("Music", "Song3.mp3", 3);
            tree.insert("Music", "NewFolder2", 5);

            // Act
            // Call the memoryUsage function
            int totalMemory = tree.memoryUsage(tree.root);

            // Assert
            // Check if the total memory is as expected
            Assert::AreEqual(33, totalMemory); // Sum of sizes of all nodes in the tree
        }



        // Test for memory usage with the provided data
        TEST_METHOD(TestMemoryUsage2)
        {
            // Arrange
            Tree tree;
            tree.setRoot("Root");

            // Add some nodes to the tree for testing
            tree.insert("Root", "Pictures", 1);
            tree.insert("Pictures", "Vacation", 2);
            tree.insert("Vacation", "Beach.jpg", 3);
            tree.insert("Vacation", "Mountains.jpg", 1);
            tree.insert("Vacation", "Wife", 2);
            tree.insert("Wife", "Love.jpg", 1);
            tree.insert("Pictures", "Family.jpg", 3);

            tree.insert("Root", "Music", 1);
            tree.insert("Music", "Song1.mp3", 3);
            tree.insert("Music", "Song2.mp3", 2);
            tree.insert("Music", "Song3.mp3", 3);
            tree.insert("Music", "NewFolder2", 2);

            // Act
            // Call the memoryUsage function to calculate the memory usage
            int totalMemory = tree.memoryUsage(tree.root);

            // Assert
            // Check if the total memory is as expected
            Assert::AreEqual(24, totalMemory); // Sum of sizes of all nodes in the tree
        }


        TEST_METHOD(TestPruneEmptyFolders)
        {
            // Arrange
            Tree tree;

            // Create a tree structure with empty folders
            tree.setRoot("Root", 0);
            tree.insert("Root", "Pictures", 0);
            tree.insert("Pictures", "Vacation", 0);
            tree.insert("Vacation", "Beach.jpg", 0);
            tree.insert("Vacation", "Mountains.jpg", 0);

            tree.pruneEmptyFolders();

            // Assert
            // Check if the tree is empty after pruning empty folders
            Assert::IsNull(tree.root);
        }


        TEST_METHOD(TestFindFilePath)
        {
            // Arrange
            Tree tree;
            tree.setRoot("root");

            // Add some nodes to the tree for testing
            tree.insert("root", "Pictures", 1);
            tree.insert("Pictures", "Vacation", 2);
            tree.insert("Vacation", "Beach.jpg", 3);
            tree.insert("Vacation", "Mountains.jpg", 1);
            tree.insert("Vacation", "Wife", 2);
            tree.insert("Wife", "Love.jpg", 1);
            tree.insert("Pictures", "Family.jpg", 3);

            // Act
            // Call the findFilePath function
            string result = findFileOrFolder(tree.root, "Love.jpg");

            // Assert
            // Check if the result is as expected
            Assert::AreEqual(string("root/Pictures/Vacation/Wife/Love.jpg"), result);
        }

        TEST_METHOD(TestMusicFolderContent)
        {
            // Create a tree and set some nodes based on the provided XML-like structure
            Tree tree;
            tree.setRoot("Music", 987654);
            tree.insert("Music", "Song1.mp3", 456789);
            tree.insert("Music", "Song2.mp3", 567890);
            tree.insert("Music", "Song3.mp3", 678901);
            tree.insert("Music", "NewFolder2", 987654);

            // Redirect cout to capture the output
            stringstream capturedOutput;
            streambuf* coutBuffer = std::cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            // Call the folderContent function using the tree instance for the "Music" folder
            string result = folderContent(tree, "Music");

            // Restore cout
            cout.rdbuf(coutBuffer);

            // Print the captured output for debugging
            cout << "Captured Output:\n" << capturedOutput.str() << endl;

            // Check if the output contains the expected content
            Assert::IsTrue(result.find("Song1.mp3") != string::npos);
            Assert::IsTrue(result.find("Song2.mp3") != string::npos);
            Assert::IsTrue(result.find("Song3.mp3") != string::npos);
            Assert::IsTrue(result.find("NewFolder2") != string::npos);
        }

       


    };
}
