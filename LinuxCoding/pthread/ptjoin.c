#include <pthread.h>
#include <string.h>
#include <stdio.h>

void *myThread(void *arg)
{
  printf("Thread %d is running.\n", arg);
  pthread_exit(arg);
}

#define MAX_THREADS 5

int main()
{
  int ret, i, status;
  pthread_t threadIds[MAX_THREADS];

  for (i = 0; i < MAX_THREADS; i++) {
    ret = pthread_create(&threadIds[i], NULL, myThread, (void *)i);
    if (ret != 0) {
      printf("create thread %d error.\n", i);
      return -1;
    }
  }

  for (i = 0; i < MAX_THREADS; i++) {
    ret = pthread_join(threadIds[i], (void **)&status);
    if (ret != 0) {
    }
    else {
      printf("Status = %d\n", status);
    }
  }

  return 0;
}
