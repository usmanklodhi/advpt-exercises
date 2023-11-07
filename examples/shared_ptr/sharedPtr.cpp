/*
 * sharedPtr.cpp
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
  std::shared_ptr<MyStruct> sharedPtr{new MyStruct(0)};

  // use an std::auto_ptr
  std::auto_ptr<MyStruct> autoPtr{new MyStruct(1)};
  std::shared_ptr<MyStruct> sharedPtr1{std::move(autoPtr)};

  std::unique_ptr<MyStruct> uniquePtr{new MyStruct(2)};
  std::shared_ptr<MyStruct> sharedPtr2{std::move(uniquePtr)};

  // Default Constructor
  std::shared_ptr<MyStruct> sharedPtr3;

  // Move Constructor
  std::unique_ptr<MyStruct> uniquePtr1{new MyStruct(3)};
  std::shared_ptr<MyStruct> sharedPtr4{std::move(uniquePtr1)};

  // Move Assignment
  std::unique_ptr<MyStruct> uniquePtr2{new MyStruct(4)};
  std::shared_ptr<MyStruct> sharedPtr5= std::move(uniquePtr2);

  // test, if unique owner of the resource
  std::cout << std::boolalpha << std::endl;
  std::cout << "sharedPtr5.unique(): "  << sharedPtr5.unique() << std::endl;
  std::cout << std::endl;

  // Copy Constructor form a std::shared_ptr
  std::shared_ptr<MyStruct> sharedPtr6{new MyStruct(5)};
  std::shared_ptr<MyStruct> sharedPtr7{sharedPtr6};

  // Copy Assignment from a std::shared_ptr
  std::shared_ptr<MyStruct> sharedPtr8= sharedPtr6;

  // get the reference count
  std::cout << std::endl;
  std::cout << "sharedPtr8.use_count(): " << sharedPtr8.use_count() << std::endl;

  // access the resource
  std::cout << std::endl;
  std::cout << "Address of resource of sharedPtr8" << (void*)sharedPtr8.get() << " " << std::endl;
  std::cout << "Get val: sharedPtr8.get()->val: " << sharedPtr8.get()->val << std::endl;
  std::cout << "Get val: sharedPtr8->val: " << sharedPtr8->val << std::endl;
  std::cout << std::endl;

  // reset the resource
  sharedPtr8.reset(new MyStruct(8));

  std::cout << std::endl;

  // only sharedPtr8 will be reset
  std::cout << "sharedPtr6.use_count(): " << sharedPtr6.use_count() << std::endl;
  std::cout << "sharedPtr6.get->val: " << sharedPtr6.get()->val << std::endl;
  std::cout << "sharedPtr7.use_count(): " << sharedPtr7.use_count() << std::endl;
  std::cout << "sharedPtr7.get->val:" << sharedPtr7.get()->val << std::endl;

  std::cout << std::endl;
  std::cout << "sharedPtr8.use_count(): " << sharedPtr8.use_count() << std::endl;
  {
    std::shared_ptr<MyStruct> sharedPtr9{sharedPtr8};
    std::shared_ptr<MyStruct> sharedPtr10= sharedPtr9;
    std::cout << "sharedPtr8.use_count(): " << sharedPtr8.use_count() << std::endl;
    sharedPtr10.reset();
    std::cout << "sharedPtr8.use_count(): " << sharedPtr8.use_count() << std::endl;
  }
  std::cout << "sharedPtr8.use_count(): " << sharedPtr8.use_count() << std::endl;
  sharedPtr8.reset();

  std::cout << std::endl;

  // swap the std::shared_ptr
  sharedPtr2.swap(sharedPtr1);
  std::swap(sharedPtr2,sharedPtr1);

  } // end of scope

  std::cout << std::endl;

}
