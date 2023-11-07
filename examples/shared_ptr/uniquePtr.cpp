/*
 * uniquePtr.cpp
 *
 *  Created on: 13.07.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <iomanip>
#include <iostream>
#include <memory>

struct MyStruct{
  MyStruct(int v):val(v){
    std::cout << std::setw(10) << std::left << (void*) this << " Hello: " << val << std::endl;
  }
  ~MyStruct(){
    std::cout << std::setw(10) << std::left << (void*)this << " Good Bye: " << val << std::endl;
  }
  int val;
};

int main(){

  std::cout << std::endl;

  { // begin of scope

  // Initialize with resource
  std::unique_ptr<MyStruct> uniquePtr0{new MyStruct(0)};

  // use an std::auto_ptr
  std::auto_ptr<MyStruct> autoPtr{new MyStruct(1)};
  std::unique_ptr<MyStruct> uniquePtr1{std::move(autoPtr)};

  // Default Constructor
  std::unique_ptr<MyStruct> uniquePtr2;

  // Move Constructor
  std::unique_ptr<MyStruct> uniquePtr4{new MyStruct(2)};
  std::unique_ptr<MyStruct> uniquePtr5{std::move(uniquePtr4)};

  // Move Assignment
  std::unique_ptr<MyStruct> uniquePtr6{new MyStruct(3)};
  std::unique_ptr<MyStruct> uniquePtr7= std::move(uniquePtr6);

  // access the resource
  std::cout << std::endl;
  std::cout << "Address of resource of uniquePtr7" << (void*)uniquePtr7.get() << " " << std::endl;
  std::cout << "Get val: uniquePtr7.get()->val: " <<uniquePtr7.get()->val << std::endl;
  std::cout << "Get val: uniquePtr7->val: " <<  uniquePtr7->val << std::endl;
  std::cout << std::endl;

  // release the resource
  MyStruct* myStruct= uniquePtr7.release();
  std::cout << "myStruct->val: " << myStruct->val << std::endl;
  delete myStruct;

  std::cout << std::endl;

  // reset the resource
  uniquePtr2.reset(new MyStruct(4));
  std::unique_ptr<MyStruct> uniquePtr8{new MyStruct(5)};
  uniquePtr8.reset(new MyStruct(6));

  std::cout << std::endl;

  // swap the std::unique_ptr
  uniquePtr2.swap(uniquePtr1);
  std::swap(uniquePtr2,uniquePtr1);

  } // end of scope

  std::cout << std::endl;

}
