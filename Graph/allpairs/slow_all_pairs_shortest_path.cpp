#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

// Conditional Compiles
#define _DEBUG

// macros
#define MAX_VERTICES 1000

// static variables
static int W[MAX_VERTICES][MAX_VERTICES];
static int auxL[MAX_VERTICES][MAX_VERTICES];
static int auxR[MAX_VERTICES][MAX_VERTICES];

// local functions
int (*extend_shortest_path(int (*)[MAX_VERTICES], int vernum))[MAX_VERTICES];
int (*slow_all_pairs_shortest_paths(int vernum))[MAX_VERTICES];

int main()
{
  int vernum;
  cin >> vernum;

  string line;
  getline(cin, line); // 去掉回车符
  int w;
  for (int i = 0; i < vernum; i++) {
    getline(cin, line);
    istringstream in(line);
    for (int j = 0; j < vernum; j++) {
      in >> w;
      if (i != j && w == 0) {
	w = INT_MAX;
      }
      W[i][j] = w;
    }
  }

#ifdef _DEBUG
  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      cout << W[i][j] << " ";
    }
    cout << endl;
  }
#endif

  int (*result)[MAX_VERTICES];
  result = slow_all_pairs_shortest_paths(vernum);

  // Output result
  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      cout << result[i][j] << "\t";
    }
    cout << endl;
  }

  return 0;
}

int (*extend_shortest_path(int (*l)[MAX_VERTICES], int vernum))[MAX_VERTICES]
{
  int (*r)[MAX_VERTICES] = NULL;
  if (l == &auxL[0]) {
    r = auxR;
  } else {
    r = auxL;
  }

  for (int i = vernum-1; i >= 0; i--) {
    for (int j = 0; j < vernum; j++) {
      r[i][j] = INT_MAX;
      for (int k = 0; k < vernum; k++) {
	if (l[i][k] != INT_MAX && W[k][j] != INT_MAX) {
	  if (l[i][k] + W[k][j] < r[i][j]) {
	    r[i][j] = l[i][k] + W[k][j];
	  }
	}
      }
    }
  }

  return r;
}

int (*slow_all_pairs_shortest_paths(int vernum))[MAX_VERTICES]
{
  int (*l)[MAX_VERTICES] = W;
  for (int m = 1; m < vernum; m++) {
    l = extend_shortest_path(l, vernum);
  }
  return l;
}
