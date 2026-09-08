#include "editor.h"

// Save document to a text file
void saveFile() {

    char filename[100];

    printf("Enter file name to save (example: notes.txt): ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        fprintf(fp, "%s\n", document[i]);
    }

    fclose(fp);

    printf("Document saved successfully to %s\n", filename);
}

// Load document from a text file
void loadFile() {

    char filename[100];
    char buffer[MAX_LENGTH];

    printf("Enter file name to load: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    backupDocumentState();

    lineCount = 0;

    while (fgets(buffer, MAX_LENGTH, fp) != NULL && lineCount < MAX_LINES) {

        buffer[strcspn(buffer, "\n")] = '\0';

        strcpy(document[lineCount], buffer);

        lineCount++;
    }

    fclose(fp);

    printf("File loaded successfully.\n");
}

// Undo last action
void undoLastAction() {

    if (backupLineCount == 0 && lineCount == 0) {
        printf("Nothing to Undo!\n");
        return;
    }

    lineCount = backupLineCount;

    for (int i = 0; i < backupLineCount; i++) {
        strcpy(document[i], backupDocument[i]);
    }

    printf("Last action undone successfully.\n");
}

// Line Count & Word Count
void documentStatistics() {

    int words = 0;

    for (int i = 0; i < lineCount; i++) {

        int inWord = 0;

        for (int j = 0; document[i][j] != '\0'; j++) {

            if (document[i][j] != ' ' &&
                document[i][j] != '\t') {

                if (!inWord) {
                    words++;
                    inWord = 1;
                }

            } else {

                inWord = 0;
            }
        }
    }

    printf("\n========== DOCUMENT STATISTICS ==========\n");
    printf("Total Lines : %d\n", lineCount);
    printf("Total Words : %d\n", words);
}