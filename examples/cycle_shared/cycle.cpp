/*
 * cycle.cpp
 *
 *  Created on: 16.07.2011
 *      Author: Rainer Grimm
 *      Book  : C++0x
 */
#include <iostream>
#include <memory>

class Node{
public:
  Node(const std::string& n):name(n){}

  ~Node(){
    std::cout << "destructor invoked" << std::endl;
  }

  void setNext( std::shared_ptr<Node>n ){
    next= n;
  }

  std::string getName() const { return name; }

  void getCycle() const{
     std::cout << "this" << std::endl;
     std::cout << "     (" << getName() << ":" << (void*)this << ")" << std::endl;
     std::cout << "this->next" << std::endl;
     std::cout << "     (" << next->getName() << ":" << (void*)next.get() << ")" << std::endl;
     std::cout << "this->next->next" << std::endl;
     std::cout << "     (" << next->next->getName() << ":" << (void*)next->next.get() << ")" << std::endl;
  }

private:
  std::string name;
  std::shared_ptr<Node> next;
};



int main(){

  std::cout << std::endl;

  {

    // create the Nodes and give them names
    Node* head= new Node("head");
    Node* tail= new Node("tail");
    std::cout << "head->getName(): " << head->getName() << std::endl;
    std::cout << "tail->getName(): " << tail->getName() << std::endl;

    std::cout << std::endl;

    // create the shared pointer
    std::shared_ptr<Node> spForHead(head);
    head->setNext(std::shared_ptr<Node>(tail));

    // close the cycle
    tail->setNext(spForHead);

    // show the cycle
    spForHead->getCycle();

  }

  std::cout << std::endl;

}

