#include <iostream>
#include <sstream>
#include <string>
#include "foo.h"
#include "bar.h"

int main(){
    foo();
#ifdef DEBUG
    std::cout<<"Debug mode active"<<std::endl;
#endif
    double res = addition(1.3,5.2);
    std::cout<<res<<std::endl;
    return 0;
}

