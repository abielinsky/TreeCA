// Trees.cpp : Defines the entry point for the console application.
//
#include "Tree.h"
#include "TreeIterator.h"
#include <string>
#include <iostream>
#include <queue>

#include "XMLReader.h"
#include "FileProcess.h"
#include <fstream>
#include <stack>
#include <vector>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;


Tree tree;

void stage1() {
	ifstream file("document.xml");
	if (!file.is_open()) {
		cout << "Failed to open the XML file." << endl;
		return;
	}
	if (!hasRootElement("document.xml") && !validateXML("document.xml")) {
		return;
	}

	XMLNode root;

	parseXML(file, root);
	tree = LoadXML(root, tree);
	//tree.display();

}

void stage2() {

	cout << "Welcome to the Directory Operations Program Stage 2" << endl;


	int choice = -1;

	while (choice != 0) {
		cout << " -----------------------------------------" << endl;
		cout << " ----------- Choose an operation ---------" << endl;
	    cout << "1. Display Directory Structure" <<  endl;
		cout << "2. Determine the number of items" <<  endl;
		cout << "3. Determine memory usage" <<  endl;
		cout << "4. Prune Empty Folders" <<  endl;
		cout << "5. Find File/Folder" <<  endl;
		cout << "6. Display Folder Contents" <<  endl;
		cout << "0. Exit" << std::endl;
		cout << " -----------------------------------------" << endl;

		cout << "Enter your choice: ";
		cin >> choice;
	
		if (choice == 1) {
			cout << endl;
			tree.display();
		}
		if (choice == 2) {
			cout << endl;
			cout << "number of items: " << tree.countNode() << endl;
		}



		else {
			cout << " Invalid choice. Please select a valid option" << endl;
		}
	}
}



/*
	Print using a Depth First Search
*/
/*
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
/*
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

*/
/*
	Code to test for question 1
*/
/*
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
/*
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
*/




int main()
{
	/* CODE TO TEST THE SFML GRAPHIC WORKING*/
	/*  THIS IS A TEST TO CHECK THAT THE SFML GRAPHICS ARE WORKING PROPERLY 
	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Initial position of the circle
	float circlePosX = 100.f;
	float circlePosY = 200.f;

	// Speed of the circle movement
	float moveSpeed = 0.1f;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				// Handle window resizing here
				// You might want to update the view or do something else
				break;
			}
		}

		// Update the circle's position
		circlePosX += moveSpeed;

		// Check if the circle goes beyond the right edge, and wrap it to the left
		if (circlePosX > window.getSize().x)
			circlePosX = -shape.getRadius();  // Set to a negative value to start from the left edge

		window.clear();

		// Set the position of the circle
		shape.setPosition(circlePosX, circlePosY);

		window.draw(shape);
		window.display();
	}
	*/




	// Initialize choice to -1 to ensure the loop runs at least once
	int choice = -1;

	// Loop until the user chooses to exit (enters 0)
	while (choice != 0) {
		cout << "--------------------------------------------------" << endl;
		cout << "Which one you want to run!" << endl;
		cout << "Stage 1) Load XML (BEFORE OTHER OPTIONS)" << endl;
		cout << "Stage 2) File Process Management (cmd)" << endl;
		cout << "Stage 3) File Process Management (gui)" << endl;
		cout << "----- 0) for Exit" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Enter Your Choice: ";
		cin >> choice;
		cout << endl;

		if (choice == 1) {
			stage1();
		}
		else if (choice == 2) {
			stage2();
		}
		else if (choice == 3) {
		//	stage3();
		}
		else if (choice != 0) {
			cout << "Wrong Choice" << std::endl;
		}
	}
	return 0;


}
