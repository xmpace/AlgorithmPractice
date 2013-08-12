#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void *myThread(void *arg)
{
  printf("Thread ran!\n");
  pthread_exit(arg);
}

int main()
{
  pthread_t mythread;
  int ret;

  ret = pthread_create(&mythread, NULL, myThread, NULL);
  if (ret != 0) {
    printf("%s: %s\n", "pthread_create", strerror(errno));
    return -1;
  }

  sleep(1);
  return 0;
}

