#include "sample.h"

int aThing(int a, int b){
    return (a + b);
}

int aMoreComplicatedThing(int a, int b, bool c) {
    if (c) return b;
    return a;
}