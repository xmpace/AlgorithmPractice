#include "binomialHeap.h"
#include <iostream>
#include <sstream>
#include <string>
#include <climits>
using namespace std;

#define MAX_VERTICES 1000

typedef struct _EdgeNode {
  int vex;
  int w;
  struct _EdgeNode *next;
} EdgeNode;

EdgeNode *G[MAX_VERTICES];
int key[MAX_VERTICES];
int verHeap[MAX_VERTICES];
bool isInHeap[MAX_VERTICES];
int heapIx[MAX_VERTICES];
int heapSize;
int parent[MAX_VERTICES];

// local functions
int MST_PRIM(int vernum);
void heap_decrease_key(int verIx, int newkey);
int heap_extract_min();
void min_heapify(int ix);

int main()
{
  int m, n;
  cin >> m >> n;

  string line;
  getline(cin, line);

  int x, y, w;
  for (int i = 0; i < m; i++) {
    getline(cin, line);
    istringstream in(line);
    in >> x >> y >> w;

    EdgeNode *edge = new EdgeNode;
    edge->vex = y;
    edge->w = w;
    edge->next = G[x];
    G[x] = edge;

    edge = new EdgeNode;
    edge->vex = x;
    edge->w = w;
    edge->next = G[y];
    G[y] = edge;
  }

  /*
  for (int i = 1; i <= n; i++) {
    EdgeNode *p = G[i];
    while (p) {
      cout << p->vex << "(" << p->w << ")" << " ";
      p = p->next;
    }
    cout << endl;
  }
  */

  for (int i = 1; i <= n; i++) {
    key[i] = INT_MAX;
    verHeap[i] = i;
    isInHeap[i] = true;
    heapIx[i] = i;
    heapSize = n;
    parent[i] = 0;
  }

  int sum = MST_PRIM(n);
  
  cout << sum << endl;

  return 0;
}

int MST_PRIM(int vernum)
{
  int sum = 0;

  for (int i = 1; i <= vernum; i++) {
    key[i] = INT_MAX;
    parent[i] = 0;
    verHeap[i] = i;
    heapIx[i] = i;
  }

  key[1] = 0;
  heap_decrease_key(1, 0);
  heapSize = vernum;

  while (heapSize != 0) {
    int minVer = heap_extract_min();
    sum += key[minVer];
    EdgeNode *edge = G[minVer];
    while (edge) {
      if (isInHeap[edge->vex] && edge->w < key[edge->vex]) {
	parent[edge->vex] = minVer;
	heap_decrease_key(edge->vex, edge->w);
      }
      edge = edge->next;
    }
  }

  return sum;
}

// 将verIx的顶点的key值减小到newkey
void heap_decrease_key(int verIx, int newkey)
{
  if (newkey > key[verIx]) {
    cerr << "fatal: heap_decrease_key(" << verIx << ", " << newkey << ")" << endl;
    exit(1);
  }

  key[verIx] = newkey;

  int index = heapIx[verIx];
  int paren = index / 2;
  int tmp;
  while (paren != 0 && key[verHeap[index]] < key[verHeap[paren]]) {
    heapIx[verIx] = paren;
    heapIx[verHeap[paren]] = index;
    tmp = verHeap[index];
    verHeap[index] = verHeap[paren];
    verHeap[paren] = tmp;
    index = paren;
    paren /= 2;
  }
}

int heap_extract_min()
{
   int result = verHeap[1];
   isInHeap[verHeap[1]] = false;
   heapIx[verHeap[heapSize]] = 1;
   verHeap[1] = verHeap[heapSize];
   heapSize--;
   min_heapify(1);
   return result;
}

void min_heapify(int ix)
{
  int l = ix*2;
  int r = l+1;

  int minimum = ix;
  if (l <= heapSize && key[verHeap[l]] < key[verHeap[ix]]) {
    minimum = l;
  }
  else {
    minimum = ix;
  }

  if (r <= heapSize && key[verHeap[r]] < key[verHeap[minimum]]) {
    minimum = r;
  }

  int tmp;
  if (minimum != ix) {
    heapIx[verHeap[minimum]] = ix;
    heapIx[verHeap[ix]] = minimum;
    tmp = verHeap[minimum];
    verHeap[minimum] = verHeap[ix];
    verHeap[ix] = tmp;
    min_heapify(minimum);
  }
}
