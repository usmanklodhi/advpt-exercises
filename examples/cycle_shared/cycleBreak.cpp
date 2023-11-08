/*
 * cycleBreak.cpp
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

  void setWeakNext( std::shared_ptr<Node> n ){
    weak_next= n;
  }

  void setSharedNext( std::shared_ptr<Node> n ){
    shared_next= n;
  }

  std::string getName() const { return name; }

  void getCycle() const{
    std::cout << "this" << std::endl;
    std::cout << "     (" << getName() << ":" << (void*)this << ")" << std::endl;
    std::cout << "this->next" << std::endl;
    std::cout << "     (" << shared_next->getName() << ":" << (void*)shared_next.get() << ")" << std::endl;
    if (std::shared_ptr<Node> next = shared_next->weak_next.lock()) {
      std::cout << "this->next->next" << std::endl;
      std::cout << "     (" << next->getName() << ":" << (void*)next.get() << ")" << std::endl;
    }
  }

private:
  std::string name;
  std::weak_ptr<Node> weak_next;
  std::shared_ptr<Node> shared_next;
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
    head->setSharedNext(std::shared_ptr<Node>(tail));

    // close the cycle
    tail->setWeakNext(spForHead);

    // show the cycle
    spForHead->getCycle();

    std::cout << std::endl;

  }

  std::cout << std::endl;

}

