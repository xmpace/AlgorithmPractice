#include <stdio.h>
#include <deque>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef struct _edge {
  _edge *next;
  int vex;
} Edge;

typedef enum {WHITE = 0, GREY, BLACK} COLOR;

// Global variables
vector<COLOR> color;
vector<size_t> dist;
vector<size_t> parent;

void BFS(vector<Edge*> &G) {
  size_t vexnum = G.size();

  color.resize(vexnum);
  dist.resize(vexnum);
  parent.resize(vexnum);

  deque<size_t> Q;
  size_t s = 1;
  color[s] = GREY;
  dist[s] = 0;
  parent[s] = 0;

  Q.push_back(s);
  
  while (!Q.empty()) {
    size_t vex = Q.front();
    Q.pop_front();
    color[vex] = GREY;

    for (Edge *edg = G[vex]; edg; edg = edg->next) {
      if (color[edg->vex] == WHITE) {
	color[edg->vex] = GREY;
	dist[edg->vex] = dist[vex] + 1;
	parent[edg->vex] = vex;
	Q.push_back(edg->vex);
      }
    }
    color[vex] = BLACK;
  }
}

int main()
{
  vector<Edge*> G;

  size_t vexnum;
  cin >> vexnum;
  getchar();
  G.resize(vexnum+1);

  size_t vex;
  Edge *edg;
  string line;
  istringstream in;
  size_t index = 0;
  while (getline(cin, line)) {
    index++;
    in.clear();
    in.str(line);
    while (in >> vex) {
      edg = new Edge;
      edg->vex = vex;
      edg->next = G[vex];
      G[index] = edg;
    }
  }

  for (vector<Edge*>::iterator it = G.begin(); it != G.end(); it++) {
    if (*it != NULL) {
      cout << (*it)->vex << endl;
    }
  }

  BFS(G);

  int max = 0;
  size_t maxIx = 0;
  for (size_t ix = 1; ix <= G.size()-1; ix++) {
    cout << dist[ix] << " ";
    if (dist[ix] > max) {
      max = dist[ix];
      maxIx = ix;
    }
  }
  cout << endl;

  cout << maxIx << " ";
  while (parent[maxIx] != 0) {
    cout << parent[maxIx] << " ";
    maxIx = parent[maxIx];
  }

  return 0;
}
