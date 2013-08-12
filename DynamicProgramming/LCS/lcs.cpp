#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_lcs(string&, string&, vector<vector<int> >&, int, int);

int main(int argc, char **argv)
{
  string x, y;
  cin >> x >> y;

  int lengthx = x.size();
  int lengthy = y.size();
  vector<vector<int> > lcs;
  lcs.reserve(lengthx);
  for (int i = 0; i < lengthx; i++) {
    lcs[i].reserve(lengthy);
  }

  for (int i = 0; i < lengthx; i++) {
    if (x[i] == y[0]) {
      lcs[i][0] = 1;
    }
    else {
      lcs[i][0] = 0;
    }
  }

  for (int i = 0; i < lengthy; i++) {
    if (y[i] == x[0]) {
      lcs[0][i] = 1;
    }
    else {
      lcs[0][i] = 0;
    }
  }

  for (int i = 1; i < lengthx; i++) {
    for (int j = 1; j < lengthy; j++) {
      if (x[i] == y[j]) {
	lcs[i][j] = lcs[i-1][j-1] + 1;
      }
      else if (lcs[i-1][j] > lcs[i][j-1]) {
	lcs[i][j] = lcs[i-1][j];
      }
      else {
	lcs[i][j] = lcs[i][j-1];
      }
    }
  }

  cout << lcs[lengthx-1][lengthy-1] << endl;

  cout << "The longest common sequences is : " << endl;
  print_lcs(x, y, lcs, lengthx-1, lengthy-1);
  cout << endl;
  return 0;
}

void print_lcs(string &x, string &y, vector<vector<int> > &lcs, int i, int j)
{
  if (i < 0 || j < 0) {
    return;
  }
  else {
    if (x[i] == y[j]) {
      print_lcs(x, y, lcs, i-1, j-1);
      cout << x[i];
    }
    else {
      if (lcs[i][j-1] > lcs[i-1][j]) {
	print_lcs(x, y, lcs, i, j-1);
      }
      else {
	print_lcs(x, y, lcs, i-1, j);
      }
    }
  }
}
