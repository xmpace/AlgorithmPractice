#include <iostream>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

// local typedef
typedef struct _EdgeNode {
  struct _EdgeNode *next;
  int ver;
  int w;
} EdgeNode;

// macros
#define MAX_VERTICES 1000

// global variables
int g_dist[MAX_VERTICES];
int g_parent[MAX_VERTICES];
EdgeNode* G[MAX_VERTICES];
int W[MAX_VERTICES][MAX_VERTICES];

//local funtions
static bool bellman_ford(EdgeNode* G[], int vernum, int s);
static void initialize_single_source(int s);
static void relax(int u, int v);

int main()
{
  int vernum;
  cin >> vernum;

  for (int i = 1; i <= vernum; i++) {
    G[i] = NULL;
  }

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

  bellman_ford(G, vernum, 1);

  for (int i = 1; i <= vernum; i++) {
    if (g_dist[i] == INT_MAX) {
      cout << "INFINITE" << endl;
    }
    else {
      cout << g_dist[i] << endl;
    }
  }

  return 0;
}

bool bellman_ford(EdgeNode* G[], int vernum, int s)
{
  for (int i = 1; i <= vernum; i++) {
    g_dist[i] = INT_MAX;
    g_parent[i] = 0;
  }
  initialize_single_source(s);

  EdgeNode *edge;
  for (int i = 1; i < vernum; i++) {
    for (int j = 1; j <= vernum; j++) {
      edge = G[j];
      while (edge) {
	relax(j, edge->ver);
	edge = edge->next;
      }
    }
  }

  for (int i = 1; i <= vernum; i++) {
    edge = G[i];
    while (edge) {
      if (g_dist[edge->ver] > g_dist[i] + W[i][edge->ver]) {
	return false;
      }
      edge = edge->next;
    }
  }

  return true;
}

void initialize_single_source(int s)
{
  g_dist[s] = 0;
}

void relax(int u, int v)
{
  if (g_dist[u] != INT_MAX) {
    if (g_dist[v] > g_dist[u] + W[u][v]) {
      g_dist[v] = g_dist[u] + W[u][v];
      g_parent[v] = u;
    }
  }
}
