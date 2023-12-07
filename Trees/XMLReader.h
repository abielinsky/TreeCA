#pragma once
#include "Tree.h"
#include <fstream>
#include <string>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

// Check there is Root Node of XML Document
bool hasRootElement(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false;
    }

    string xmlContent;
    string line;

    while (getline(file, line)) {
        xmlContent += line;
    }

    file.close();

    size_t openTagStart = xmlContent.find('<');
    size_t openTagEnd = xmlContent.find('>');

    if (openTagStart == string::npos || openTagEnd == string::npos) {
        cout << "Invalid XML: Missing or mismatched opening or closing tags" << endl;
        return false;
    }

    string openTag = xmlContent.substr(openTagStart + 1, openTagEnd - openTagStart - 1);

    size_t closeTagStart = xmlContent.find("</" + openTag + ">");
    if (closeTagStart == string::npos) {
        std::cout << "ERROR: XML documents must have a root element!" << endl;
        return false;
    }

    return true;
}

// Validate XML elements must have a closing tag and XML elements must be properly nested
bool validateXML(const string& filename) {
    std::ifstream xmlFile(filename);

    if (!xmlFile.is_open()) {
        cout << "Failed to open the XML file." << endl;
        return false;
    }

    stack<string> openTags;
    string tag;

    char ch;
    while (xmlFile.get(ch)) {
        if (ch == '<') {
            tag = "";
            while (xmlFile.get(ch) && ch != '>') {
                tag += ch;
            }

            if (tag[0] == '/') {
                if (openTags.empty()) {
                    cout << "Error: Found a closing tag without a corresponding opening tag." << std::endl;
                    xmlFile.close();
                    return false;
                }

                if (tag.substr(1) != openTags.top()) {
                    cout << "Error: Mismatched closing tag: " << tag << std::endl;
                    xmlFile.close();
                    return false;
                }

                openTags.pop();
            }
            else {
                if (tag.find(" ") != string::npos) {
                    tag = tag.substr(0, tag.find(" "));
                }
                openTags.push(tag);
            }
        }
    }

    xmlFile.close();

    if (!openTags.empty()) {
        cout << "Error: Some opening tags are not closed." << endl;
        return false;
    }

    cout << "XML file is valid - all elements have closing tags." << endl;
    return true;
}



// XML parsing
struct XMLNode {
    string name;
    string size;
    vector<XMLNode> children;
};

bool parseXML(ifstream& file, XMLNode& parent) {
    string line;
    while (getline(file, line)) {
        if (line.find("</folder>") != string::npos) {
            return true; // End of folder
        }
        else if (line.find("<folder") != string::npos) {
            XMLNode folder;
            size_t namePos = line.find("name=\"") + 6;
            size_t sizePos = line.find("size=\"") + 6;
            size_t nameEnd = line.find("\"", namePos);
            size_t sizeEnd = line.find("\"", sizePos);

            if (namePos != string::npos && sizePos != string::npos) {
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

            if (fileNamePos != string::npos && fileSizePos != string::npos) {
                file.name = line.substr(fileNamePos, fileNameEnd - fileNamePos);
                file.size = line.substr(fileSizePos, fileSizeEnd - fileSizePos);
                parent.children.push_back(file);
            }
        }
    }

    return true;
}

// Helper Method to check String is completely numeric or not
bool isNumber(const string& str) {
    try {
        size_t pos;
        int value = stoi(str, &pos);
        return pos == str.length();
    }
    catch (const invalid_argument& e) {
        return false;
    }
    catch (const out_of_range& e) {
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