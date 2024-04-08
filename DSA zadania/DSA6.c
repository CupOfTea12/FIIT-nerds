/*
Code by Rebeca Martinakova/CupOfTea12
@2024
*/
//---LIBRARIES---//
#include <stdio.h>
#include <stdlib.h>

// Global variable for counter
int counter = 0;
//Global variable for temporary memory
char temp[15];
char name[12];
char surname[12];
char dob[11];
int bal, decimal,separator,negative;

#define TABLE_SIZE 9999

// Struct representing a node in the hash map
typedef struct node {
    char name[12];
    char surname[12];
    char dob[11];
    int balance;
    struct node* next;
} Node;

// Function prototypes
int hash(char* key1, char* key2, char* key3);
int strToNum(char* balance);
int customStrCmp(char* str1, char* str2);
int insert(Node* hash_map[]);
int search(Node* hash_map[]);
int update(Node* hash_map[]);
int delete(Node* hash_map[]);

// Function to compute the hash value for keys
int hash(char* key1, char* key2, char* key3) {
    int hash = 0;
    counter = 0;
    while (key1[counter] != '\0') {
        hash = 33 * hash + key1[counter++];
    }
    counter = 0;
    while (key2[counter] != '\0') {
        hash = 33 * hash + key2[counter++];
    }
    counter = 0;
    while (key3[counter] != '\0') {
        hash = 33 * hash + key3[counter++];
    }
    return abs(hash) % TABLE_SIZE;
}

// Function to convert balance from string to integer
int strToNum(char* balance) {
     bal = 0;
     decimal = 2;
     separator = 0;
     negative = 1;
    
    if (balance[0] == '-') {
        negative = -1;
    }
    counter = 0;
    while (balance[counter] != '\0') {
        if (balance[counter] != ',' && balance[counter] != '-') {
            if (separator && decimal > 0) {
                if (decimal == 1 && balance[counter + 1] > '5') {
                    bal = bal * 10 + 1 + (balance[counter] - '0');
                } else {
                    bal = bal * 10 + (balance[counter] - '0');
                }
                decimal--;
            } else if (decimal > 0) {
                bal = bal * 10 + (balance[counter] - '0');
            }
        } else if (balance[counter] == ',') {
            separator = 1;
        }
        counter++;
    }
    return bal * negative;
}

// Function to compare two strings
int customStrCmp(char* str1, char* str2) {
    counter = 0;
    while (str1[counter] != '\0' && str2[counter] != '\0') {
        if (str1[counter] != str2[counter]) {
            return str1[counter] - str2[counter];
        }
        counter++;
    }
    return str1[counter] - str2[counter];
}


// Function to search for the balance associated with a key in the hash map
int search(Node* hash_map[]) {
    char name[12];
    char surname[12];
    char dob[11];
    if (scanf("%s %s %s", name, surname, dob) != 3) {
        return -1;  // Invalid number of parameters
    }
    int index = hash(name, surname, dob);
    Node* current = hash_map[index];
    while (current != NULL) {
        if (customStrCmp(current->name, name) == 0 &&
            customStrCmp(current->surname, surname) == 0 &&
            customStrCmp(current->dob, dob) == 0) {
            return current->balance;  // Return the balance associated with the key
        }
        current = current->next;
    }
    return -1;  // Key not found in the hash map
}

// Function to insert a node into the hash map
int insert(Node* hash_map[]) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (scanf("%s %s %s %s", new_node->name, new_node->surname, new_node->dob, temp) != 4) {
        free(new_node);
        return -1;  // Invalid number of parameters
    }
    int balance_to_int = strToNum(temp);
    new_node->balance = balance_to_int;
    new_node->next = NULL;
    if (balance_to_int < 0) {
        free(new_node);
        return -1;  // Balance cannot be negative
    }
    int index = hash(new_node->name, new_node->surname, new_node->dob);
    if (hash_map[index] == NULL) {
        hash_map[index] = new_node;
    } else {
        Node* current = hash_map[index];
        Node* prev = NULL;
        while (current != NULL) {
            if (customStrCmp(current->name, new_node->name) == 0 &&
                customStrCmp(current->surname, new_node->surname) == 0 &&
                customStrCmp(current->dob, new_node->dob) == 0) {
                free(new_node);
                return -1;  // Key already exists in the hash map
            }
            prev = current;
            current = current->next;
        }
        prev->next = new_node;
    }
    return 0;  // Insertion successful
}

// Function to update the balance associated with a key in the hash map
int update(Node* hash_map[]) {
    name[12];
    surname[12];
    dob[11];
    temp[15];
    if (scanf("%s %s %s %s", name, surname, dob, temp) != 4) {
        return -1;  // Invalid number of parameters
    }
    int update_amount = strToNum(temp);
    int index = hash(name, surname, dob);
    Node* current = hash_map[index];
    while (current != NULL) {
        if (customStrCmp(current->name, name) == 0 &&
            customStrCmp(current->surname, surname) == 0 &&
            customStrCmp(current->dob, dob) == 0) {
            if (update_amount < 0 && ((update_amount < 0) ? update_amount * -1 : update_amount) > current->balance) {
                return -1;  // Balance cannot be negative
            }
            current->balance += update_amount;
            return 0;  // Update successful
        }
        current = current->next;
    }
    return -1;  // Key not found in the hash map
}

// Function to delete a node from the hash map
int delete(Node* hash_map[]) {
    name[12];
    surname[12];
    dob[11];
    if (scanf("%s %s %s", name, surname, dob) != 3) {
        return -1; // Invalid number of parameters
    }
    int index = hash(name, surname, dob);
    Node* current = hash_map[index];
    Node* prev = NULL;
    while (current != NULL) {
        if (customStrCmp(current->name, name) == 0 &&
            customStrCmp(current->surname, surname) == 0 &&
            customStrCmp(current->dob, dob) == 0) {
            if (prev == NULL) {
                hash_map[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return 0;  // Deletion successful
        }
        prev = current;
        current = current->next;
    }
    return -1;  // Key not found in the hash map
}

//---MAIN---//
int main(void) {
    char operator = getchar();
    int first = 1;
    Node* hash_map[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_map[i] = NULL;
    }
    while (operator != EOF) {
        int srch_result;
        switch (operator) {
            case 'i':
                // Insert into hash
                if (insert(hash_map) == -1) {
                    if (!first) {
                        printf("\n");
                    }
                    printf("insert failed");
                    first = 0;
                }
                break;

            case 's':
                // Search in hash
                srch_result = search(hash_map);
                if (!first) {
                    printf("\n");
                }
                if (srch_result == -1) {
                    printf("search failed");
                } else {
                    printf("%d,%02d", srch_result / 100, srch_result % 100);
                    first = 0;
                }
                break;

            case 'u':
                // Update hash
                if (update(hash_map) == -1) {
                    if (!first) {
                        printf("\n");
                    }
                    printf("update failed");
                    first = 0;
                }
                break;

            case 'd':
                // Delete from hash
                if (delete(hash_map) == -1) {
                    if (!first) {
                        printf("\n");
                    }
                    printf("delete failed");
                    first = 0;
                }
                break;
        }
        operator = getchar();
    }
    return 0;
}