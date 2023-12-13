#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tree.h"
#include "FileProcess.h"

const std::string FONT_PATH = "F:/00_COLLEGE_DKI_SOFTWARE_DEVELOPMENT/23_ALGORITHMS_AND_DATA_STRUCTURES/00_TreeCA/TreeCA/fonts/arial.ttf";

void innerWindow(const std::string& title, const std::string& description, const std::string& fontPath) {
    sf::RenderWindow subWindow(sf::VideoMode(700, 900), title);
    subWindow.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font file: " << fontPath << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(description);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);

    sf::RectangleShape exitButton(sf::Vector2f(100, 40));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(600, 850);

    sf::Text exitButtonText;
    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(20);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    exitButtonText.setPosition(620, 860);

    while (subWindow.isOpen()) {
        sf::Event subEvent;
        while (subWindow.pollEvent(subEvent)) {
            if (subEvent.type == sf::Event::Closed) {
                subWindow.close();
            }
            else if (subEvent.type == sf::Event::MouseButtonPressed) {
                if (subEvent.mouseButton.button == sf::Mouse::Left) {
                    sf::FloatRect exitButtonBounds = exitButton.getGlobalBounds();
                    sf::Vector2f mousePosition = sf::Vector2f(subEvent.mouseButton.x, subEvent.mouseButton.y);
                    if (exitButtonBounds.contains(mousePosition)) {
                        subWindow.close(); // Close the inner window
                    }
                }
            }
        }
        subWindow.clear(sf::Color(30, 30, 30)); // Background color
        subWindow.draw(text);
        subWindow.draw(exitButton);
        subWindow.draw(exitButtonText);
        subWindow.display();
    }
}

void innerInputWindow(Tree& tree, const std::string& title, const std::string& description, int index, const std::string& fontPath) {
    sf::RenderWindow window(sf::VideoMode(800, 900), title);

    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font file: " << fontPath << std::endl;
        return;
    }

    sf::Text labelText;
    labelText.setFont(font);
    labelText.setCharacterSize(24);
    labelText.setFillColor(sf::Color::Black);
    labelText.setString(description);
    labelText.setPosition(50, 50);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 150);

    sf::RectangleShape inputFieldBorder(sf::Vector2f(400, 40));
    inputFieldBorder.setFillColor(sf::Color::Transparent);
    inputFieldBorder.setOutlineColor(sf::Color::Black);
    inputFieldBorder.setOutlineThickness(2);
    inputFieldBorder.setPosition(50, 150);

    std::string inputText;

    sf::RectangleShape submitButton(sf::Vector2f(200, 50));
    submitButton.setFillColor(sf::Color::Cyan);
    submitButton.setPosition(50, 210);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString("Search");
    buttonText.setPosition(120, 220);

    sf::RectangleShape exitButton(sf::Vector2f(100, 40));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300, 210);

    sf::Text exitButtonText;
    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(20);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    exitButtonText.setPosition(320, 220);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && !inputText.empty()) {
                        inputText.pop_back();
                    }
                    else if (event.text.unicode >= 32) {
                        inputText += static_cast<char>(event.text.unicode);
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::FloatRect buttonBounds = submitButton.getGlobalBounds();
                    sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (buttonBounds.contains(mousePosition)) {

                        if (index == 4) {
                            std::string completePath = "Complete Path: " + findFileOrFolder(tree.root, inputText);
                            innerWindow(title, completePath, fontPath);
                        }
                        else if (index == 5) {
                            std::string completePath = "File Content: " + folderContent(tree, inputText);
                            innerWindow(title, completePath, fontPath);
                        }

                    }
                    else if (exitButton.getGlobalBounds().contains(mousePosition)) {
                        window.close(); // Close the input window
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
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

        window.clear(sf::Color::White);
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
