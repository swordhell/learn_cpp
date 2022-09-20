#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 复杂度分析： 期望复杂度 O(n lg n)  最坏复杂度 O(n^2)
// 数组 A[p.. r] 被划分为两个（可能为空）子数组 A[p.. q-1] A[q+ 1.. r], 使得
// A[p .. l] 中的每一个元素都小于等于 A[q], A[q] 也小于等于 A[q+l..r] 中的每个元素。
// 其中，计算下标 也是划分过程的一部分。

// 这个函数是将 [p,r)之间的数字，分成两半，前面的都小于r位置的数字；
int partition(int *A, int p, int r) {
  int x = A[r]; // 找到末尾的数字
  int i = p - 1;// 将指针指向起始位置前一位
  for (int j = p; j <= r - 1; j++) {// 遍历[p,r)，
    if (A[j] <= x) { // 找到当前位置数字比末尾数字小
      ++i;// 将数组中i++位置数字和j位置交换；
      if (i !=j ){
        std::swap(A[i], A[j]);
      }
    }
  }
  if (i+1 != r) {
    std::swap(A[i + 1], A[r]); // 将最后一个被交换的对象和r位置的交换
  }
  return i + 1;
}

void quick_sort(int *A, int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quick_sort(A, p, q - 1);
    quick_sort(A, q + 1, r);
  }
}

int main(int argn, char *argc[]) {
  srand((unsigned)time(0));
  const int MAX_ARRAY = 10;
  const int NUMBER_RANGE = 500;
  int *A = new int[MAX_ARRAY];
  for (int i = 0; i < MAX_ARRAY; i++) {
    A[i] = rand() % NUMBER_RANGE;
  }
  for (int i = 0; i < MAX_ARRAY; i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl << "--------------" << std::endl;
  quick_sort(A,0,MAX_ARRAY-1);
  for (int i = 0; i < MAX_ARRAY; i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
  delete [] A;
}
