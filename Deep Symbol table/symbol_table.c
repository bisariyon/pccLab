// gcc -o symbol_table symbol_table.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define FILENAME "symbol.txt" // Filename to store symbols

// Symbol structure to hold information about each symbol
typedef struct Symbol {
    char *name;         // Symbol name (e.g., variable name)
    char *type;         // Type of the symbol (e.g., int, float)
    struct Symbol *next; // Pointer to the next symbol in the chain
} Symbol;

// Hash table structure
typedef struct SymbolTable {
    Symbol **table; // Array of pointers to Symbol
} SymbolTable;

// Hash function to compute hash value for a symbol name
unsigned int hash(const char *name) {
    unsigned int hashValue = 0;
    while (*name) {
        hashValue = (hashValue << 5) + *name++;
    }
    return hashValue % TABLE_SIZE;
}

// Create a new symbol
Symbol* createSymbol(const char *name, const char *type) {
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name); // Duplicate the name
    newSymbol->type = strdup(type); // Duplicate the type
    newSymbol->next = NULL;          // Initialize next to NULL
    return newSymbol;
}

// Create a new symbol table
SymbolTable* createSymbolTable() {
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    table->table = (Symbol **)malloc(sizeof(Symbol *) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL; // Initialize all entries to NULL
    }
    return table;
}

// Insert a symbol into the symbol table
void insert(SymbolTable *table, const char *name, const char *type) {
    unsigned int index = hash(name);
    Symbol *newSymbol = createSymbol(name, type);
    newSymbol->next = table->table[index]; // Insert at the beginning of the chain
    table->table[index] = newSymbol;
}

// Lookup a symbol in the symbol table
Symbol* lookup(SymbolTable *table, const char *name) {
    unsigned int index = hash(name);
    Symbol *current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Symbol found
        }
        current = current->next; // Move to the next symbol in the chain
    }
    return NULL; // Symbol not found
}

// Free the symbol table
void freeSymbolTable(SymbolTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = table->table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name);
            free(temp->type);
            free(temp);
        }
    }
    free(table->table);
    free(table);
}

// Save symbols to a file
void saveSymbols(SymbolTable *table) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Unable to open file for writing");
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = table->table[i];
        while (current != NULL) {
            fprintf(file, "%s %s\n", current->name, current->type);
            current = current->next;
        }
    }
    fclose(file);
}

// Load symbols from a file
void loadSymbols(SymbolTable *table) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Unable to open file for reading");
        return;
    }
    char name[50];
    char type[50];
    while (fscanf(file, "%s %s", name, type) != EOF) {
        insert(table, name, type);
    }
    fclose(file);
}

// Main function to demonstrate the symbol table with user input
int main() {
    SymbolTable *table = createSymbolTable();

    // Load symbols from file if it exists
    loadSymbols(table);

    char name[50];
    char type[50];
    char searchName[50];
    int choice;

    while (1) {
        printf("\n1. Insert symbol\n2. Lookup symbol\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert symbol
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter symbol type: ");
                scanf("%s", type);
                insert(table, name, type);
                printf("Symbol '%s' of type '%s' inserted.\n", name, type);
                break;

            case 2:
                // Lookup symbol
                printf("Enter symbol name to search: ");
                scanf("%s", searchName);
                Symbol *symbol = lookup(table, searchName);
                if (symbol) {
                    printf("Found: %s of type %s\n", symbol->name, symbol->type);
                } else {
                    printf("Symbol not found.\n");
                }
                break;

            case 3:
                // Save symbols to file and exit
                saveSymbols(table);
                freeSymbolTable(table);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
