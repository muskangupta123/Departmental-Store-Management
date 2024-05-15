#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define ANSI_COLOR_RED_BACKGROUND "\033[41m"
#define ANSI_COLOR_GREEN_BACKGROUND "\033[42m"
#define ANSI_COLOR_BLUE_BACKGROUND "\033[44m"
#define ANSI_COLOR_WHITE_TEXT "\033[97m"
#define ANSI_COLOR_RESET "\033[0m"

// Structure to represent an item
typedef struct {
    char code[10];
    char name[50];
    float rate;
    int quantity;
} Item;

// Array to store items
Item items[MAX_ITEMS];
int itemCount = 0;

// Function prototypes
void loadItemsFromFile();
void saveItemsToFile();
void addItem();
void editItem();
void displayAll();
void searchItems();
void deleteItem();
void calculateBill();
void clearScreen();
void printMenu();
// main function for the choices 
int main() {
    loadItemsFromFile(); // to Load items from a file at program starting

    int choice;

    while (1) {
//        clearScreen();
        printMenu();
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                editItem();
                break;
            case 3:
                displayAll();
                break;
            case 4:
                searchItems();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                calculateBill();
                break;
            case 7:
                saveItemsToFile(); // Save 
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
    getch();
}

void loadItemsFromFile() {
    FILE *file = fopen("items.dat", "rb"); // creating a file
    if (file == NULL) {
        return; // File doesn't exist or can't be opened
    }

    fread(&itemCount, sizeof(int), 1, file);
    fread(items, sizeof(Item), itemCount, file);

    fclose(file);
}

void saveItemsToFile() {
    FILE *file = fopen("items.dat", "wb"); // entering the details in the file
    if (file == NULL) {
        printf("Error: Cannot save data to file.\n");
        return;
    }

    fwrite(&itemCount, sizeof(int), 1, file);
    fwrite(items, sizeof(Item), itemCount, file);

    fclose(file);
}

void addItem() {
    if (itemCount < MAX_ITEMS) {
        Item newItem;

        printf("\n\tEnter item code: ");
        scanf("%s", newItem.code);
        printf("\n\tEnter item name: ");
        scanf("%s", newItem.name);
        printf("\n\tEnter item rate: ");
        scanf("%f", &newItem.rate);
        printf("\n\tEnter item quantity: ");
        scanf("%d", &newItem.quantity);

        items[itemCount++] = newItem;
        printf("\n\tItem added successfully!\n");
    } else {
        printf("\n\tMax item limit reached. Cannot add more items.\n");
    }
    getchar(); // Consume newline character
    printf("\nPress Enter to continue...");
    getchar();
}

void editItem() {
    char searchCode[10];
    int found = 0;
    int i;

    printf("\n\tEnter item code to edit: ");
    scanf("%s", searchCode);

    for (i = 0; i < itemCount; i++) {
        if (strcmp(items[i].code, searchCode) == 0) {
            printf("\n\tEnter new item name: ");
            scanf("%s", items[i].name);
            printf("\n\tEnter new item rate: ");
            scanf("%f", &items[i].rate);
            printf("\n\tEnter new item quantity: ");
            scanf("%d", &items[i].quantity);
            found = 1;
            printf("\n\tItem updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\n\tItem not found.\n");
    }
    getchar(); // Consume newline character
    printf("\n\tPress Enter to continue...");
    getchar();
}

//void displayAll() {
//	int i;
//    if (itemCount == 0) {
//        printf("\n\tNo items in the inventory.\n");
//    } else {
//        printf("Inventory:\n");
//        printf("-------------------------------------------------\n");
//        printf("Code\tName\t\tRate\tQuantity\n");
//        printf("-------------------------------------------------\n");
//
//        for (i = 0; i < itemCount; i++) {
//            printf("%s\t%s\t\t%.2f\t%d\n", items[i].code, items[i].name, items[i].rate, items[i].quantity);
//        }
//    }
////    printf("Press Enter to continue...");
////    getchar();
//}
void displayAll() {
	int i;
    if (itemCount == 0) {
        printf("\n\tNo items in the inventory.\n");
    } else {
        printf("\n\tInventory:\n");
        printf("\t++-------++------------------------++----------++----------++\n");
        printf("\t|| Code  || Name                   || Rate     || Quantity ||\n");
        printf("\t++-------++------------------------++----------++----------++\n");

        for ( i = 0; i < itemCount; i++) {
            printf("\t|| %-5s || %-22s || %-8.2f || %-8d ||\n", items[i].code, items[i].name, items[i].rate, items[i].quantity);
        }

        printf("\t++-------++------------------------++----------++----------++\n");
    }
    getchar(); // Consume newline character
    printf("\nPress Enter to continue...");
    getchar();
}
//
void searchItems() {
    int choice,i;

    printf("\n\tSearch by:\n");
    printf("\t\t1. Item Code\n");
    printf("\t\t2. Item Rate Range\n");
    printf("\t\t3. Back to Main Menu\n");
    printf("\t\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char searchCode[10];
        int found = 0;

        printf("\n\tEnter item code to search: ");
        scanf("%s", searchCode);

        for (i = 0; i < itemCount; i++) {
            if (strcmp(items[i].code, searchCode) == 0) {
                printf("\n\tItem found:\n");
                printf("\t++-------++------------------------++----------++----------++\n");
                printf("\t|| Code  || Name                   || Rate     || Quantity ||\n");
                printf("\t++-------++------------------------++----------++----------++\n");
                printf("\t|| %s    || %s                 || %.2f    || %d        || \n", items[i].code, items[i].name, items[i].rate, items[i].quantity);
                printf("\t++-------++------------------------++----------++----------++\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("\n\tItem not found.\n");
        }
        getchar(); // Consume newline character
        printf("\n\tPress Enter to continue...");
        getchar();
    } else if (choice == 2) {
        float minRate, maxRate;

        printf("\n\tEnter minimum item rate: ");
        scanf("%f", &minRate);
        printf("\n\tEnter maximum item rate: ");
        scanf("%f", &maxRate);

        printf("\n\tItems within the rate range:\n");
        printf("\n\tCode\tName\t\tRate\tQuantity\n");

        for (i = 0; i < itemCount; i++) {
            if (items[i].rate >= minRate && items[i].rate <= maxRate) {
                printf("%s\t%s\t\t%.2f\t%d\n", items[i].code, items[i].name, items[i].rate, items[i].quantity);
            }
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}

void deleteItem() {
    char searchCode[10];
    int found = 0;
    int i,j;

    printf("\n\tEnter item code to delete: ");
    scanf("%s", searchCode);

    for (i = 0; i < itemCount; i++) {
        if (strcmp(items[i].code, searchCode) == 0) {
            for (j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            found = 1;
            printf("\n\tItem deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\n\tItem not found.\n");
    }
    getchar(); // Consume newline character
    printf("Press Enter to continue...");
    getchar();
}

void calculateBill() {
    char itemCode[10];
    int quantity,i;
    float total = 0;

    printf("\n\tCalculate Bill:\n");
    while (1) {
        printf("\n\tEnter item code (or 'end' to finish): ");
        scanf("%s", itemCode);
        if (strcmp(itemCode, "end") == 0) {
            break;
        }

        printf("\n\tEnter quantity: ");
        scanf("%d", &quantity);

        for (i = 0; i < itemCount; i++) {
            if (strcmp(items[i].code, itemCode) == 0) {
                total += items[i].rate * quantity;
                items[i].quantity -= quantity;
                break;
            }
        }
    }

    printf("\n\tTotal bill: %.2f\n", total);
    getchar(); // Consume newline character
    printf("Press Enter to continue...");
    getchar();
}

void clearScreen() {
    system("clear || cls");
}

void printMenu() {
	//printf("\033[42m" ANSI_COLOR_WHITE_TEXT);

	printf("\n\n");
    printf("\t   ++==================================================++\n");
    printf("\t   ||                     MENU                         ||\n");
    printf("\t   ++==================================================++\n");
    printf("\t   ||                                                  ||\n");
    printf("\t   ||          DEPARTMENTAL STORE MANAGEMENT           ||\n");
    printf("\t   ||                                                  ||\n");
    printf("\t   ++==================================================++\n");
    printf("\t   ||   1. Add Item                                    ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   2. Edit Item                                   ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   3. Display All Items                           ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   4. Search Items                                ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   5. Delete Item                                 ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   6. Calculate Bill                              ||\n");
    printf("\t   |+--------------------------------------------------+|\n");
    printf("\t   ||   7. Exit                                        ||\n");
    printf("\t   ++==================================================++\n");
    //printf(ANSI_COLOR_RESET);


}
