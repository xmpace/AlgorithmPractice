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

// local functions
void floyd_warshall(int vernum);

int main()
{
  int vernum;
  cin >> vernum;

  string line;
  getline(cin, line); //      
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

  floyd_warshall(vernum);

  // Output Result
  for (int i = 0; i < vernum; i++) {
    for (int j = 0; j < vernum; j++) {
      cout << W[i][j] << "\t";
    }
    cout << endl;
  }

  return 0;
}

void floyd_warshall(int vernum)
{
  for (int k = 0; k < vernum; k++) {
    for (int i = vernum-1; i >= 0; i--) {
      for (int j = 0; j < vernum; j++) {
	if (W[i][k] != INT_MAX && W[k][j] != INT_MAX) {
	  if (W[i][k] + W[k][j] < W[i][j]) {
	    W[i][j] = W[i][k] + W[k][j];
	  }
	}
      }
    }
  }
}
