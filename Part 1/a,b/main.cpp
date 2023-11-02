
#include <iostream>
#include "range.h"
#include "factorial.h"
using namespace std;

int main() {
    // Testing part 1
    int start = 1;
    int end = 10;
    int sum = sum_range(start, end);
    cout << "Sum from " << start << " to " << end << " is " << sum << endl;

    // Testing part 2
    cout << "Enter a number whose factorial you want to calculate: ";
    int n;
    cin >> n;
    double result = factorial(n);
    cout << "Factorial of " << n << " is " << result << endl;

    return 0;
}
