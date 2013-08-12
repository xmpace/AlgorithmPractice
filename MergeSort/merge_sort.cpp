#include <iostream>

void merge(int A[], int p, int q, int r);
void merge_sort(int A[], int p, int r);

using namespace std;

int main(int argc, char **argv)
{
  int num;
  int a[1000];
  cout << "How many numbers: ";
  cin >> num;

  cout << "Input the numbers: ";
  for (int i = 0; i < num; i++)
    cin >> a[i];

  merge_sort(a, 0, num-1);
  
  for (int i = 0; i < num; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}

void merge_sort(int A[], int p, int r)
{
  if (p < r)
  {
    int q = (p+r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);
    merge(A, p, q, r);
  }
}

/*
 *哨兵版
 */
/*
void merge(int A[], int p, int q, int r)
{
  int larray[501], rarray[501];
  int lsize = q-p+1;
  int rsize = r-q;

  const int INFINITE = 0x7FFFFFFF;
  larray[lsize] = rarray[rsize] = INFINITE;

  for (int i = 0; i < lsize; i++)
    larray[i] = A[p+i];

  for (int i = 0; i < rsize; i++)
    rarray[i] = A[q+i+1];

  int n = 0;
  int m = 0;
  for (int i = 0; i < lsize + rsize; i++)
  {
    if (larray[n] < rarray[m])
    {
      A[p+i] = larray[n];
      n++;
    }
    else
    {
      A[p+i] = rarray[m];
      m++;
    }
  }
}
*/

/*
 *非哨兵版
 */
void merge(int A[], int p, int q, int r)
{
  int larray[500], rarray[500];
  int lsize = q-p+1;
  int rsize = r-q;

  for (int i = 0; i < lsize; i++)
    larray[i] = A[p+i];
  for (int i = 0; i < rsize; i++)
    rarray[i] = A[q+i+1];

  int n = 0;
  int m = 0;
  int i = 0;
  while (n != lsize && m != rsize)
  {
    if (larray[n] <= rarray[m])
      A[p+i++] = larray[n++];
    else
      A[p+i++] = rarray[m++];
  }
  while (n != lsize)
    A[p+i++] = larray[n++];
  while (m != rsize)
    A[p+i++] = rarray[m++];
}
