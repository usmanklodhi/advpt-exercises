#pragma once

#include <iostream>
#include <cmath>

double factorial(int n) {
    if (n < 0) {
        std::cout << "Factorial of negative numbers is undefined." << std::endl;
        return NAN;
    }
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
