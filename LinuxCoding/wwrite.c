#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define FILENAME "wwrite.dat"

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *pFile;
  const wchar_t str[] = L"你好，我是肖密\nHello World!\n";

  pFile = fopen(FILENAME, "w");
  if (pFile == (FILE*)NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  int i = 0;
  while (str[i] != L'\0') {
    fputwc((wint_t)str[i], pFile);
    i++;
  }

  fclose(pFile);

  return 0;
}
