#pragma once

int sum_range(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += i;
    }
    return sum;
}