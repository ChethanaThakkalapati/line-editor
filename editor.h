#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

// Stores the document
extern char document[MAX_LINES][MAX_LENGTH];
extern int lineCount;

// Used for Undo
extern char backupDocument[MAX_LINES][MAX_LENGTH];
extern int backupLineCount;

// Function Prototypes

// Core Features
void insertLine();
void deleteLine();
void displayDocument();

// Bonus Features
void searchWord();
void replaceWord();
void saveFile();
void loadFile();
void documentStatistics();
void undoLastAction();

// Utility Functions
void backupDocumentState();
void showMenu();

#endif