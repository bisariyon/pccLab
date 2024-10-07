#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABELS 100
#define MAX_INSTRUCTIONS 100
#define MAX_LABEL_LENGTH 10
#define MAX_OPCODE_LENGTH 10

typedef struct {
    char label[MAX_LABEL_LENGTH];
    int address;
} Label;

typedef struct {
    char opcode[MAX_OPCODE_LENGTH];
    char operand[10];
} Instruction;

Label symbolTable[MAX_LABELS];
int labelCount = 0;
Instruction instructions[MAX_INSTRUCTIONS];
int instructionCount = 0;
int locationCounter = 0;

void addLabel(char *label, int address) {
    strcpy(symbolTable[labelCount].label, label);
    symbolTable[labelCount].address = address;
    labelCount++;
}

int findLabelAddress(char *label) {
    for (int i = 0; i < labelCount; i++) {
        if (strcmp(symbolTable[i].label, label) == 0) {
            return symbolTable[i].address;
        }
    }
    return -1; // Label not found
}

void firstPass(FILE *source) {
    char line[100];
    while (fgets(line, sizeof(line), source)) {
        char *token = strtok(line, " \t\n");
        if (token == NULL) continue;

        // Check if the line is a label
        if (strchr(token, ':')) {
            // Remove the ':' from the label
            token[strcspn(token, ":")] = 0;
            addLabel(token, locationCounter);
            token = strtok(NULL, " \t\n");
        }

        // If there's an opcode, add it to the instruction list
        if (token != NULL) {
            strcpy(instructions[instructionCount].opcode, token);
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                strcpy(instructions[instructionCount].operand, token);
            } else {
                instructions[instructionCount].operand[0] = '\0'; // No operand
            }
            instructionCount++;
            locationCounter += 1; // Increment location counter (modify based on instruction size)
        }
    }
}

void secondPass(FILE *output) {
    for (int i = 0; i < instructionCount; i++) {
        int opcode = 0; // Initialize machine code representation
        // Convert opcode to machine code (this is a simplified example)
        if (strcmp(instructions[i].opcode, "MOV") == 0) {
            opcode = 0x46; // Example opcode for MOV
        } else if (strcmp(instructions[i].opcode, "ADD") == 0) {
            opcode = 0x80; // Example opcode for ADD
        }

        fprintf(output, "%02X", opcode); // Write the opcode to the output file
        if (instructions[i].operand[0] != '\0') {
            int address = findLabelAddress(instructions[i].operand);
            if (address != -1) {
                fprintf(output, " %02X", address); // Write the operand (address) if it's a label
            }
        }
        fprintf(output, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source file> <output file>\n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (!source) {
        perror("Error opening source file");
        return 1;
    }

    firstPass(source);
    fclose(source);

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        return 1;
    }

    secondPass(output);
    fclose(output);

    printf("Assembly completed successfully.\n");
    return 0;
}
