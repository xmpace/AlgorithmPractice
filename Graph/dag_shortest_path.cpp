#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

// Conditional Compile
//#define _DEBUG

// typedef
typedef struct _EdgeNode {
  struct _EdgeNode *next;
  int ver;
  int w;
} EdgeNode;

typedef enum {WHITE, BLACK} COLOR;

//macros
#define MAX_VERTICES 1000

//global variables
static EdgeNode* G[MAX_VERTICES];
static int W[MAX_VERTICES][MAX_VERTICES];
static COLOR color[MAX_VERTICES];
static int topologicalQueue[MAX_VERTICES];
static int g_queueIx = 0;
static int d[MAX_VERTICES];

//local functions
static void dag_shortest_path(int vernum);
static void initialize_single_source(int ver);
static void dfs_topologic(int vernum);
static void dfs_visit(int ver);
static void relax(int u, int v);

int main()
{
  int vernum;
  cin >> vernum;

  string line;
  int w;
  EdgeNode *edge;
  for (int i = 1; i <= vernum; i++) {
    getline(cin, line);
    istringstream in(line);
    for (int j = 1; j <= vernum; j++) {
      cin >> w;
      W[i][j] = w;
      if (w != 0) {
	edge = new EdgeNode;
	edge->ver = j;
	edge->w = w;
	edge->next = G[i];
	G[i] = edge;
      }
    }
  }

  #ifdef _DEBUG
  for (int i = 1; i <= vernum; i++) {
    for (int j = 1; j <= vernum; j++) {
      cout << W[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 1; i <= vernum; i++) {
    cout << i << ": ";
    EdgeNode *tmp = G[i];
    while (tmp) {
      cout << tmp->ver << "(" << tmp->w << ") ";
      tmp = tmp->next;
    }
    cout << endl;
  }
  #endif

  for (int i = 1; i <= vernum; i++) {
    d[i] = INT_MAX;
  }
  dag_shortest_path(vernum);

  // output result
  for (int i = 1; i <= vernum; i++) {
    if (d[i] == INT_MAX) {
      cout << i << ": INFINITE" << endl;
    } else {
    cout << i << ": " << d[i] << endl;
    }
  }

  return 0;
}

void dag_shortest_path(int vernum)
{
  // initialize
  g_queueIx = 0;

  initialize_single_source(2);

  dfs_topologic(vernum);

  for (int i = g_queueIx; i >= 0; i--) {
    EdgeNode *tmp = G[topologicalQueue[i]];
    while (tmp) {
      relax(topologicalQueue[i], tmp->ver);
      tmp = tmp->next;
    }
  }
}

void initialize_single_source(int ver)
{
  d[ver] = 0;
}

void dfs_topologic(int vernum)
{
  for (int i = 1; i <= vernum; i++) {
    color[i] = WHITE;
  }

  for (int i = 1; i <= vernum; i++) {
    if (color[i] == WHITE) {
      dfs_visit(i);
    }
  }
}

void dfs_visit(int ver)
{
  color[ver] = BLACK;
  EdgeNode *tmp = G[ver];
  while (tmp) {
    if (color[tmp->ver] == WHITE) {
      dfs_visit(tmp->ver);
    }
    tmp = tmp->next;
  }
  topologicalQueue[g_queueIx++] = ver;
}

void relax(int u, int v)
{
  if (d[u] != INT_MAX) {
    if (d[v] > d[u] + W[u][v]) {
      d[v] = d[u] + W[u][v];
    }
  }
}
