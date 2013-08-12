#include <iostream>
#include <climits>
#include <string>
#include <sstream>
using namespace std;

typedef struct _EdgeNode {
  struct _EdgeNode *next;
  int ver;
  int w;
} EdgeNode;

// macros
#define MAX_VERTICES 1000
#define HEAP_IX(x) (g_heapIx[x])
#define VER_NUM(x) (g_heap[x])

// global_variables
EdgeNode* G[MAX_VERTICES];
int g_dist[MAX_VERTICES];
int g_parent[MAX_VERTICES];
int g_heap[MAX_VERTICES];
int g_heapSize;
int g_heapIx[MAX_VERTICES];
int W[MAX_VERTICES][MAX_VERTICES];

// local function declaration
int dijkstra(EdgeNode* G[], int vernum, int s);
void initialize_single_source(EdgeNode* G[], int vernum, int s);
void decrease_distance(int pt, int newdist);
void heap_decrease_key(int ix, int key);
int heap_extract_min();
void heap_min_heapify(int ix);
void relax(int u, int v);

int main()
{
  int vernum;
  cin >> vernum;

  string line;
  //  getline(cin, line);

  int w = 0;
  EdgeNode *edge = NULL;
  for (int i = 1; i <= vernum; i++) {
    getline(cin, line);
    istringstream in(line);
    for (int j = 1; j <= vernum; j++) {
      cin >> w;

      if (w != 0) {
	edge = new EdgeNode;
	edge->ver = j;
	edge->w = w;
	edge->next = G[i];
	G[i] = edge;
      }
      W[i][j] = w;
    }
  }

  /* DEBUG
  for (int i = 1; i<= vernum; i++) {
    for (int j = 1; j <= vernum; j++) {
      cout << W[i][j] << " ";
    }
    cout << endl;
  }
  DEBUG */
  dijkstra(G, vernum, 2);

  for (int i = 1; i <= vernum; i++) {
    if (g_dist[i] == INT_MAX) {
      cout << "INFINITE" << endl;
    } else {
      cout << g_dist[i] << endl;
    }
  }
  
  return 0;
}

int dijkstra(EdgeNode* G[], int vernum, int s)
{
  int sum = 0;

  for (int i = 1; i <= vernum; i++) {
    g_heap[i] = i;
    g_heapIx[i] = i;
    g_dist[i] = INT_MAX;
    g_parent[i] = 0;
    g_heapSize = vernum;
  }

  initialize_single_source(G, vernum, s);
  while (g_heapSize != 0) {
    int u = heap_extract_min();
    sum += g_dist[u];
    EdgeNode *edge = G[u];
    while (edge) {
      relax(u, edge->ver);
      edge = edge->next;
    }
  }

  return sum;
}


void initialize_single_source(EdgeNode* G[], int vernum, int s)
{
  decrease_distance(s, 0);
}

void decrease_distance(int pt, int newdist)
{
  g_dist[pt] = newdist;
  heap_decrease_key(HEAP_IX(pt), newdist);
}

void heap_decrease_key(int ix, int key)
{
  int paren = ix / 2;
  int tmp;
  while (paren != 0 && g_dist[VER_NUM(ix)] < g_dist[VER_NUM(paren)]) {
    g_heapIx[VER_NUM(ix)] = paren;
    g_heapIx[VER_NUM(paren)] = ix;
    tmp = g_heap[ix];
    g_heap[ix] = g_heap[paren];
    g_heap[paren] = tmp;
    ix = paren;
    paren /= 2;
  }
}


int heap_extract_min()
{
  int result = g_heap[1];
  g_heapIx[VER_NUM(g_heapSize)] = 1;
  g_heapIx[VER_NUM(1)] = g_heapSize;
  g_heap[1] = g_heap[g_heapSize];
  g_heapSize--;
  heap_min_heapify(1);
  return result;
}

void heap_min_heapify(int ix)
{
  int l = ix * 2;
  int r = l + 1;
  int minute = ix;

  if (l <= g_heapSize && g_dist[VER_NUM(l)] < g_dist[VER_NUM(ix)]) {
    minute = l;
  } else {
    minute = ix;
  }

  if (r <= g_heapSize && g_dist[VER_NUM(r)] < g_dist[VER_NUM(minute)]) {
    minute = r;
  }

  int tmp;
  if (minute != ix) {
    g_heapIx[VER_NUM(ix)] = minute;
    g_heapIx[VER_NUM(minute)] = ix;
    tmp = g_heap[minute];
    g_heap[minute] = g_heap[ix];
    g_heap[ix] = tmp;
    heap_min_heapify(minute);
  }
}

void relax(int u, int v)
{
  /* DEBUG
  if (v == 3) {
    cout << "-----------" << endl;
    cout << u << endl;
    cout << v << endl;
    cout << g_dist[u] << endl;
    cout << W[u][v] << endl;
    cout << g_dist[v] << endl;
    cout << "-----------" << endl;
  }
  DEBUG */ 
  if (g_dist[u] != INT_MAX) {
    if (g_dist[u] + W[u][v] < g_dist[v]) {
      decrease_distance(v, g_dist[u]+W[u][v]);
      g_parent[v] = u;
    }
  }
}
