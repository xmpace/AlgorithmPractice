// child process send signal to parent

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void usr1_handler(int sig_num)
{
  printf("Parent %d: I caught the usr1 signal.\n", getpid());
  return;
}

int main(int argc, char **argv)
{
  int ret;
  int status;
  int role = -1;

  ret = fork();
  if (ret > 0) {
    printf("Parent: This is parent process: %d\n", getpid());
    signal(SIGUSR1, usr1_handler);
    printf("Parent: I'm waiting child sending signal to me.\n");
    pause();
    printf("Parent: I'm waiting child to exit.\n");
    ret = wait(&status);
    role = 0;
  }
  else if (ret == 0) {
    printf("Child: This is child process: %d\n", getpid());
    printf("Child: I'm sending usr1 signal to my parent.\n");
    sleep(1);
    kill(getppid(), SIGUSR1);
    role = 1;
    sleep(1);
  }
  else {
    printf("Parent: Error occuced when invoke fork().\n");
    return -1;
  }

  printf("%s: Exiting...\n", ((role == 0) ? "Parent" : "Child"));

  return 0;
}
