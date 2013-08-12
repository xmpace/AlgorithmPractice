#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int num = 0;
  int array[1000];

  int i = 0;
  while (cin >> array[i++]);
  num = --i;
  
  // Print array
  for (i = 0; i < num; i++)
    cout << array[i] << " ";
  cout << endl;

  int b;
  b = array[0];
  int max = b;

  for(i = 1; i < num; i++)
  {
    if (b + array[i] < array[i])
    {
      b = array[i];
    }
    else
    {
      b += array[i];
    }
    
    if (b > max)
      max = b;
  }

  cout << "The maximum sum is " << max << endl;

  return 0;
}
