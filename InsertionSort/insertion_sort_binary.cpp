#include <iostream>

int insertion_position(int A[], int ix);

using namespace std;

int main(int argc, char **argv)
{
  int a[1000];
  int key = 0;
  int num = 0;
  cout << "How many numbers: ";
  cin >> num;

  cout << "Input the numbers: ";
  for (int i = 0; i < num && cin >> a[i]; i++);

  
  for (int j = 1; j < num; j++)
  {
    int pos = insertion_position(a, j);
    int key = a[j];
    for (int i = j-1; i >= pos; i--)
      a[i+1] = a[i];
    a[pos] = key;
  }
  

  cout << "Sorted numbers are: ";
  for(int i = 0; i < num; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
    
  return 0;
}

int insertion_position(int A[], int ix)
{
  int end = ix - 1;
  int left = 0;
  int right = end;

  while (left <= right)
  {
    int mid = (left+right) / 2;
    if (A[mid] == A[ix])
      return mid;
    else if (A[ix] > A[mid])
      left = mid + 1;
    else
      right = mid - 1;
  }
  return left;
}
