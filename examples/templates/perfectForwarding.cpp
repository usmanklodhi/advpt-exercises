/*
 * perfectForwarding.cpp
 *
 *  Created on: 21.05.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <algorithm>
#include <string>
#include <vector>

class BigData1{
  public:
    BigData1(std::vector<int> data):data(data){}
  private:
    std::vector<int> data;
};


class BigData2{
  public:
    BigData2(std::vector<int>& data):data(data){}
    BigData2(std::vector<int>&& data):data(std::move(data)){}
  private:
    std::vector<int> data;
};

class BigData3{
  public:
    BigData3(std::vector<int>& data,std::string& str):data(data),str(str){}
    BigData3(std::vector<int>& data,std::string&& str):data(data),str(std::move(str)){}
    BigData3(std::vector<int>&& data,std::string& str):data(std::move(data)),str(str){}
    BigData3(std::vector<int>&& data,std::string&& str):data(std::move(data)),str(std::move(str)){}
  private:
    std::vector<int> data;
    std::string str;
};


class BigDataNew{
  public:
    template<typename T1, typename T2>
    BigDataNew(T1&& vec,T2&& s):data(std::forward<T1>(vec)),str(std::forward<T2>(s)){}
  private:
    std::vector<int> data;
    std::string str;
};

int main(){

  std::vector<int> myVec{1,2,3,4,5,6,7,8,9};

  // copy
  BigData1 bigData11(myVec);

  // copy
  BigData2 bigData21(myVec);
  // move
  BigData2 bigData22({1,2,3,4,5,6,7,8,9});

  std::string s{"Only for testing purpose."};

  // copy, copy
  BigData3 bigData31(myVec,s);
  // copy, move
  BigData3 bigData32(myVec,{"Only for testing purpose."});
  // move, copy
  BigData3 bigData33({1,2,3,4,5,6,7,8,9},s);
  // move, move
  BigData3 bigData34({1,2,3,4,5,6,7,8,9},{"Only for testing purpose."});


  std::string tempStr{"testing first"};
  std::vector<int>vec{10,20};
  // copy, copy
  BigDataNew bigData41(myVec,s);
  // copy, move
  BigDataNew bigData42(myVec,std::move(tempStr));
  // move, copy
  BigDataNew bigData43(std::move(myVec),s);
  // move, move
  BigDataNew bigData44(std::move(vec),std::move(s));

}
