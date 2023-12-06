#pragma once
#include "Tree.h"
#include <fstream>
#include <string>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

// Check there is Root Node of XML Document
bool hasRootElement(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false;
    }

    std::string xmlContent;
    std::string line;

    while (std::getline(file, line)) {
        xmlContent += line;
    }

    file.close();

    size_t openTagStart = xmlContent.find('<');
    size_t openTagEnd = xmlContent.find('>');

    if (openTagStart == std::string::npos || openTagEnd == std::string::npos) {
        std::cout << "Invalid XML: Missing or mismatched opening or closing tags" << std::endl;
        return false;
    }

    std::string openTag = xmlContent.substr(openTagStart + 1, openTagEnd - openTagStart - 1);

    size_t closeTagStart = xmlContent.find("</" + openTag + ">");
    if (closeTagStart == std::string::npos) {
        std::cout << "ERROR: XML documents must have a root element!" << std::endl;
        return false;
    }

    return true;
}

// Validate XML elements must have a closing tag and XML elements must be properly nested
bool validateXML(const std::string& filename) {
    std::ifstream xmlFile(filename);

    if (!xmlFile.is_open()) {
        std::cerr << "Failed to open the XML file." << std::endl;
        return false;
    }

    std::stack<std::string> openTags;
    std::string tag;

    char ch;
    while (xmlFile.get(ch)) {
        if (ch == '<') {
            tag = "";
            while (xmlFile.get(ch) && ch != '>') {
                tag += ch;
            }

            if (tag[0] == '/') {
                if (openTags.empty()) {
                    std::cerr << "Error: Found a closing tag without a corresponding opening tag." << std::endl;
                    xmlFile.close();
                    return false;
                }

                if (tag.substr(1) != openTags.top()) {
                    std::cerr << "Error: Mismatched closing tag: " << tag << std::endl;
                    xmlFile.close();
                    return false;
                }

                openTags.pop();
            }
            else {
                if (tag.find(" ") != std::string::npos) {
                    tag = tag.substr(0, tag.find(" "));
                }
                openTags.push(tag);
            }
        }
    }

    xmlFile.close();

    if (!openTags.empty()) {
        std::cerr << "Error: Some opening tags are not closed." << std::endl;
        return false;
    }

    std::cout << "XML file is valid - all elements have closing tags." << std::endl;
    return true;
}



// XML parsing
struct XMLNode {
    std::string name;
    std::string size;
    std::vector<XMLNode> children;
};

bool parseXML(std::ifstream& file, XMLNode& parent) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("</folder>") != std::string::npos) {
            return true; // End of folder
        }
        else if (line.find("<folder") != std::string::npos) {
            XMLNode folder;
            size_t namePos = line.find("name=\"") + 6;
            size_t sizePos = line.find("size=\"") + 6;
            size_t nameEnd = line.find("\"", namePos);
            size_t sizeEnd = line.find("\"", sizePos);

            if (namePos != std::string::npos && sizePos != std::string::npos) {
                folder.name = line.substr(namePos, nameEnd - namePos);
                folder.size = line.substr(sizePos, sizeEnd - sizePos);
                parent.children.push_back(folder);

                if (!parseXML(file, parent.children.back())) {
                    return false;
                }
            }
        }
        else if (line.find("<file") != std::string::npos) {
            XMLNode file;
            size_t fileNamePos = line.find("name=\"") + 6;
            size_t fileSizePos = line.find("size=\"") + 6;
            size_t fileNameEnd = line.find("\"", fileNamePos);
            size_t fileSizeEnd = line.find("\"", fileSizePos);

            if (fileNamePos != std::string::npos && fileSizePos != std::string::npos) {
                file.name = line.substr(fileNamePos, fileNameEnd - fileNamePos);
                file.size = line.substr(fileSizePos, fileSizeEnd - fileSizePos);
                parent.children.push_back(file);
            }
        }
    }

    return true;
}

// Helper Method to check String is completely numeric or not
bool isNumber(const std::string& str) {
    try {
        size_t pos;
        int value = std::stoi(str, &pos);
        return pos == str.length();
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
}

// Load XML into tree structure
Tree& LoadXML(const XMLNode& node, Tree tree, int level = 0) {

    if (level == 0) {
        tree.setRoot("FileSystem", 0);
        for (const XMLNode& child : node.children) {
            if (isNumber(child.size)) {
                tree.insert("FileSystem", child.name, stoi(child.size));
            }
        }
    }
    else {
        for (const XMLNode& child : node.children) {
            if (isNumber(child.size)) {
                tree.insert(node.name, child.name, stoi(child.size));
            }
        }
    }

    for (const XMLNode& child : node.children) {
        LoadXML(child, tree, level + 1);
    }

    return tree;
}