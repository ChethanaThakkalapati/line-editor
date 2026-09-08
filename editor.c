#include "editor.h"

// Global Variables
char document[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

// Backup for Undo
char backupDocument[MAX_LINES][MAX_LENGTH];
int backupLineCount = 0;

// Backup current document
void backupDocumentState() {
    backupLineCount = lineCount;

    for (int i = 0; i < lineCount; i++) {
        strcpy(backupDocument[i], document[i]);
    }
}

// Insert Line
void insertLine() {

    int pos;

    if (lineCount >= MAX_LINES) {
        printf("\nDocument is Full!\n");
        return;
    }

    printf("Enter Line Number (1-%d): ", lineCount + 1);
    scanf("%d", &pos);
    getchar();

    if (pos < 1 || pos > lineCount + 1) {
        printf("Invalid Line Number!\n");
        return;
    }

    backupDocumentState();

    // Shift lines down
    for (int i = lineCount; i >= pos; i--) {
        strcpy(document[i], document[i - 1]);
    }

    printf("Enter Text: ");
    fgets(document[pos - 1], MAX_LENGTH, stdin);

    document[pos - 1][strcspn(document[pos - 1], "\n")] = '\0';

    lineCount++;

    printf("Line Inserted Successfully!\n");
}

// Delete Line
void deleteLine() {

    int pos;

    if (lineCount == 0) {
        printf("Document is Empty!\n");
        return;
    }

    printf("Enter Line Number to Delete: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > lineCount) {
        printf("Invalid Line Number!\n");
        return;
    }

    backupDocumentState();

    for (int i = pos - 1; i < lineCount - 1; i++) {
        strcpy(document[i], document[i + 1]);
    }

    lineCount--;

    printf("Line Deleted Successfully!\n");
}

// Display Document
void displayDocument() {

    if (lineCount == 0) {
        printf("\nDocument is Empty.\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (int i = 0; i < lineCount; i++) {
        printf("%2d. %s\n", i + 1, document[i]);
    }
}

// Search Word
void searchWord() {

    char word[100];
    int found = 0;

    getchar();

    printf("Enter Word to Search: ");
    fgets(word, sizeof(word), stdin);

    word[strcspn(word, "\n")] = '\0';

    printf("\nSearch Results:\n");

    for (int i = 0; i < lineCount; i++) {

        if (strstr(document[i], word) != NULL) {

            printf("Line %d : %s\n", i + 1, document[i]);

            found = 1;
        }
    }

    if (!found)
        printf("Word Not Found.\n");
}

// Find and Replace
void replaceWord() {

    char oldWord[100];
    char newWord[100];

    getchar();

    printf("Enter Word to Replace: ");
    fgets(oldWord, sizeof(oldWord), stdin);

    oldWord[strcspn(oldWord, "\n")] = '\0';

    printf("Enter New Word: ");
    fgets(newWord, sizeof(newWord), stdin);

    newWord[strcspn(newWord, "\n")] = '\0';

    backupDocumentState();

    int replaced = 0;

    for (int i = 0; i < lineCount; i++) {

        char *ptr = strstr(document[i], oldWord);

        if (ptr != NULL) {

            char temp[MAX_LENGTH];

            int index = ptr - document[i];

            strncpy(temp, document[i], index);
            temp[index] = '\0';

            strcat(temp, newWord);
            strcat(temp, ptr + strlen(oldWord));

            strcpy(document[i], temp);

            replaced++;
        }
    }

    if (replaced)
        printf("%d Replacement(s) Done.\n", replaced);
    else
        printf("Word Not Found.\n");
}