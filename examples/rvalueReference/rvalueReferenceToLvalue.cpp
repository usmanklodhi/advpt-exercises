/*
 * rvalueReferenceToLvalue.cpp
 *
 *  Created on: 21.05.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <algorithm>
#include <iostream>


struct MyData{

  MyData()= default;

  // copy constructor
  MyData(const MyData& m){
    std::cout << "copy constructor MyData"  << std::endl;
  }

  // move constructor
  MyData(MyData&& m){
    std::cout << "move constructor MyData" << std::endl;
  }

};

struct CopyMyData{

  CopyMyData()= default;

  MyData myData;

  // move constructor
  CopyMyData(CopyMyData&& m): myData(m.myData){
    std::cout << "move constructor CopyMyData" << std::endl;
  }

};

struct MoveMyData{

  MoveMyData()= default;

  MyData myData;

  // move constructor
  MoveMyData(MoveMyData&& m): myData(std::move(m.myData)){
    std::cout << "move constructor MoveMyData" << std::endl;
  }

};

void rvalueReferenceToLvalue(MyData&& myData){
  std::cout << "rvalueReferenceToLvalue(MyData&& myData): ";
  MyData myData1(myData);
}

void rvalueReferenceToRvalue(MyData&& myData){
  std::cout << "rvalueReferenceToRvalue(MyData&& myData): ";
  MyData myData1(std::move(myData));
}

int main(){

  std::cout << std::endl;

  rvalueReferenceToLvalue(MyData());
  rvalueReferenceToRvalue(MyData());

  std::cout << std::endl;

  CopyMyData copyMyData;
  CopyMyData c(std::move(copyMyData));

  std::cout << std::endl;

  MoveMyData moveMyData;
  MoveMyData m(std::move(moveMyData));

  std::cout << std::endl;

}
