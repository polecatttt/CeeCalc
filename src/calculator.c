#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calculator.h"
#include "math_utils.h"

#define MAX_TOKENS 4

static const char oneArgOps[3][10] = {
    "sin",
    "cos",
    "tan",
};

static const char twoArgOps[4][10] = {
    "add",
    "sub",
    "mul",
    "div",
};

static const int oneArgSize = sizeof(oneArgOps) / sizeof(oneArgOps[0]);
static const int twoArgSize = sizeof(twoArgOps) / sizeof(twoArgOps[0]);


static opType getOpType(const char *oper, int verbose) {
    for (int i=0; i < oneArgSize; i+=1) {
        if (strcmp(oper, oneArgOps[i]) == 0) {
            if (verbose) printf("Expected type 1\n");
            return ONE_ARG;
    }
}

    for (int i=0; i < twoArgSize; i+=1) {
        if (strcmp(oper, twoArgOps[i]) == 0) {
            if (verbose) printf("Expected type 2\n");
            return TWO_ARG;
        }
    }

    return INVALID;
}


opType parseExpr(char *inp, char **op, long double *args, int *nArgs, int verbose) {
    char *tokensArr[MAX_TOKENS];
    int nTokens = 0;

    char *token = strtok(inp, " ");
    while (token && nTokens < MAX_TOKENS) {
        tokensArr[nTokens] = token;
        if (verbose) printf("Token %d = %s\n", nTokens, tokensArr[nTokens]);
        nTokens+=1;
        token = strtok(NULL, " ");
    }

    *op = tokensArr[0];
    opType type = getOpType(*op, verbose);
    *nArgs = (type == ONE_ARG) ? 1 : (type = TWO_ARG) ? 2 : 0;

    if ((type == ONE_ARG && nTokens != 2) || (type == TWO_ARG && nTokens != 3)) {
        return INVALID;
    }

    char *end;
    for (int i=0; i < *nArgs; i+=1) {
        args[i] = strtold(tokensArr[i+1], &end);
        if (end == tokensArr[i] || *end != '\0') return INVALID;
    }

    return type;

}

Result compute(const char *oper, long double *args, int nArgs) {

    // 1 arg
    if (strcmp(oper, "add") == 0) { return add(args[0], args[1] ); }
    else if (strcmp(oper, "sub") == 0) { return sub(args[0], args[1] ); }
    else if (strcmp(oper, "mul") == 0) { return multiply(args[0], args[1] ); }
    else if (strcmp(oper, "div") == 0) { return divide(args[0], args[1] ); }

    // 2 arg
    else if (strcmp(oper, "sin") == 0) { return sine(args[0]); }
    else if (strcmp(oper, "cos") == 0) { return cosine(args[0]); }
    else if (strcmp(oper, "tan") == 0) { return tangent(args[0]); }

    // default
    return (Result){.code = 0, .msg = "Unknown Operator", .value = 0};
    
}