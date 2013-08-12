#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <errno.h>
#include <locale.h>

#define LEN 80
#define FILENAME "strout.dat"

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *pFile;
  pFile = fopen(FILENAME, "r");
  if (pFile == NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  wchar_t line[LEN+1];
  while (fgetws(line, LEN, pFile) != NULL) {
    wprintf(L"%ls", line);
  }

  fclose(pFile);

  return 0;
}
