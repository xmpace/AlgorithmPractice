#include <stdio.h>
#include <errno.h>
#include <string.h>

#define FILENAME "write.dat"

int main(int argc, char **argv)
{
  FILE *pFile;
  const char str[] = "你好，我是肖密\nHello World!\n";

  pFile = fopen(FILENAME, "w");
  if (pFile == (FILE*)NULL) {
    printf("%s: %s\n", FILENAME, strerror(errno));
    return -1;
  }

  int i = 0;
  while (str[i] != '\0') {
    fputc((int)str[i], pFile);
    i++;
  }

  fclose(pFile);

  return 0;
}
