#include "binomialHeap.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
  int key;
  int i;
  HeapNode *Heap = NULL;
  HeapNode *tmp;
  HeapNode *tmpChild;

  srand(time(NULL));

  for (i = 0; i < 100; i++) {
    key = rand() % 10000 + 1;
    printf("%d\n", key);
    binomial_heap_insert(&Heap, key, NULL);
  }

  printf("%s: %d\n", "The minimum key is", binomial_heap_minimum(Heap)->key);

  while ( (tmp=binomial_heap_extract_min(&Heap)) != NULL ) {
    printf("%d ", tmp->key);
    free(tmp);
  }
  printf("\n");

  return 0;
}

