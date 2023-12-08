#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trees/Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
    TEST_CLASS(TestTree)
    {
    public:

        TEST_METHOD(TestRootInsert)
        {
            Tree tree;
            std::string rootData = "Root Data";
            tree.setRoot(rootData);
            // Use Assert instead of ASSERT, and the correct syntax is Assert::IsNotNull
            Assert::IsNotNull(tree.root);
            // Use Assert::AreEqual for comparing values
            Assert::AreEqual(rootData, tree.root->data);
        }

        TEST_METHOD(TestAppendValueWithRoot)
        {
            Tree treeWithRoot;
            std::string rootData = "Root Data";

            // Set the root node with the provided data
            treeWithRoot.setRoot(rootData);

            // Insert three child nodes under the root
            treeWithRoot.insert("Root Data", "Child 1");
            treeWithRoot.insert("Root Data", "Child 2");
            treeWithRoot.insert("Root Data", "Child 3");

            // Assert that the root node has three children with the correct data
            Assert::AreEqual(3, static_cast<int>(treeWithRoot.root->children.size()));
            Assert::AreEqual(std::string("Child 1"), treeWithRoot.root->children[0]->data);
            Assert::AreEqual(std::string("Child 2"), treeWithRoot.root->children[1]->data);
            Assert::AreEqual(std::string("Child 3"), treeWithRoot.root->children[2]->data);
        }


    };
}
