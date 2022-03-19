#include "utils.h"
#include <random>
#include <iostream>

std::random_device rd;
std::mt19937 gen(rd());

int randNum(int a, int b) {
    std::uniform_int_distribution<> genInt(a, b);
    return genInt(gen);
}