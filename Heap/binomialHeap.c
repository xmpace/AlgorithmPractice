#include "binomialHeap.h"

static HeapNode* binomial_heap_link(HeapNode*, HeapNode*);
static HeapNode* binomial_heap_merge(HeapNode*, HeapNode*);
static void _binomial_heap_insert(HeapNode**, HeapNode*);
static bool _binomial_heap_decrease_key(HeapNode*, int);

HeapNode* binomial_heap_link(HeapNode *h1, HeapNode *h2)
{
  h2->sibling = h1->child;
  h1->child = h2;
  h2->parent = h1;
  h1->degree++;
  return h1;
}

HeapNode* binomial_heap_minimum(HeapNode *h)
{
  HeapNode *result = NULL;
  int min = INT_MAX;

  while (h) {
    if (h->key < min) {
      min = h->key;
      result = h;
    }
    h = h->sibling;
  }

  return result;
}

HeapNode* binomial_heap_merge(HeapNode *h1, HeapNode *h2)
{
  HeapNode *newH = NULL;
  HeapNode *p = NULL;
  if (h1->degree < h2->degree) {
    newH = h1;
    h1 = h1->sibling;
  }
  else {
    newH = h2;
    h2 = h2->sibling;
  }
  p = newH;

  while (h1 != NULL && h2 != NULL) {
    if (h1->degree < h2->degree) {
      p->sibling = h1;
      h1 = h1->sibling;
    }
    else {
      p->sibling = h2;
      h2 = h2->sibling;
    }
    p = p->sibling;
  }
  while (h1 != NULL) {
    p->sibling = h1;
    p = h1;
    h1 = h1->sibling;
  }
  while (h2 != NULL) {
    p->sibling = h2;
    p = h2;
    h2 = h2->sibling;
  }

  return newH;
}

HeapNode* binomial_heap_union(HeapNode *h1, HeapNode *h2)
{
  if (h1 == NULL) {
    return h2;
  }
  else if (h2 == NULL) {
    return h1;
  }

  HeapNode *newH = binomial_heap_merge(h1, h2);
  HeapNode *prevx = NULL;
  HeapNode *x = newH;
  HeapNode *nextx = x->sibling;

  while (nextx) {
    if ( (x->degree != nextx->degree) || 
	 ((nextx->sibling != NULL) && (x->degree == nextx->sibling->degree)))
      {
	prevx = x;
	x = nextx;
      }
    else if (x->key < nextx->key) {
      x->sibling = nextx->sibling;
      x = binomial_heap_link(x, nextx);
    }
    else {
      if (prevx == NULL) {
	newH = nextx;
      }
      else {
	prevx->sibling = nextx;
      }
      x = binomial_heap_link(nextx, x);
    }
    nextx = x->sibling;
  }

  return newH;
}

void _binomial_heap_insert(HeapNode **h, HeapNode *node)
{
  *h = binomial_heap_union(*h, node);
}

void binomial_heap_insert(HeapNode **h, int key, void *data)
{
  HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode));
  memset(node, 0, sizeof(HeapNode));
  node->key = key;
  node->data = data;
  _binomial_heap_insert(h, node);
}

HeapNode* binomial_heap_extract_min(HeapNode **h)
{
  HeapNode *head = *h;
  HeapNode *prev = NULL;
  HeapNode *hMin = NULL;
  HeapNode *prevMin = NULL;
  int min = INT_MAX;

  if (head == NULL) {
    return NULL;
  }

  while (head) {
    if (head->key < min) {
      min = head->key;
      hMin = head;
      prevMin = prev;
    }
    prev = head;
    head = head->sibling;
  }

  if (prevMin) {
    prevMin->sibling = hMin->sibling;
  }
  else {
    *h = hMin->sibling;
  }
  hMin->sibling = NULL;

  if (hMin->degree == 0) {
    return hMin;
  }

  prev = hMin->child;
  hMin->child = NULL;

  HeapNode *newHeap = prev;
  prev->parent = NULL;
  head = prev->sibling;
  prev->sibling = NULL;


  prev = head;
  while (prev) {
    head = prev->sibling;
    prev->sibling = newHeap;
    prev->parent = NULL;
    newHeap = prev;
    prev = head;
  }

  *h = binomial_heap_union(*h, newHeap);

  return hMin;
}

bool _binomial_heap_decrease_key(HeapNode *node, int key)
{
  if (key > node->key) {
    return false;
  }

  HeapNode *p = node->parent;
  HeapNode *tmp;
  void *vtmp;
  int ntmp;
  while (p && node->key < p->key) {
    ntmp = node->key;
    node->key = p->key;
    p->key = ntmp;

    vtmp = node->data;
    node->data = p->data;
    p->data = vtmp;

    node = p;
    p = p->parent;
  }

  return true;
}

HeapNode* binomial_heap_delete(HeapNode **head, HeapNode *node)
{
  _binomial_heap_decrease_key(node, INT_MIN);
  return binomial_heap_extract_min(head);
}

