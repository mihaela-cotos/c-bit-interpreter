# c-bit-interpreter

A simple implementation of a bit instruction interpreter, trying to simulate a processor.

## Project Overview

This programme is designed to interpret and decode binary instructions. This project is a **mini-processor** that decodes the given instructions, each provided in a binary format. 

The instructions include information about the number of operations to be executed, the specific operations (+, -, *, or /), and the size of operands.

#### Instruction format
- **Number of Operations (N):** Encoded in 3 bits, representing the count of instructions to be executed. The decimal value is obtained by converting the most significant 3 bits from binary to decimal and adding 1. The maximum number of instructions to be executed is 8.

- **Operation Code (Op):** Encoded in 2 bits, specifying the operation to be performed (+, -, *, or /).

| Code | Operation |
| ---- | --------- |
|  00  |     +     |
|  01  |     -     |
|  10  |     *     |
|  11  |     /     |


- **Operand Size (Dim):** Encoded in 4 bits, indicating the size of operands. Similar to N, the decimal value is obtained by transforming the least significant 4 bits into decimal and adding 1. Operand sizes can range from 1 to 16.


## Build

In order to build this programme you will need the **gcc compiler** installed on your machine.

To begin, clone the project and change the directory into it, then run the make command to build the project :
```
cd c-bit-interpreter
make
```

You will get 3 executables : decode, encode and execute.

Then you can introduce some numbers and see how it will be decoded in operands and operators, resulting in some arithmetic operations.
