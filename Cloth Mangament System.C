#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "clothing.dat"
#define MAX_ITEMS 100

typedef struct {
    int id;
    char name[50];
    char category[30];
    char size[10];
    float price;
    int stock;
} Clothing;

Clothing inventory[MAX_ITEMS];
int itemCount = 0;

// Function prototypes
void loadInventory();
void saveInventory();
void addClothing();
void displayClothing();
void updateClothing();
void deleteClothing();
void searchClothing();
void showMenu();

int main() {
    loadInventory();
    showMenu();
    return 0;
}

void loadInventory() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) return;

    itemCount = fread(inventory, sizeof(Clothing), MAX_ITEMS, file);
    fclose(file);
}

void saveInventory() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    
    fwrite(inventory, sizeof(Clothing), itemCount, file);
    fclose(file);
}

void addClothing() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory full!\n");
        return;
    }

    Clothing newItem;
    newItem.id = itemCount + 1;

    printf("\nEnter clothing details:\n");
    printf("Name: "); scanf("%s", newItem.name);
    printf("Category: "); scanf("%s", newItem.category);
    printf("Size: "); scanf("%s", newItem.size);
    printf("Price: "); scanf("%f", &newItem.price);
    printf("Stock: "); scanf("%d", &newItem.stock);

    inventory[itemCount++] = newItem;
    saveInventory();
    printf("Item added successfully!\n");
}

void displayClothing() {
    printf("\n%-5s %-20s %-15s %-10s %-10s %-10s\n", 
           "ID", "Name", "Category", "Size", "Price", "Stock");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < itemCount; i++) {
        printf("%-5d %-20s %-15s %-10s $%-9.2f %-10d\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].category,
               inventory[i].size,
               inventory[i].price,
               inventory[i].stock);
    }
}

void updateClothing() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < itemCount; i++) {
        if(inventory[i].id == id) {
            printf("Enter new details:\n");
            printf("Name: "); scanf("%s", inventory[i].name);
            printf("Category: "); scanf("%s", inventory[i].category);
            printf("Size: "); scanf("%s", inventory[i].size);
            printf("Price: "); scanf("%f", &inventory[i].price);
            printf("Stock: "); scanf("%d", &inventory[i].stock);
            
            saveInventory();
            printf("Item updated!\n");
            return;
        }
    }
    printf("Item not found!\n");
}

void deleteClothing() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < itemCount; i++) {
        if(inventory[i].id == id) {
            for(int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            saveInventory();
            printf("Item deleted!\n");
            return;
        }
    }
    printf("Item not found!\n");
}

void searchClothing() {
    char query[50];
    printf("Enter name to search: ");
    scanf("%s", query);

    printf("\nSearch results:\n");
    printf("%-5s %-20s %-15s %-10s %-10s %-10s\n", 
           "ID", "Name", "Category", "Size", "Price", "Stock");
    
    for(int i = 0; i < itemCount; i++) {
        if(strstr(inventory[i].name, query) != NULL) {
            printf("%-5d %-20s %-15s %-10s $%-9.2f %-10d\n",
                   inventory[i].id,
                   inventory[i].name,
                   inventory[i].category,
                   inventory[i].size,
                   inventory[i].price,
                   inventory[i].stock);
        }
    }
}

void showMenu() {
    int choice;
    do {
        printf("\nClothing Management System\n");
        printf("1. Add New Item\n");
        printf("2. Display All Items\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("5. Search Item\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addClothing();
             break;
            case 2: displayClothing();
             break;
            case 3: updateClothing();
             break;
            case 4: deleteClothing();
             break;
            case 5: searchClothing(); 
            break;
            case 6: printf("Exiting...\n");
             break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 6);
}