#include <iostream>

/*int binary_search(int A[], int size, int key);*/
int binary_search(int A[], int left, int right, int key);

using namespace std;

int main(int argc, char **argv)
{
  int num;
  int a[1000];
  cout << "How many numbers: ";
  cin >> num;

  cout << "Input the sorted arrays: ";
  for (int i = 0; i < num; i++)
    cin >> a[i];

  int key;
  cout << "Which number do you want to find: ";
  cin >> key;

  int ix = binary_search(a, 0, num-1, key);
  if (ix != -1)
    cout << "The number " << key << " is at " << ix << "." << endl;
  else
    cout << "The number " << key << " is not in the array." << endl;

  return 0;
}

/*
 *迭代版本
 */
/*
int binary_search(int A[], int size, int key)
{
  int left = 0;
  int right = size - 1;
    
  while (left <= right)
  {
    int mid = (left+right) / 2;
    if (A[mid] == key)
      return mid;
    else if (key > A[mid])
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}
*/

 /*
  *递归版本
  */
int binary_search(int A[], int left, int right, int key)
{
  if (left <= right)
  {
    int mid = (left+right) / 2;
    if (A[mid] == key)
      return mid;
    else if (key > A[mid])
      return binary_search(A, mid+1, right, key);
    else
      return binary_search(A, left, mid-1, key);
  }
  else
    return -1;
}
