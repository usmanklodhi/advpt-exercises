#include <iostream>
#include "bar.h"


double addition(double a, double b){
#ifdef DEBUG
    std::cout<<"a: "<<a<<"; b: "<<b<<std::endl;
#endif
    return a+b;
}
