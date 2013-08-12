// 取前100个最小的值
#include <climits>
#include <iostream>
using namespace std;

// macros
#define NUM 100

// local functions
void make_heap();
void heap_max_heapify(int ix);
void heap_sort_output();

int heap[NUM];
int heapSize = NUM;

int main()
{

  make_heap();
  int number;
  while (cin >> number) {
    if (number < heap[0]) {
      heap[0] = number;
      heap_max_heapify(0);
    }
  }

  //Output Result
  cout << "The first 100 minimum numbers are:" << endl;

  /*
  for (int i = 0; i < NUM; i++) {
    cout << heap[i] << endl;
  }
  */

  heap_sort_output();

  return 0;
}

void make_heap()
{
  for (int i = 0; i < NUM; i++) {
    heap[i] = INT_MAX;
  }
}

void heap_max_heapify(int ix)
{
  ix++;
  int l = ix*2;
  int r = l+1;
  int largest = ix;
  if (l <= heapSize && heap[l-1] > heap[ix-1]) {
    largest = l;
  } else {
    largest = ix;
  }

  if (r <= heapSize && heap[largest-1] < heap[r-1]) {
    largest = r;
  }

  int tmp;
  while (largest != ix) {
    tmp = heap[largest-1];
    heap[largest-1] = heap[ix-1];
    heap[ix-1] = tmp;
    ix = largest;
    heap_max_heapify(ix-1);
  }
}

void heap_sort_output()
{
  int result[NUM];
  for (int i = NUM-1; i >= 0; i--) {
    result[i] = heap[0];
    heap[0] = heap[i];
    heapSize--;
    heap_max_heapify(0);
  }

  for (int i = 0; i < NUM; i++) {
    cout << result[i] << endl;
  }
}
