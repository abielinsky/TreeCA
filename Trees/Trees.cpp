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
#include <filesystem>
#include "GUI.h"
#include "font_resource.h"  


const std::string fontPath = "F:/00_COLLEGE_DKI_SOFTWARE_DEVELOPMENT/23_ALGORITHMS_AND_DATA_STRUCTURES/00_TreeCA/TreeCA/fonts/arial.ttf";

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
		else if (choice == 2) {
			cout << endl;
			cout << "number of items: " << tree.countNode() << endl;

			// Get user input for the folder name
			string userFolder;
			cout << "Enter the folder name: ";
			cin >> userFolder;

			// Get the count of nodes inside the user-specified folder
			int countInsideFolder = tree.countNodeInFolder(userFolder);
			cout << "Number of nodes inside '" << userFolder << "' folder: " << countInsideFolder << endl;

			//

		}

		else if (choice == 3) {
			cout << endl;
			
			// Determine the amount of memory used by a given folder using a breadth first algorithm.
			cout << "Total Memory Usage: " << memoryUsage(tree.root) << " bytes" << endl;
			
			// Get user input for the folder name
			string userFolder;
			cout << "Enter the folder name: ";
			cin >> userFolder;

			// Get the size of the specified folder (excluding subfolders)
			int sizeOfFolder = tree.getSizeOfFolder(userFolder);
			cout << "Size of '" << userFolder << "' folder: " << sizeOfFolder << " bytes" << endl;

		}

		else if (choice == 4) {
			cout << endl;
			tree.display();
			cout << endl;
			while (true) {
				int prevCount = tree.countNode();
				pruneEmptyFolder(tree.root, tree);
				if (tree.countNode() == prevCount) {
					break;
				}
			}
			tree.display(); 

			/*
			// Display the tree before pruning
			cout << "Tree before pruning:" << endl;
			tree.display();

			// Prune empty folders
			tree.pruneEmptyFolders();

			// Display the tree after pruning
			cout << "\nTree after pruning:" << endl;
			tree.display();*/
		}

		else if (choice == 5) {			
			string target;
			cout << endl << "Enter the file/folder name to search for: ";
			cin >> target;
			cout << findFileOrFolder(tree.root, target) << std::endl;
		
		}

		else if (choice == 6) {
			string targetFolder;
			cout << endl << "Enter the folder name to display contents: ";
			cin >> targetFolder;
			cout << folderContent(tree, targetFolder);
		}


		else {
			cout << " Invalid choice. Please select a valid option" << endl;
		}
	}
}


// Main function to create the main directory operations GUI window
void stage3() {
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Directory Operations GUI");

	// Load font
	sf::Font font;
	if (!font.loadFromFile(FONT_PATH)) {
		return; // Return if font loading fails
	}

	// Create text for the welcome message
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);
	text.setString("Welcome to the Directory Operations Program");

	float centerX = window.getSize().x / 2.0f;
	float centerY = 30;

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(centerX, centerY);

	const int buttonWidth = 200;
	const int buttonHeight = 50;
	sf::RectangleShape buttons[6];
	sf::Text buttonLabels[6];

	float buttonSpacing = 10;
	float currentY = centerY + textRect.height / 2.0f + buttonSpacing;

	std::string customButtonLabels[6] = {
		"Display Directory Structure",
		"Number of items",
		"Memory usage",
		"Prune Empty Folders",
		"Find File/Folder",
		"Display Folder Contents"
	};

	// Create buttons and labels
	for (int i = 0; i < 6; ++i) {
		buttonLabels[i].setFont(font);
		buttonLabels[i].setCharacterSize(20);
		buttonLabels[i].setFillColor(sf::Color::Magenta);
		buttonLabels[i].setString(customButtonLabels[i]);

		float buttonWidth = buttonLabels[i].getLocalBounds().width + 20;

		buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
		buttons[i].setFillColor(sf::Color::Cyan);
		buttons[i].setPosition(centerX - buttonWidth / 2.0f, currentY);

		sf::FloatRect labelRect = buttonLabels[i].getLocalBounds();
		buttonLabels[i].setOrigin(labelRect.left + labelRect.width / 2.0f, labelRect.top + labelRect.height / 2.0f);
		buttonLabels[i].setPosition(centerX, currentY + buttonHeight / 2.0f);

		currentY += buttonHeight + buttonSpacing;
	}

	// Handle events and display the main window
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					for (int i = 0; i < 6; ++i) {
						if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {

							// Check the button index to perform the corresponding action
							if (i == 0) {
								innerWindow("Tree Structure", tree.getTree(), FONT_PATH);
							}
							else if (i == 1) {
								std::string items = "Number of nodes in a tree: " + std::to_string(tree.countNode());
								innerWindow("Number of Items in a tree", items, FONT_PATH);
							}
							else if (i == 2) {
								std::string memoryInBytes = "Total Memory Usage: " + std::to_string(tree.memoryUsage(tree.root)) + std::string(" Bytes");
								innerWindow("Total Memory Usage", memoryInBytes, FONT_PATH);
							}
							else if (i == 3) {
								tree.pruneEmptyFolders();
								innerWindow("Pruned Tree Structure", tree.getTree(), FONT_PATH);
							}
							else if (i == 4) {
								innerInputWindow(tree, "Complete File Path", "Enter File/Folder name for search", i, FONT_PATH);
							}
							else if (i == 5) {
								innerInputWindow(tree, "Complete File Path", "Enter Folder name for get all Content of folder", i, FONT_PATH);
							}
						}
					}
				}
			}
		}

		window.clear(sf::Color(50, 50, 50)); // Background color

		window.draw(text);

		for (int i = 0; i < 6; ++i) {
			window.draw(buttons[i]);
			window.draw(buttonLabels[i]);
		}

		window.display();
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
			stage3();
		}
		else if (choice != 0) {
			cout << "Wrong Choice" << std::endl;
		}
	}
	return 0;


}
