#include <stdio.h>

typedef struct _Edge {
  struct _Edge *next;
  int vex;
  int w;
} Edge;

int main()
{
  int m;
  scanf("%d", &m);
  Edge *G = malloc(
