/*
Code by Rebeca Martinakova/CupOfTea12
@2024
*/
//---LIBRARIES---//
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 9999
#define NAME_MAX_LENGTH 12
#define DOB_MAX_LENGTH 11

typedef struct personData {
    char name[NAME_MAX_LENGTH];
    char surname[NAME_MAX_LENGTH];
    char dob[DOB_MAX_LENGTH];
    int balance;
    struct personData* next;
} PersonDATA;

unsigned long hash(char* key1, char* key2, char* key3);
int strToNum(char* str);
void insert(PersonDATA* hash_map[], int * firstOutput);
void search(PersonDATA* hash_map[], int * firstOutput);
void update(PersonDATA* hash_map[], int * firstOutput);
void delete(PersonDATA* hash_map[], int * firstOutput);
int customStrCmp(const char* str1, const char* str2);
void customStrCpy(char* dest, const char* src);

unsigned long hash(char* key1, char* key2, char* key3) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key1++)) hash = ((hash << 5) + hash) + c;
    while ((c = *key2++)) hash = ((hash << 5) + hash) + c;
    while ((c = *key3++)) hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

int strToNum(char* str) {
    int result = 0, sign = 1;
    if (*str == '-') {
        sign = -1;
        ++str;
    }
    for (int decimal = 0; *str; str++) {
        if (*str == ',') continue;
        result = result * 10 + (*str - '0');
    }
    return result * sign;
}

void insert(PersonDATA* hash_map[], int *firstOutput) {
    char name[NAME_MAX_LENGTH], surname[NAME_MAX_LENGTH], dob[DOB_MAX_LENGTH], temp[15];
    if (scanf("%s %s %s %s", name, surname, dob, temp) != 4) {
        if (*firstOutput != 1) {
            printf("\n");
        } else *firstOutput = 0;
        printf("insert failed");
        return;
    }
    int index = hash(name, surname, dob);
    for (PersonDATA* ptr = hash_map[index]; ptr; ptr = ptr->next) {
        if (!customStrCmp(ptr->name, name) && !customStrCmp(ptr->surname, surname) && !customStrCmp(ptr->dob, dob)) {
            if (*firstOutput != 1) {
                printf("\n");
            } else *firstOutput = 0;
            printf("insert failed");
            return;
        }
    }
    PersonDATA* new_node = malloc(sizeof(PersonDATA));
    customStrCpy(new_node->name, name);
    customStrCpy(new_node->surname, surname);
    customStrCpy(new_node->dob, dob);
    new_node->balance = strToNum(temp);
    new_node->next = hash_map[index];
    hash_map[index] = new_node;
}

void search(PersonDATA* hash_map[], int *firstOutput) {
    char name[NAME_MAX_LENGTH], surname[NAME_MAX_LENGTH], dob[DOB_MAX_LENGTH];
    if (scanf("%s %s %s", name, surname, dob) != 3) {
        if(*firstOutput != 1){
            printf("\n");
        } else *firstOutput = 0;
        printf("search failed");
        return;
    }
    int index = hash(name, surname, dob);
    int found = 0; // Flag to check if record is found
    for (PersonDATA* ptr = hash_map[index]; ptr; ptr = ptr->next) {
        if (!customStrCmp(ptr->name, name) && !customStrCmp(ptr->surname, surname) && !customStrCmp(ptr->dob, dob)) {
            found = 1; // Record found
            if(*firstOutput != 1) {
                printf("\n");
            } else *firstOutput = 0;
            printf("%d,%02d", ptr->balance / 100, ptr->balance % 100);
            break; // Exit loop after printing the result
        }
    }
    if (!found) { // If record not found
        if(*firstOutput != 1) {
            printf("\n");
        } else *firstOutput = 0;
        printf("search failed");
    }
}

void update(PersonDATA* hash_map[], int *firstOutput) {
    char name[NAME_MAX_LENGTH], surname[NAME_MAX_LENGTH], dob[DOB_MAX_LENGTH], temp[15];
    if (scanf("%s %s %s %s", name, surname, dob, temp) != 4) {
        if (*firstOutput != 1) {
            printf("\n");
        } else *firstOutput = 0; 
        printf("update failed");
        return;
    }
    int index = hash(name, surname, dob);
    int amount = strToNum(temp);
    for (PersonDATA* ptr = hash_map[index]; ptr; ptr = ptr->next) {
        if (!customStrCmp(ptr->name, name) && !customStrCmp(ptr->surname, surname) && !customStrCmp(ptr->dob, dob)) {
            if (ptr->balance + amount < 0) {
                if (*firstOutput != 1) {
                    printf("\n");
                } else *firstOutput = 0;
                printf("update failed");
                return;
            }
            ptr->balance += amount;
            return;
        }
    }
    if (*firstOutput != 1) {
        printf("\n");
    } else *firstOutput = 0;
    printf("update failed");
}


void delete(PersonDATA* hash_map[], int * firstOutput) {
    char name[NAME_MAX_LENGTH], surname[NAME_MAX_LENGTH], dob[DOB_MAX_LENGTH];
    if (scanf("%s %s %s", name, surname, dob) != 3) {
        if (*firstOutput != 1) {
            printf("\n");
        } else *firstOutput = 0;
        printf("delete failed");
        return;
    }
    int index = hash(name, surname, dob);
    PersonDATA **ptr = &hash_map[index], *temp;
    while (*ptr) {
        if (!customStrCmp((*ptr)->name, name) && !customStrCmp((*ptr)->surname, surname) && !customStrCmp((*ptr)->dob, dob)) {
            temp = *ptr;
            *ptr = (*ptr)->next;
            free(temp);
            return;
        }
        ptr = &(*ptr)->next;
    }
    if (*firstOutput != 1) {
            printf("\n");
        } else *firstOutput = 0;
    printf("delete failed");
}

int customStrCmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

void customStrCpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int main() {
    PersonDATA* hash_map[TABLE_SIZE] = {0};
    char operation;
    int firstOutput = 1;  // Flag to control the first line output
    while (scanf(" %c", &operation) != EOF) {
        switch (operation) {
            case 'i': insert(hash_map, &firstOutput); break;
            case 's': search(hash_map, &firstOutput); break;
            case 'u': update(hash_map, &firstOutput); break;
            case 'd': delete(hash_map, &firstOutput); break;
            default: break;
        }
    }
    return 0;
}
