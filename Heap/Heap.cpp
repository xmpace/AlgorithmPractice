#include <iostream>
using namespace std;

#define LEFT(i) (i<<1)
#define RIGHT(i) (LEFT(i)+1)
#define PARENT(i) (i/2)
#define INFINITE (0x7FFFFFFF)

void build_max_heap(int A[], int size);
void max_heapify(int A[], int heapSize, int i);
static inline void exchange(int A[], int n, int m);
void heap_sort(int A[], int size);
int heap_maximum(int A[]);
int heap_extract_max(int A[], int size);
int heap_increase_key(int A[], int heapSize, int i, int key);
int max_heap_insert(int A[], int heapSize, int key);

void build_max_heap(int A[], int size)
{
  int n = size / 2;
  for (int i = n; i > 0; i--)
  {
    max_heapify(A, size, i);
  }  
}

static inline void exchange(int A[], int n, int m)
{
  int temp = A[n];
  A[n] = A[m];
  A[m] = temp;
}

/*
void max_heapify(int A[], int heapSize, int i)
{
  int largest = i;
  do
  {
    i = largest;
    int l = LEFT(i);
    int r = RIGHT(i);

    if (l <= heapSize && A[l] > A[i])
      largest = l;
    if (r <= heapSize && A[r] > A[largest])
      largest = r;
    exchange(A, i, largest);
  } while (i != largest)
}
*/

void max_heapify(int A[], int heapSize, int i)
{
  int largest;
  int l,r;

  largest = i;
  while (true)
  {
    l = LEFT(i);
    r = RIGHT(i);

    if (l <= heapSize && A[l] > A[i])
      largest = l;
    if (r <= heapSize && A[r] > A[largest])
      largest = r;

    if (largest == i)
      break;
    else
    {
      exchange(A, largest, i);
      i = largest;
    }
  }
}

int main(int argc, char **argv)
{
  int num;
  int a[1001];
  cout << "How many numbers: ";
  cin >> num;

  cout << "Input the arrays: ";
  for (int i = 1; i <= num && cin >> a[i]; i++);

  heap_sort(a, num);
  
  cout << "The sorted array is: ";
  for (int i = 1; i <= num; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}

void heap_sort(int A[], int size)
{
  build_max_heap(A, size);
  
  int heapSize = size;
  for (int i = size; i > 1; i--)
  {
    exchange(A, 1, i);
    heapSize--;
    max_heapify(A, heapSize, 1);
  }
}

int heap_maximum(int A[])
{
  return A[1];
}

int heap_extract_max(int A[], int size)
{
  int ret = A[1];
  exchange(A, 1, size);
  max_heapify(A, size-1, 1);
  return ret;
}

int heap_increase_key(int A[], int heapSize, int i, int key)
{
  if (key < A[i])
    return -1;
  A[i] = key;
  while (i > 1 && A[i] > A[PARENT(i)])
  {
    exchange(A, i, PARENT(i));
    i = PARENT(i);
  }
  return i;
}

int max_heap_insert(int A[], int heapSize, int key)
{
  A[heapSize+1] = -INFINITE;
  return heap_increase_key(A, heapSize+1, heapSize+1, key);
}

