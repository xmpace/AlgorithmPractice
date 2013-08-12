#include <stdio.h>


int main(int argc, char *argv[], char *envp[])
{
  char *p;
  int index = 0;
  for (; p = envp[index++]; ) {
    if (strncmp(p, "PATH", 4) == 0) {
      printf("%s\n", p);
    }
  }

  return 0;
}



 /*
extern char *environ[];

int main(int argc, char *argv[])
{
  int index = 0;
  char *p = environ[0];
  for (; p; p = environ[index++]) {
    printf("%s\n", p);
  }
  return 0;
}
 */
