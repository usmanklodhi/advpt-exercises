/*
 * sharedPtrDouDelete.cpp
 *
 *  Created on: 14.07.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <iomanip>
#include <iostream>
#include <memory>

struct MyStruct{
  MyStruct(int v):val(new int(v)){
    std::cout << std::setw(10) << std::left << (void*) this << " Hello: " << *val << std::endl;
  }
  ~MyStruct(){
    std::cout << std::setw(10) << std::left << (void*)this << " Good Bye: " << *val << std::endl;
  }
  int* val;
};

int main(){

  std::cout << std::endl;

  std::cout << std::boolalpha;

  MyStruct* myStruct1= new MyStruct(5);
  MyStruct* myStruct2= myStruct1;

  std::shared_ptr<MyStruct> sharedPtr1(myStruct1);
  std::shared_ptr<MyStruct> sharedPtr2(myStruct2);

  std::cout << "sharedPtr1.unique(): " << sharedPtr1.unique() << std::endl;
  std::cout << "sharedPtr2.unique(): " << sharedPtr2.unique() << std::endl;

}
