#ifndef RANGE_H
#define RANGE_H

int sum_range(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += i;
    }
    return sum;
}

#endif //RANGE_H