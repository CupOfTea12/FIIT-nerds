#include <stdio.h>

void primeNumbersFromInterval() {
    unsigned long long int cisloIntervalu1, cisloIntervalu2;
    while (scanf("%llu %llu", &cisloIntervalu1, &cisloIntervalu2) != 2) {
        printf("Nespravny vstup. Zadajte dve cisla oddelene medzerou: ");
        while (getchar() != '\n');
    }

    // Creating an array to store if numbers are prime
    char primes[cisloIntervalu2 + 1];
    for (unsigned long long int i = 0; i <= cisloIntervalu2; ++i) {
        primes[i] = 1; // Mark all as potential primes
    }
    primes[0] = primes[1] = 0; // 0 and 1 are not primes

    // Using Sieve of Eratosthenes to mark non-primes
    for (unsigned long long int p = 2; p * p <= cisloIntervalu2; ++p) {
        if (primes[p] == 1) {
            // Mark multiples of p as non-prime
            for (unsigned long long int i = p * p; i <= cisloIntervalu2; i += p) {
                primes[i] = 0;
            }
        }
    }

    // Printing primes in the given interval
    int printed = 0;
    for (unsigned long long int i = cisloIntervalu1; i <= cisloIntervalu2; ++i) {
        if (primes[i] == 1) {
            if (printed) {
                printf(", ");
            }
            printf("%llu", i);
            printed = 1;
        }
    }
    // If no primes were printed, print a message
    if (!printed) {
        printf("No primes found in the given interval.");
    }
}

int main() {
    primeNumbersFromInterval();
    return 0;
}
