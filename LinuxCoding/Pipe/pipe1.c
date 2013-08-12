#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LEN 80
#define PIPE_STDOUT 1
#define PIPE_STDIN  0

int main(int argc, char **argv)
{
  int ret, myPipe[2];
  const char* str = "你好，我是一个管道！Hello World!";
  //  printf("%d\n", wcslen(str));

  ret = pipe(myPipe);

  char recv[LEN+1];
  if (ret == 0) {
    write(myPipe[PIPE_STDOUT], str, strlen(str)+1);
    ret = read(myPipe[PIPE_STDIN], recv, LEN);

    printf("%s\n", recv);
  }

  return 0;
}
