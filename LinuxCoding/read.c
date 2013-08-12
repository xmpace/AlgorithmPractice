#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define FILENAME "write.dat"

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *pFile;
  pFile = fopen(FILENAME, "r");

  if (pFile == (FILE*)NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  /*
  wint_t wc;
  while ((wc = fgetwc(pFile)) != EOF) {
    wprintf(L"%lc", (wchar_t)wc);
  }
  */

  wint_t wc;
  while ((wc = fgetwc(pFile)) != EOF) {
    wprintf(L"%lc", (wchar_t)wc);
  }

  fclose(pFile);

  return 0;
}
