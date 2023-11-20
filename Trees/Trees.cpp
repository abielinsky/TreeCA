// Trees.cpp : Defines the entry point for the console application.
//
#include "Tree.h"
#include "TreeIterator.h"
#include <string>
#include <iostream>
#include <queue>

#include "SFML/Graphics.hpp"

using namespace std;
/*
	The indented parenthetic representation of a tree
*/


void displayTree(TreeIterator<string> iter, string indent)
{
	cout << indent << iter.node->data ;
	if (iter.childValid())
	{
		cout << "(" <<endl;
	
	while (iter.childValid())
	{
		TreeIterator<string> iter2(iter.childIter.currentNode->data);
		displayTree(iter2, "\t" + indent);
		iter.childForth();
	}
	cout <<indent<< ")" ;
	}
	cout << endl;
}
/*
	Print using a Depth First Search
*/
void printDFS(TreeIterator<string> iter)
{
	while (iter.childValid())
	{
		TreeIterator<string> iter2(iter.childIter.currentNode->data);
		printDFS(iter2);
		iter.childForth();
	}
	cout << iter.item() << ", ";
}
/*
	Print using a Breadth first Search
*/
void printBFS(Tree<string> tree)
{
	queue<Tree<string>> queue;
	queue.push(tree);
	while (!queue.empty())
	{
		DListIterator<Tree<string>*> iter = queue.front().children->getIterator();
		while (iter.isValid())
		{
			queue.push(*iter.item());
			iter.advance();
		}
		cout << queue.front().data << ", ";
		queue.pop();

	}


}
/*
	Code to test for question 1
*/
void question1()
{
	Tree<string>* root = new Tree<string>("Sales");
	TreeIterator<string> iter(root);
	iter.appendChild("Domestic");
	iter.appendChild("Iternational");
	iter.childForth();
	iter.down();
	iter.appendChild("Canada");
	iter.appendChild("South America");
	iter.appendChild("Overseas");
	iter.childForth();
	iter.childForth();
	iter.down();
	iter.appendChild("Africa");
	iter.appendChild("Europe");
	iter.appendChild("Asia");
	iter.appendChild("Australia");
	iter.root();
	displayTree(iter, "");

}
/*
	Code to test question 2 & 3.
*/
void question2()
{
	Tree<string>* root = new Tree<string>("Sales");
	TreeIterator<string> iter(root);
	iter.appendChild("Domestic");
	iter.appendChild("Iternational");
	iter.childForth();
	iter.down();
	iter.appendChild("Canada");
	iter.appendChild("South America");
	iter.appendChild("Overseas");
	iter.childForth();
	iter.childForth();
	iter.down();
	iter.appendChild("Africa");
	iter.appendChild("Europe");
	iter.appendChild("Asia");
	iter.appendChild("Australia");
	iter.root();
	printBFS(*root);
	delete root;
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 800), "Test");
	sf::Event e;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		
	}


	//question2();
    return 0;





}
