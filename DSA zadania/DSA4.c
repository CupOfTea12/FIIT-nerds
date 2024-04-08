/*
Code by CupOfTea12
2024@ All rights reserved 
*/
//---LIBRARIES---//
#include <stdlib.h>
#include <stdio.h>


//---STRUCT---//
typedef struct {
    char *data;
    int top;
} Zasobnik;

void inicializovat(Zasobnik *s){
    s->top = -1;
    s->data = NULL;
}

void vlozit(Zasobnik *s, char c){
    s->data = realloc(s->data, (s->top + 2) * sizeof(char));
    if (s->data == NULL) {
        printf("nejde.\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = c;
}

char vybrat(Zasobnik *s){
    return s->data[(s->top)--];
}

int jeOtvoreny(char c){
    switch(c) {
        case '(':
        case '[':
        case '{':
        case '<':
            return 1;
        default:
            return 0;
    }
}

int jeZatvoreny(char c){
    switch(c) {
        case ')':
        case ']':
        case '}':
        case '>':
            return 1;
        default:
            return 0;
    }
}

int jePlatnyPar(char otvoreny, char uzavrety) {
    switch(otvoreny) {
        case '(':
            return uzavrety == ')';
        case '[':
            return uzavrety == ']';
        case '{':
            return uzavrety == '}';
        case '<':
            return uzavrety == '>';
        default:
            return 0;
    }
}

//---MAIN---//
int main() {
    int N;
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; i++) {
        Zasobnik s;
        inicializovat(&s);
        char postupnost[10000];
        fgets(postupnost, sizeof(postupnost), stdin);
        int chyby = 0;
        for (int j = 0; postupnost[j] != '\0'; j++) {
            char aktualny = postupnost[j];
            if (jeOtvoreny(aktualny)) {
                vlozit(&s, aktualny);
            } else if (jeZatvoreny(aktualny)) {
                if (s.top == -1) {
                    chyby++;
                } else {
                    char vrch = vybrat(&s);
                    if (!jePlatnyPar(vrch, aktualny)) {
                        chyby++;
                    }
                }
            }
        }
        while (s.top != -1) {
            chyby++;
            vybrat(&s);
        }
        free(s.data);
        if (i == N - 1) {
            printf("%d", chyby);
        } else {
            printf("%d\n", chyby);
        }
    }
    return 0;
}
