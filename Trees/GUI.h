#ifndef GUI_H
#define GUI_H

// Include necessary SFML and other headers
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tree.h"
#include "FileProcess.h"

// Path to the font file
const std::string FONT_PATH = "F:/00_COLLEGE_DKI_SOFTWARE_DEVELOPMENT/23_ALGORITHMS_AND_DATA_STRUCTURES/00_TreeCA/TreeCA/fonts/arial.ttf";

// Function to display an inner window with a title and description
void innerWindow(const std::string& title, const std::string& description, const std::string& fontPath) {
    // Create a window
    sf::RenderWindow subWindow(sf::VideoMode(700, 600), title);
    subWindow.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font file: " << fontPath << std::endl;
        return; // Return if font loading fails
    }

    // Create text to display the description
    sf::Text text;
    text.setFont(font);
    text.setString(description);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setPosition(20, 20);

    // Handle events and display the window
    while (subWindow.isOpen()) {
        sf::Event subEvent;
        while (subWindow.pollEvent(subEvent)) {
            if (subEvent.type == sf::Event::Closed) {
                subWindow.close();
            }
        }
        subWindow.clear(sf::Color(30, 30, 30)); // Background color
        subWindow.draw(text);
        subWindow.display();
    }
}

// Function to display an input window with a text input field

    void innerInputWindow(Tree & tree, const std::string & title, const std::string & description, int index, const std::string & fontPath) {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), title);

    // Load font
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font file: " << fontPath << std::endl;
        return; // Return if font loading fails
    }

    // Create text to display the input field label
    sf::Text labelText;
    labelText.setFont(font);
    labelText.setCharacterSize(24);
    labelText.setFillColor(sf::Color::Red);
    labelText.setString(description);
    labelText.setPosition(50, 50);

    // Create text to display the input text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(150, 175);

    // Create a rectangle for the input field border
    sf::RectangleShape inputFieldBorder(sf::Vector2f(400, 40));
    inputFieldBorder.setFillColor(sf::Color::Transparent);
    inputFieldBorder.setOutlineColor(sf::Color::Magenta);
    inputFieldBorder.setOutlineThickness(2);
    inputFieldBorder.setPosition(50, 150);

    std::string inputText;

    // Create a rectangle for the submit button
    sf::RectangleShape submitButton(sf::Vector2f(200, 50));
    submitButton.setFillColor(sf::Color::Cyan);
    submitButton.setPosition(50, 210);

    // Create text for the submit button label
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString("Search");
    buttonText.setPosition(120, 220);


    // Create a rectangle for the exit button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300, 210);

    // Create text for the exit button label
    sf::Text exitButtonText;
    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    exitButtonText.setPosition(370, 220);



    // Handle events and display the window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                // ... (existing code)
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ... (existing code)

                    // Check if the exit button is pressed
                    sf::FloatRect exitButtonBounds = exitButton.getGlobalBounds();
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (exitButtonBounds.contains(mousePosition)) {
                        window.close(); // Close the input window
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    // Check the index to determine the action
                    if (index == 4) {
                        std::string completePath = "Complete Path: " + findFileOrFolder(tree.root, inputText);
                        innerWindow(title, completePath, fontPath);
                    }
                    else if (index == 5) {
                        std::string completePath = "File Content: " + folderContent(tree, inputText);
                        innerWindow(title, completePath, fontPath);
                    }
                    window.close(); // Close the input window
                }
            }
        }

        text.setString(inputText);

        window.clear(sf::Color(40, 40, 40)); // Background color
        window.draw(labelText);
        window.draw(inputFieldBorder);
        window.draw(text);
        window.draw(submitButton);
        window.draw(buttonText);
        window.draw(exitButton);
        window.draw(exitButtonText);
      
        window.display();
    }
}


#endif // GUI_H
