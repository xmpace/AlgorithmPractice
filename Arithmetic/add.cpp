#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

#define MAX_LEN 100

void reverse_string(char *str);
char *add(const char *a, const char *b);
int main(int argc, char **argv)
{
  char a[MAX_LEN], b[MAX_LEN];
  scanf("%s", a);
  scanf("%s", b);
  char *result = add(a, b);
  cout << result << endl;
  return 0;
}

char *add(const char *a, const char *b)
{
  int c = 0; // 进位
  int aix = strlen(a);
  int bix = strlen(b);
  char achar, bchar, rchar;

  int maxlen = aix;
  if (bix > maxlen) {
    maxlen = bix;
  }

  aix--;
  bix--;

  char *result = (char*)malloc(maxlen+1);

  int ix = 0;
  while (aix >= 0 || bix >= 0) {
    if (aix < 0) {
      achar = '0';
    } else {
      achar = a[aix];
    }

    if (bix < 0) {
      bchar = '0';
    } else {
      bchar = b[bix];
    }

    rchar = achar - '0' + bchar + c;
    if (rchar > '9') {
      c = 1;
      rchar -= 10;
    } else {
      c = 0;
    }

    result[ix++] = rchar;
    aix--;
    bix--;
  }

  if (c == 1) {
    result[ix++] = '1';
  }
  result[ix] = '\0';

  reverse_string(result);
  return result;
}

void reverse_string(char *str)
{
  int len = strlen(str);
  int i = 0;
  int j = len - 1;
  while (i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}
