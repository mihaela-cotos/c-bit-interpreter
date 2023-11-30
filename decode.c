#include <stdio.h>
#include <stdlib.h>
#define SIZE 32
#define OFFSET_N 3
#define OFFSET_OP 4
#define OFFSET_DIM 4


int main() {
    // read the instruction from input
    unsigned int instruct = 0;
    int check_scan = scanf("%u", &instruct);

    if (check_scan > 1) {
        printf("Reading instruction failed\n");
        exit(0);
    }

    // init instruction parameters
    int N = 1;
    int Dim = 1;
    int power = 1;


    // determine first 3 bits
    for (int i = SIZE - OFFSET_N; i < SIZE; i++) {
        if ((1 << i) & instruct) {
            N = N + power;
        }
        power = power * 2;
    }

    printf("Number of instructions to be executed : %d\n", N);

    int operands = N * 2;
    char operators[N + 1];
    operators[N] = '\0';
    int a = 0, b = 0, c = 0;

    for (int i = SIZE - OFFSET_OP; i > SIZE - OFFSET_OP - operands; i = i - 2) {
        if (instruct & (1 << i)) {
            a = 1;
        } else {
            a = 0;
        }

        if (instruct & (1 << (i - 1))) {
            b = 1;
        } else {
            b = 0;
        }

        // determine operators
        if (a == 0 && b == 0) {
            operators[c] = '+';
        } else if (a == 0 && b == 1) {
            operators[c] = '-';
        } else if (a == 1 && b == 0) {
            operators[c] = '*';
        } else {
            operators[c] = '/';
        }
        c++;
    }

    printf("Decoded operators :\n");
    for (int i = 0; i < N; i++) {
        printf("%c ", operators[i]);
    }
    printf("\n");

    power = 1;
    for (int i = 1; i < OFFSET_DIM; i++) {
        power = power * 2;
    }

    int sizeDim = SIZE - OFFSET_OP - operands - OFFSET_DIM;
    for (int i = SIZE - OFFSET_OP - operands; i > sizeDim; i--) {
        if ((1 << i) & instruct) {
            Dim = Dim + power;
        }
        power = power / 2;
    }

    printf("Operand dimension : %d\n", Dim);


    return 0;
}
