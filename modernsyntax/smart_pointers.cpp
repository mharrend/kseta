/*
g++ -o smart_pointers -std=c++14 -pthread -g -Wall -Wextra -Wpedantic -Werror smart_pointers.cpp
*/
#include <iostream>
#include <memory>

class IntegerStore1 {
public:
   std::shared_ptr<int> i;

   IntegerStore1():i(new int(0)) { }

   ~IntegerStore1() {
      if(i) {
         i.reset();
      }
   }

   void put(int* newValue) {
      i = std::shared_ptr<int>(newValue);
   }

   std::shared_ptr<int> get() {return i;}

private:
    // we need to explicitly disable value-copying, as it's not safe!
    IntegerStore1(const IntegerStore1&);
    IntegerStore1& operator=(const IntegerStore1&);
};

class IntegerStore2 {
public:
   std::shared_ptr<int> i;

   IntegerStore2():i(new int(0)) { }

   ~IntegerStore2() {
      if(i) {
         i.reset();
      }
   }

   void set(int* newValue) {
      i = std::shared_ptr<int>(newValue);
   }

   std::shared_ptr<int> get() {return i;}


private:
    // we need to explicitly disable value-copying, as it's not safe!
    IntegerStore2(const IntegerStore2&);
    IntegerStore2& operator=(const IntegerStore2&);
};

void useCaseOne(){
  std::cout << "*** useCaseOne *** " << std::endl;
  // This use case contains a memory leak
  IntegerStore1 store;
  auto p_anInteger = new int(3);
  std::cout << "IntegerStore contains " << *(store.get()) << std::endl;
  store.put(p_anInteger);
  std::cout << "IntegerStore contains " << *(store.get()) << std::endl;
  // ops, we didn't delete the created integer
}

void useCaseTwo() {
  std::cout << "*** useCaseTwo *** " << std::endl;
  // This use case will crash
  auto store = new IntegerStore2();
  auto anInteger = int(3);
  std::cout << "IntegerStore contains " << *(store->get()) << std::endl;
  store->set( &anInteger);
  // let's change the value
  anInteger = 5;
  // does the IntegerStore see the changed value?
  std::cout << "IntegerStore contains " << *(store->get()) << std::endl;
//  delete store;
  std::cout << "The integer is " << anInteger << std::endl;
}


int main(){
//  useCaseOne();
  useCaseTwo();

  return 0;
}
