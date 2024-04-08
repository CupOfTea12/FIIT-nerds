//---LIBRARIES---//
#include <stdio.h>

//---FUNCTIONS---//
long long unsigned int euklidsMethod(long long unsigned int a, long long unsigned int b) {
    long long unsigned int  temporaryVar;
    while (b != 0) {
        temporaryVar = a % b;
        a = b;
        b = temporaryVar;
    }
    return a;
}

//---MAIN---//
int main() {
    int count, i;
    unsigned long long a, b;
    scanf("%d", &count);

    for (i = 0; i < count; i++) {
        scanf("%llu %llu", &a, &b);
        printf("%llu%s", euklidsMethod(a, b), (i == count - 1) ? "" : "\n");
    }
    return 0;
}
