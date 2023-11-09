#include <iostream>
#include "foo.h"

void foo(){
    #ifdef DEBUG
    std::cout<<"Inside foo-fuction"<<std::endl;
    #endif
    std::cout<<"Hello World!"<<std::endl;
    
}

