#include <iostream>
#include <string>

using namespace std;
void _radixTransform(int m, int radix, string &);
string* radixTransform(int m , int radix);
int main(int argc, char **argv)
{
  string* s = radixTransform(217, 8);
  cout << *s << endl;
  return 0;
}

string* radixTransform(int m , int radix)
{
  string *result = new string;
  _radixTransform(m, radix, *result);
  return result;
}

void _radixTransform(int m, int radix, string &s)
{  
  if (m == 0) {
    return;
  }
  else {
    _radixTransform(m / radix, radix, s);
    s.push_back((m % radix) + '0');
  }
}
  
