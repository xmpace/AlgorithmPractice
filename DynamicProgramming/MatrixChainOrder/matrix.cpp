#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void print_parenthe(int i, int j, vector<vector<size_t> > &s);

int main(int argc, char **argv)
{
  size_t num;
  cin >> num;

  vector<size_t> p;
  size_t tmp;
  for (int i = 0; i <= num; i++) {
    cin >> tmp;
    p.push_back(tmp);
  }

  vector<vector<size_t> > m;
  vector<vector<size_t> > s;
  m.reserve(num);
  s.reserve(num);
  for (int i = 0; i < num; i++) {
    m[i].reserve(num);
    s[i].reserve(num);
  }

  for (int i = 0; i < num; i++) {
    m[i][i] = 0;
  }

  for (int l = 1; l < num; l++) {
    for (int i = 0; i < num-l; i++) {
      int j = i + l;
      m[i][j] = -1;
      for (int k = i; k < j; k++) {
	if (m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1] < m[i][j]) {
	  m[i][j] = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
	  s[i][j] = k;
	}
      }
    }
  }

  cout << m[0][num-1] << endl;
  print_parenthe(0, num-1, s);
  return 0;
}

void print_parenthe(int i, int j, vector<vector<size_t> > &s)
{
  if (i == j) {
    cout << "A" << i+1;
  }
  else {
    cout << "(";
    print_parenthe(i, s[i][j], s);
    print_parenthe(s[i][j]+1, j, s);
    cout << ")";
  }
}
