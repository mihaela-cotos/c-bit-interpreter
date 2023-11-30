#include <stdio.h>
#include <stdlib.h>
#define SIZE 32
#define OFFSET_N 3
#define OFFSET_OP 4
#define OFFSET_DIM 4
#define SIZE_SHORT 16

// evaluation of * and / (first operation)
void MultAndDiv(int *size, int *N, char *operators, int *num) {
    for (int i = 0; i < *size; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            if (operators[i] == '*') {
                num[i] = num[i] * num[i+1];
            } else {
                num[i] = num[i] / num[i+1];
            }

            // deleting the number from position i + 1
            for (int j = i + 1; j < *N - 1; j++) {
                num[j] = num[j+1];
            }
            *N = *N - 1;

            // deleting the operator from current position
            for (int k = i; k < *size - 1; k++) {
                operators[k] = operators[k+1];
            }
            *size = *size -1;
            i--;
        }
    }
}

// evaluation of + and - (last operation)
void AddAndSubs(int size, int *result, char *operators, int *num) {
    for (int i = 0; i < size; i++) {
        if (operators[i] == '+') {
            *result += num[i+1];
        } else if (operators[i] == '-') {
            *result -= num[i+1];
        }
    }
}


int main() {
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
        // det the operators
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
    if (((N+1) * Dim) % SIZE_SHORT != 0) {
        num = ((N+1) * Dim) / SIZE_SHORT + 1;
    } else {
        num = ((N+1) * Dim) / SIZE_SHORT;
    }

    printf("Numbers to be introduced : %d\n", num);
    unsigned short number[num];
    for (int i = 0; i < num; i++) {
        printf("Give a number : ");
        scanf("%hu", &number[i]);
    }

    int *operand = (int*) calloc(N + 1, sizeof(int));
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

    // size of operators array
    int sizeop = N + 1;

    // size of operands array
    int sizenum = sizeop + 1;

    // evaluating *, /
    MultAndDiv(&sizeop, &sizenum, operators, operand);

    result = operand[0];
    // evaluating +, -
    AddAndSubs(sizenum, &result, operators, operand);

    printf("\nResult : %d\n", result);

    free(operand);
    return 0;
}
