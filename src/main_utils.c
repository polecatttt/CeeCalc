#include <stdio.h>
#include "main_utils.h"

void flushBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void help(void) {
    printf("== C Calculator %s ==\n\n", VERSION);
    printf("Add - add <num1> <num2>\n");
    printf("Subtract - sub <num1> <num2>\n");
    printf("Multiply - mul <num1> <num2>\n");
    printf("Divide - div <num1> <num2>\n");
    printf("Sine - sin <num>\n");
    printf("Cosine - cos <num>\n");
    printf("Tangent - tan <num>\n");
    printf("q - quit - but why tho :(\n\n");
    printf("== Flags ==\n");
    printf("Verbose (-v) prints extra output for debugging\n");
}