/*
 * rvalueReference.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <algorithm>
#include <iostream>
#include <string>

struct MyData{};

std::string function( MyData & ) {
    return "lvalue reference";
}

std::string function( MyData && ) {
    return "rvalue reference";
}

int main(){
  std::cout << std::endl;
  MyData myD;

  std::cout << "function(myD): " << function(myD) << std::endl;
  std::cout << "function(MyData()): " << function(MyData()) << std::endl;
  std::cout << "function(std::move(myD)): " << function(std::move(myD)) << std::endl;

  std::cout << std::endl;

}
