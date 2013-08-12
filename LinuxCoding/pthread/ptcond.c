#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_CONSUMER 10
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int workCount = 0;

void *producerThread(void *arg)
{
  int ret;
  int i;

  printf("Producer started!\n");

  for (i = 0; i < 10; i++) {
    ret = pthread_mutex_lock(&mutex);
    assert(ret == 0);
    printf("Producer created work %d.\n", i);
    workCount++;
    ret = pthread_cond_broadcast(&cond);
    if (ret != 0) {
      printf("%s: %s\n", "pthread_cond_broadcast", strerror(errno));
    }
    assert(pthread_mutex_unlock(&mutex) == 0);
    sleep(1);
  }

  pthread_exit(arg);
}

void *consumerThread(void *arg)
{
  int ret, i;

  printf("Consumer started!\n");
  pthread_detach(pthread_self());

  while (true) {
    ret = pthread_mutex_lock(&mutex);
    assert(ret == 0);
    pthread_cond_wait(&cond, &mutex);
    if (workCount) {
      printf("Consumer %x performed work %d.\n", pthread_self(), workCount);
      workCount--;
    }
    ret = pthread_mutex_unlock(&mutex);
    assert(ret == 0);
  }

  pthread_exit(arg);
}

int main()
{
  pthread_t consumers[MAX_CONSUMER];
  pthread_t producer;
  int ret, i;

  for (i = 0; i < MAX_CONSUMER; i++) {
    ret = pthread_create(&consumers[i], NULL, consumerThread, NULL);
    if (ret != 0) {
      printf("%s %d: %s\n", "pthread_create", i, strerror(errno));
    }
  }

  ret = pthread_create(&producer, NULL, producerThread, NULL);
  if (ret != 0) {
    printf("%s %d: %s\n", "pthread_create", i, strerror(errno));
  }

  ret = pthread_join(producer, NULL);
  if (ret != 0) {
    printf("%s: %s\n", "pthread_join", strerror(errno));
  }

  while (workCount) ;

  // cancel consumers
  for (i = 0; i < MAX_CONSUMER; i++) {
    ret = pthread_cancel(consumers[i]);
    if (ret != 0) {
      printf("%s %d: %s\n", "pthread_cancel", i, strerror(errno));
    }
  }

  ret = pthread_mutex_destroy(&mutex);
  if (ret != 0) {
    printf("%s: %s\n", "pthread_mutex_destroy", strerror(errno));
  }

  ret = pthread_cond_destroy(&cond);
  if (ret != 0) {
    printf("%s: %s\n", "pthread_cond_destroy", strerror(errno));
  }

  return 0;
}

