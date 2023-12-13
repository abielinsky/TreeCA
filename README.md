# TreeCA
 AlgorithmsAndDataStructures

# File Management System

## Overview

This C++ project implements a file management system using a Tree data structure. The system allows users to view, retrieve, and remove files and folders. The solution loads the file system from an XML document, validates the XML structure, and provides a command-line interface (CLI) for various file management tasks. Additionally, it includes a graphical user interface (GUI) developed using SFML.

## Project Structure

The project is organized into three stages:

1. **Stage 1: Load XML Document into Tree**
    - Parses and validates XML documents to load the file tree into a Tree data structure.
    - Implements XML validation rules using a stack data structure.

2. **Stage 2: Command-Line Application**
    - Provides a CLI for interacting with the Tree data structure.
    - Tasks include determining the number of items, calculating memory usage, pruning empty folders, finding files/folders, and displaying folder contents.

3. **Stage 3: GUI using SFML**
    - Implements a graphical user interface using SFML.
    - Provides a user-friendly way to perform file management tasks.

## Implementation Details

### XML Document Validation

### Unit Testing

The project follows a Test Driven Development (TDD) approach. Each function is thoroughly tested:
- Stubs are created for classes and functions.
- Tests are written, run, failed, and then code is refactored until success.

