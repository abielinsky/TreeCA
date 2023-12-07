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


    };
}
