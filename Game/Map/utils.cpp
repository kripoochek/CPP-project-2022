#include "utils.h"
#include <random>
#include <iostream>

std::mt19937 rnd(time(0));

int randNum(long long a, long long b) {
    return rnd() % (b - a + 1) + a;
}