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
static int W[MAX_VERTICES*MAX_VERTICES];
static int auxL[MAX_VERTICES*MAX_VERTICES];
static int auxR[MAX_VERTICES*MAX_VERTICES];

// local functions
int* extend_shortest_path(int *l, int vernum);
int* slow_all_pairs_shortest_paths(int vernum);

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
      W[i*MAX_VERTICES + j] = w;
    }
  }

#ifdef _DEBUG
  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      cout << W[i*MAX_VERTICES + j] << " ";
    }
    cout << endl;
  }
#endif

  int *result = NULL;
  result = slow_all_pairs_shortest_paths(vernum);

  // Output result
  
  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      cout << result[i*MAX_VERTICES + j] << "\t";
    }
    cout << endl;
  }
  

  return 0;
}


int* extend_shortest_path(int *l, int vernum)
{
  int *r = NULL;
  if (l == auxL) {
    r = auxR;
  } else {
    r = auxL;
  }

  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      r[i*MAX_VERTICES + j] = INT_MAX;
      for (int k = 0; k < vernum; k++) {
	if (l[i*MAX_VERTICES + k] != INT_MAX && W[k*MAX_VERTICES + j] != INT_MAX) {
	  if (l[i*MAX_VERTICES + k] + W[k*MAX_VERTICES + j] < r[i*MAX_VERTICES + j]) {
	    r[i*MAX_VERTICES + j] = l[i*MAX_VERTICES + k] + W[k*MAX_VERTICES + j];
	  }
	}
      }
    }
  }

  return r;
}

int* slow_all_pairs_shortest_paths(int vernum)
{
  int *l = W;
  for (int m = 1; m < vernum; m++) {
    l = extend_shortest_path(l, vernum);
  }
  return l;
}

