#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
long globalVariable = 0L;

void *myThread(void *arg)
{
  int i;
  int ret = pthread_mutex_lock(&mu);
  assert(ret == 0);

  for (i = 0; i < 1000; i++) {
    globalVariable++;
  }

  ret = pthread_mutex_unlock(&mu);
  assert(ret == 0);

  pthread_exit(arg);
}

#define MAX_THREADS 10

int main()
{
  int i;
  pthread_t myThreads[MAX_THREADS];
  int ret;

  for (i = 0; i < MAX_THREADS; i++) {
    ret = pthread_create(&myThreads[i], NULL, myThread, NULL);
    if (ret != 0) {
      printf("%s %d: %s\n", "pthread_create", i, strerror(errno));
    }
  }

  for (i = 0; i < MAX_THREADS; i++) {
    ret = pthread_join(myThreads[i], NULL);
    if (ret != 0) {
      printf("%s %d: %s\n", "pthread_join", i, strerror(errno));
    }
  }

  printf("The value of globalVariable is: %ld\n", globalVariable);

  ret = pthread_mutex_destroy(&mu);
  if (ret != 0) {
    // error!
  }

  return 0;
}
