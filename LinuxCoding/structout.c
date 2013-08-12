#include <stdio.h>
#include <errno.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

#define LEN 40
#define FILENAME "structout.dat"

typedef struct {
  int id;
  float x_coord;
  float y_coord;
  wchar_t name[LEN+1];
} MY_TYPE_T;

#define MAX_OBJS 3
MY_TYPE_T objs[MAX_OBJS] = {
  {0, 1.5, 8.4, L"第一个点"},
  {1, 2.1, 7.9, L"第二个点"},
  {2, 3.2, 4.7, L"第三个点"}
};

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  FILE *fout;
  fout = fopen(FILENAME, "w");
  if (fout == NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  int i = 0;
  for (i = 0; i < MAX_OBJS; i++) {
    fwprintf(fout, L"%d %f %f %ls\n",
	     objs[i].id,
	     objs[i].x_coord,
	     objs[i].y_coord,
	     objs[i].name);
  }

  fclose(fout);

  return 0;
}
