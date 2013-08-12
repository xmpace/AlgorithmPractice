#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <errno.h>

#define LEN 40

typedef struct {
  int id;
  float x;
  float y;
  wchar_t name[LEN+1];
} MY_TYPE_T;

#define FILENAME "structout.dat"

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *fin;
  fin = fopen(FILENAME, "r");
  if (fin == NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  MY_TYPE_T obj;
  while (!feof(fin)) {
    fwscanf(fin, L"%d %f %f %ls\n",
	    &obj.id,
	    &obj.x,
	    &obj.y,
	    &obj.name);

    wprintf(L"%d %f %f %ls\n",
	    obj.id,
	    obj.x,
	    obj.y,
	    obj.name);
  }

  fclose(fin);

  return 0;
}

