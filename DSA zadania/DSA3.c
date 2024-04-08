#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_SIZE 20

int compareRational(char *num1, char *num2) {
    while (*num1 == '0' || *num1 == '-') num1++;
    while (*num2 == '0' || *num2 == '-') num2++;

    while (*num1 == *num2 && *num1 != '\0') {
        num1++;
        num2++;
    }

    if (*num1 == '\0' && *num2 == '\0') return 0;
    if (*num1 > *num2) return 1;
    return -1;
}

// Vlastná implementácia funkcie na zistenie dĺžky reťazca
int my_strlen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Vlastná implementácia funkcie na kopírovanie reťazca
void my_strcpy(char *dest, char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main() {
    char **sequence;
    int N, M;

    scanf("%d", &N);
    sequence = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        char num[MAX_NUM_SIZE];
        scanf("%s", num);
        int len = my_strlen(num);
        sequence[i] = (char *)malloc((len + 1) * sizeof(char));
        my_strcpy(sequence[i], num);
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        char num[MAX_NUM_SIZE];
        int found = 0;

        scanf("%s", num);

        for (int j = 0; j < N; j++) {
            if (compareRational(sequence[j], num) == 0) {
                printf("%d\n", j + 1);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("0\n");
    }

    // Uvoľnenie pamäte
    for (int i = 0; i < N; i++) {
        free(sequence[i]);
    }
    free(sequence);

    return 0;
}
