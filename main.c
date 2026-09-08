#include "editor.h"

int main() {

    int choice;

    printf("=====================================\n");
    printf("      SIMPLE LINE EDITOR IN C\n");
    printf("=====================================\n");

    while (1) {

        showMenu();

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid Input!\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice) {

            case 1:
                insertLine();
                break;

            case 2:
                deleteLine();
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                searchWord();
                break;

            case 5:
                replaceWord();
                break;

            case 6:
                saveFile();
                break;

            case 7:
                loadFile();
                break;

            case 8:
                documentStatistics();
                break;

            case 9:
                undoLastAction();
                break;

            case 10:
                printf("\nThank you for using Line Editor!\n");
                return 0;

            default:
                printf("\nInvalid Choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
        getchar();
    }

    return 0;
}