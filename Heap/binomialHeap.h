#ifndef _BINOMIAL_HEAP_H__
#define _BINOMIAL_HEAP_H__
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct _HeapNode {
  struct _HeapNode *parent;
  struct _HeapNode *child;
  struct _HeapNode *sibling;
  int degree;
  int key;
  void *data;
} HeapNode;

extern HeapNode* binomial_heap_union(HeapNode *h1, HeapNode *h2);
extern void binomial_heap_insert(HeapNode **h, int key, void *data);
extern HeapNode* binomial_heap_extract_min(HeapNode**);
extern HeapNode* binomial_heap_minimum(HeapNode *h);
extern HeapNode* binomial_heap_delete(HeapNode **head, HeapNode *node);

#endif
