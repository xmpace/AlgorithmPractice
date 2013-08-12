#include <iostream>
using namespace std;

void quick_sort(int A[], int p, int q);
int partition(int A[], int p, int q);
void exchange(int A[], int n, int m);

int main(int argc, char **argv)
{
  int num;
  int a[1001];

  cout << "How many numbers: ";
  cin >> num;

  cout << "Input the numbers: ";
  for (int i = 0; i < num && cin >> a[i]; i++);

  quick_sort(a, 0, num-1);

  cout << "The sorted array is: ";
  for (int i = 0; i < num; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}

void quick_sort(int A[], int p, int q)
{
  if (q > p)
  {
    int r = partition(A, p, q);
    quick_sort(A, p, r);
    quick_sort(A, r+1, q);
  }
}

/*
int partition(int A[], int p, int q)
{
  int x = A[q];
  int i = p-1;
  for (int j = p; j < q; j++)
  {
    if (A[j] < x)
    {
      i++;
      exchange(A, i, j);
    }
  }
  exchange(A, i+1, q);
  return i+1;
}
*/

int partition(int A[], int p, int q)
{
  int x = A[p];
  int i = p-1;
  int j = q+1;
  while (true)
  {
    while (A[--j] > x);
    while (A[++i] < x);
    if (i < j)
      exchange(A, i, j);
    else
      return j;
  }
}

void exchange(int A[], int n, int m)
{
  int temp = A[n];
  A[n] = A[m];
  A[m] = temp;
}
