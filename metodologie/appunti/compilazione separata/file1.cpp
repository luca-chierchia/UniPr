#include <iostream>

// file1.cpp
const int magic_num = 42;
static double d = 2.33;
extern const char c2 = 'c';
extern char c;
int b = 2;
int x = 1;     
int f(){return 6;};

int global_counter = 0;
static int internal_counter = 0;

void incrementGlobalCounter(){
  ++global_counter;
}

void incrementInternalCounter(){
  ++internal_counter;
}

int castTheMagic(){
  return magic_num;
}

void printFileState(){
  std::cout << "[file1] global_counter = " << global_counter << "\n"
            << "internal_counter = " << internal_counter << std::endl;
}
