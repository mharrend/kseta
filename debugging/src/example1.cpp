/*
g++ -o example1 -std=c++14 -fgnu-tm -pthread -g -Wall -Wextra -Wpedantic -Werror example1.cpp
*/
#include <iostream>
#include <thread>

void incrementCounter(int* counter, const unsigned int times){
  for (unsigned int i=0; i<times;++i){
    __transaction_atomic{
    	++(*counter);
    }
  }
}

int main(){
  int counter(0);
  // launch two threads to increment the counter
  std::thread increment1(incrementCounter,&counter,100000);
  std::thread increment2(incrementCounter,&counter,100000);
  increment1.join();
  increment2.join();
  std::cout << "Expected value:   200000" << std::endl;
  std::cout << "Calculated value: " << counter << std::endl;
  return 0;
}
