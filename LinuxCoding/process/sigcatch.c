#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void catch_ctrlc(int sig_num)
{
  printf("Caught Control-C\n");
  fflush(stdout);
  return;
}

int main(int argc, char **argv)
{
  signal(SIGINT, catch_ctrlc);

  printf("I'm waiting for SIGINT...\n");

  pause();

  return 0;
}
