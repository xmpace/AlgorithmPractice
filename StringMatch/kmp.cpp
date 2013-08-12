#include <iostream>
#include <string>

using namespace std;

int* generate_prefix(string &str);

int main(int argc, char **argv)
{
  string subStr, str;
  getline(cin, str);
  getline(cin, subStr);

  int *prefix = generate_prefix(subStr);

  int subLen = subStr.length();
  int len = str.length();
  int q = 0;
  for (int i = 0; i < len; i++) {
    while (q != 0 && subStr[q] != str[i]) {
      q = prefix[q];
    }
    if (subStr[q] == str[i]) {
      q++;
    } 

    if (q == subLen) {
      cout << "Matched!" << endl;
      q = 0;
    }
  }

  delete[] prefix;
  return 0;
}

int* generate_prefix(string &str)
{
  int len = str.length();
  int *prefix = new int[len+1];

  prefix[1] = 0;
  int k = 0;
  for (int i = 2; i <= len; i++) {
    while (prefix[k] != 0 && str[k] != str[i-1]) {
      k = prefix[k];
    }
    if (str[k] == str[i-1]) {
      prefix[i] = k + 1;
    } else {
      prefix[i] = 0;
    }
  }

  return prefix;
}
