#include <iostream>

// clang++ -g -std=c++17 ./main.cpp -o ./main

void test(void* out,int n) {
  float* cur = (float* )out;
  for (int i = 0;i<5;i++) {
    *cur++ = 0.1f;
    *cur++ = 0.2f;
    cur++ = 0.1f;
  }
}

int main() {
  float* pf = new float[10];
  test(pf,5);
  for (int i=0;i<5;i++) {
    std::cout << pf[i] << ' ' << std::endl;
  }
  delete [] pf;
}
