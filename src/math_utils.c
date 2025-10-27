#include <stdio.h>
#include <math.h>
#include "math_utils.h"

Result add(long double a, long double b) {
    return (Result){.code=1, .msg=NULL, .value=a+b};
}

Result sub(long double a, long double b) {
    return (Result){.code=1, .msg=NULL, .value=a-b};
}

Result multiply(long double a, long double b) {
    return (Result){.code=1, .msg=NULL, .value=a*b};
}

Result divide(long double a, long double b) {
    if (b == 0.0L) {
        return (Result){.code=0, .msg="Division by Zero", .value=0};
    }

    return (Result){.code=1, .msg=NULL, .value=a/b};
}

Result sine(long double num) {
    return (Result){.code=1, .msg=NULL, .value=sinl(num)};
}

Result cosine(long double num) {
    return (Result){.code=1, .msg=NULL, .value=cosl(num)};
}

Result tangent(long double num) {
    return (Result){.code=1, .msg=NULL, .value=tanl(num)};
}