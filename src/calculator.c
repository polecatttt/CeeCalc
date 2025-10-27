#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calculator.h"
#include "math_utils.h"
#include "globals.h"

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


static opType getOpType(const char *oper) {
    for (int i=0; i < oneArgSize; i+=1) {
        if (strcmp(oper, oneArgOps[i]) == 0) {
            if (verbose) printf("Expected one argument\n");
            return ONE_ARG;
    }
}

    for (int i=0; i < twoArgSize; i+=1) {
        if (strcmp(oper, twoArgOps[i]) == 0) {
            if (verbose) printf("Expected two arguments\n");
            return TWO_ARG;
        }
    }

    return INVALID;
}


opResult parseExpr(char *expr, char **oper, long double *args, int *nArgs) {
    char *tokensArr[MAX_TOKENS];
    int nTokens = 0;

    char *token = strtok(expr, " ");
    while (token && nTokens < MAX_TOKENS) {
        tokensArr[nTokens] = token;
        if (verbose) printf("Token %d = %s\n", nTokens, tokensArr[nTokens]);
        nTokens+=1;
        token = strtok(NULL, " ");
    }

    *oper = tokensArr[0];
    opType type = getOpType(*oper);
    *nArgs = (type == ONE_ARG) ? 1 : (type = TWO_ARG) ? 2 : 0;

    if ((type == ONE_ARG && nTokens != 2) || (type == TWO_ARG && nTokens != 3)) {

        char msg[64];
        int expectedArgs = type == ONE_ARG ? 1 : 2;
        snprintf(msg, sizeof(msg), "Operation %s requires %d argument%s",
        *oper, expectedArgs, expectedArgs==1 ? "" : "s");
        return (opResult){.oper=INVALID, .msg=msg};

    }

    char *end;
    for (int i=0; i < *nArgs; i+=1) {
        args[i] = strtold(tokensArr[i+1], &end);
        if (end == tokensArr[i] || *end != '\0') {

            char msg[1000];
            snprintf(msg, sizeof(msg), "Invalid number: %s", tokensArr[i]);
            return (opResult){.oper=INVALID, .msg=msg};

        }
    }

    return (opResult){.oper=type, .msg=NULL};

}

calcResult compute(const char *oper, long double *args) {

    // 2 arg
    if (strcmp(oper, "add") == 0) { return add(args[0], args[1] ); }
    else if (strcmp(oper, "sub") == 0) { return sub(args[0], args[1] ); }
    else if (strcmp(oper, "mul") == 0) { return multiply(args[0], args[1] ); }
    else if (strcmp(oper, "div") == 0) { return divide(args[0], args[1] ); }

    // 1 arg
    else if (strcmp(oper, "sin") == 0) { return sine(args[0]); }
    else if (strcmp(oper, "cos") == 0) { return cosine(args[0]); }
    else if (strcmp(oper, "tan") == 0) { return tangent(args[0]); }

    // default
    return (calcResult){.code = 0, .msg = "Unknown Operator", .value = 0};
    
}