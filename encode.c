#include <stdio.h>
#include <stdlib.h>
#define SIZE 32
#define OFFSET_N 3
#define OFFSET_OP 4
#define OFFSET_DIM 4
#define SIZE_SHORT 16



int main() {
    // read and init instruction
    unsigned int instruct = 0;
    int check_scan = scanf("%u", &instruct);

    if (check_scan > 1) {
        printf("Reading instruction failed\n");
        exit(0);
    }

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

    int nr_operands = N * 2;
    char operators[N + 1];
    operators[N] = '\0';
    int a = 0, b = 0, c = 0;

    for (int i = SIZE - OFFSET_OP; i > SIZE - OFFSET_OP - nr_operands; i = i - 2) {
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

    power = 1;
    for (int i = 1; i < OFFSET_DIM; i++) {
        power = power * 2;
    }

    int sizeDim = SIZE - OFFSET_OP - nr_operands - OFFSET_DIM;
    for (int i = SIZE - OFFSET_OP - nr_operands; i > sizeDim; i--) {
        if ((1 << i) & instruct) {
            Dim = Dim + power;
        }
        power = power / 2;
    }
    int num = 0;

    // determine how many numbers are needed
    if (((N + 1) * Dim) % SIZE_SHORT != 0) {
        num = ((N + 1)*Dim) / SIZE_SHORT + 1;
    } else {
        num = ((N + 1) * Dim) / SIZE_SHORT;
    }

    printf("Numbers to be introduced : %d\n", num);
    unsigned short number[num];

    for (int i = 0; i < num; i++) {
        printf("Give a number : ");
        scanf("%hu", &number[i]);
    }

    int *operand = (int*)calloc(N + 1, sizeof(int));
    int count = 0;
    int temp = 0;

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < SIZE_SHORT / Dim; j++) {
            temp = 0;
            power = 1;
            for (int k = SIZE_SHORT - (j + 1) * Dim;
                k < SIZE_SHORT - (j + 1) * Dim + Dim; k++) {
                if ((1 << k) & number[i]) {
                    temp = temp + power;
                }
                power = power * 2;
            }

            operand[count] = temp;
            count++;

            if (count == (N + 1)) {
                break;
            }
        }
    }

    
    printf("Decoded operands :");

    for (int i = 0; i < N + 1; i++) {
        printf(" %d", operand[i]);
    }


    int result = 0;
    result = operand[0];
    for (int i = 0; i < N + 1; i++) {
        if (operators[i] == '+') {
            result += operand[i+1];
        } else if (operators[i] == '-') {
            result -= operand[i+1];
        } else if (operators[i] == '*') {
            result *= operand[i+1];
        } else if (operators[i] == '/') {
            result /= operand[i+1];
        }
    }

    printf("\nResult : %d\n", result);

    free(operand);
    return 0;
}
