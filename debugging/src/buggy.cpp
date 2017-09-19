/* Exercise about GDB
 * Use break points and print variables
 * Show some modern c++ behind the scenes
 * g++ -o buggy buggy.cpp -gstabs -g -std=c++14
 */

#include "inttypes.h"
#include <iostream>

class Student {
  public:
    Student (uint64_t ID,const std::string& name ):
     m_ID(ID),
     m_name(name){};
   uint64_t getID(){return m_ID;};
   const char* getName(){return m_name.c_str();};
  private:
  uint64_t m_ID;
  std::string m_name;
};

Student* getStudent(){
  Student* myStudent = new Student(10801983,"Mary Wright");
// ***** OPS!
  return myStudent;  
}

void printStudent(Student* myStudent){
  std::cout << "-- Student's Data --\n";
  std::cout << "Student's ID is " << myStudent->getName()
            << " and name is " << myStudent->getID() << std::endl;
}

int main(){
  Student* myStudent = getStudent();
  printStudent(myStudent);
//  return 1;
}
