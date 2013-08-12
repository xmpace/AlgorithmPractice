#include <iostream>

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
    
  /*
  for (int j = 1; j < num; j++)
  {
    for (int k = 0; k < j-1; k++)
    {
      if (a[j] < a[k])
      {
	key = a[j];
	for (int m = j-1; m >= k; m--)
	  a[m+1] = a[m];
	a[k] = key;
      }
    }
  }
  */
  
  for (int j = 1; j < num; j++)
  {
    key = a[j];
    int i = j-1;
    
    while (i > -1 && a[i] < key)
    {
      a[i+1] = a[i];
      i--;
    }
    a[i+1] = key;
  }

  cout << "Sorted numbers are: ";
  for(int i = 0; i < num; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
    
  return 0;
}
