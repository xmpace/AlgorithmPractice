#include <stdio.h>
#include <errno.h>
#include <string.h>

#define FILENAME "xiaomi.ext"

int main(int argc, char **argv)
{
  FILE *pFile;
  pFile = fopen(FILENAME, "r");

  if (pFile == (FILE*)NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  fclose(pFile);
  return 0;
}
