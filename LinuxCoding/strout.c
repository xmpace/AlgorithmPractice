#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <wchar.h>

#define LEN 80
#define FILENAME "strout.dat"
int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *fout;
  fout = fopen(FILENAME, "w");

  if (fout == NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  FILE *fin;
  fin = fdopen(0, "r");

  wchar_t line[LEN+1];
  while (fgetws(line, LEN, fin) != NULL) {
    fputws(line, fout);
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
