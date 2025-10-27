#include <stdio.h>
#include <math.h>
#include "math_utils.h"

calcResult add(long double a, long double b) {
    return (calcResult){.code=1, .msg=NULL, .value=a+b};
}

calcResult sub(long double a, long double b) {
    return (calcResult){.code=1, .msg=NULL, .value=a-b};
}

calcResult multiply(long double a, long double b) {
    return (calcResult){.code=1, .msg=NULL, .value=a*b};
}

calcResult divide(long double a, long double b) {
    if (b == 0.0L) {
        return (calcResult){.code=0, .msg="Division by Zero", .value=0};
    }

    return (calcResult){.code=1, .msg=NULL, .value=a/b};
}

calcResult sine(long double num) {
    return (calcResult){.code=1, .msg=NULL, .value=sinl(num)};
}

calcResult cosine(long double num) {
    return (calcResult){.code=1, .msg=NULL, .value=cosl(num)};
}

calcResult tangent(long double num) {
    return (calcResult){.code=1, .msg=NULL, .value=tanl(num)};
}