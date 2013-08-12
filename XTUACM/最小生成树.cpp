#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Vertice {
  int vex;
  int rank;
  struct _Vertice *parent;
} Vertice;

typedef struct {
  Vertice *x;
  Vertice *y;
  int w;
} Edge;

//Local functions
static void link_set(Vertice *a, Vertice *b);
void make_set(Vertice *v);
Vertice* find_set(Vertice *v);
void union_set(Vertice *a, Vertice *b);

bool compare(Edge *a, Edge *b)
{
  return (a->w <= b->w);
}

void make_set(Vertice *v)
{
  v->parent = v;
  v->rank = 0;
}

Vertice* find_set(Vertice *v)
{
  if (v->parent != v) {
    v->parent = find_set(v->parent);
  }
  return v->parent;
}

void union_set(Vertice *a, Vertice *b)
{
  link_set(find_set(a), find_set(b));
}

void link_set(Vertice *a, Vertice *b)
{
  if (a->rank > b->rank) {
    b->parent = a;
  }
  else {
    a->parent = b;
  }

  if (a->rank == b->rank) {
    b->rank++;
  }    
}


int main()
{
  vector<Edge*> edg;
  int M, B;
  string line;

  cin >> M >> B;
  //  getline(cin, line); // 去掉回车符

  int X, Y, V;
  Edge *edgTmp;
  Vertice *ver;
  if (B == 1) {
    int maxVex = 0;
    for (int i = 0; i < M; i++) {
      getline(cin, line);
      istringstream in(line);
      cin >> X >> Y >> V;
      cout << X << " " << Y << " " << V << endl;
      if (X > maxVex) {
	maxVex = X;
      }
      else if (Y > maxVex) {
	maxVex = Y;
      }

      edgTmp = new Edge;

      ver = new Vertice;
      ver->vex = X;
      edgTmp->x = ver;
      make_set(ver);

      ver = new Vertice;
      ver->vex = Y;
      edgTmp->y = ver;
      make_set(ver);

      edgTmp->w = V;
      edg.push_back(edgTmp);
    }

    sort(edg.begin(), edg.end(), compare);

    int sum = 0;
    for (vector<Edge*>::iterator ix = edg.begin(); ix != edg.end(); ix++) {
      if (find_set((*ix)->x) != find_set((*ix)->y)) {
	sum += (*ix)->w;
	cout << (*ix)->w << endl;
	union_set((*ix)->x, (*ix)->y);
      }
    }

    cout << sum << endl;

  }

  return 0;
}
