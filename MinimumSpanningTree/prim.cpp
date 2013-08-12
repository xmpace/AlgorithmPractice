#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

typedef struct{
  int parent;
  int key;
} VEX;

typedef struct _EdgeNode {
  struct _EdgeNode *next;
  int vex;
  int w;
} EdgeNode;

int main()
{
  int m,b;
  cin >> m >> b;

  vector<EdgeNode*> G;
  int maxVex = 0;
  string line;
  getline(cin, line); // 去回车符
  if (b == 1) {
    for (int i = 0; i < m; i++) {
      int X, Y, W;
      getline(cin, line);
      istringstream in(line);
      in >> X >> Y >> W;
      if (G.size() < X+1) {
	G.resize(X+1);
      }

      EdgeNode *edgTmp = new EdgeNode;
      edgTmp->next = G[X];
      edgTmp->vex = Y;
      edgTmp->w = W;
      G[X] = edgTmp;

      if (X > maxVex) {
	maxVex = X;
      }
      if (Y > maxVex) {
	maxVex = Y;
      }
    }
    G.resize(maxVex+1);
  }



  return 0;
}
