// send signal to self.

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void usr1_handler(int sig_num)
{
  printf("I caught the usr1 signal!\n");
  return;
}

int main(int argc, char **argv)
{
  signal(SIGUSR1, usr1_handler);

  printf("I'm sending usr1 signal to myself.\n");

  raise(SIGUSR1);

  printf("I'm exiting...\n");

  return 0;
}
