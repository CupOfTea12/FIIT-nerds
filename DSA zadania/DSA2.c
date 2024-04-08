#include <stdio.h>

void primeNumbersFromInterval() {
    unsigned long long int cisloIntervalu1, cisloIntervalu2;
    while (scanf("%llu %llu", &cisloIntervalu1, &cisloIntervalu2) != 2) {
        printf("Nespravny vstup. Zadajte dve cisla oddelene medzerou: ");
        while (getchar() != '\n');
    }

    char prvocisla[cisloIntervalu2 + 1];
    for (unsigned long long int i = 0; i <= cisloIntervalu2; ++i) {
        prvocisla[i] = 1; 
    }
    prvocisla[0] = prvocisla[1] = 0; 

    for (unsigned long long int p = 2; p * p <= cisloIntervalu2; ++p) {
        if (prvocisla[p] == 1) {
            for (unsigned long long int i = p * p; i <= cisloIntervalu2; i += p) {
                prvocisla[i] = 0;
            }
        }
    }

    int vypis = 0;
    for (unsigned long long int i = cisloIntervalu1; i <= cisloIntervalu2; ++i) {
        if (prvocisla[i] == 1) {
            if (vypis) {
                printf(", ");
            }
            printf("%llu", i);
            vypis = 1;
        }
    }
    if (!vypis) {
        printf("V zadanom intervale neboli najdute ziadne prvocisla.");
    }
}

int main() {
    primeNumbersFromInterval();
    return 0;
}
