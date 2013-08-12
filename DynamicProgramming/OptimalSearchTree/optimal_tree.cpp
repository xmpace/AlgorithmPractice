#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int print_tree_struct(vector<vector<int> > &root, int i, int j);
void print_tree(vector<vector<int> > &root, int i, int j, int p);
int main(int argc, char **argv)
{
  int num;
  cin >> num;

  vector<double> p;
  vector<double> q;
  p.reserve(num+1);
  q.reserve(num+1);

  for (int i = 1; i <= num; i++) {
    cin >> p[i];
  }

  for (int i = 0; i <= num; i++) {
    cin >> q[i];
  }

  vector<vector<double> > e, w;
  e.reserve(num+2);
  w.reserve(num+2);
  for (int i = 0; i <= num+1; i++) {
    e[i].reserve(num+1);
    w[i].reserve(num+1);
  }

  for (int i = 0; i <= num; i++) {
    e[i+1][i] = q[i];
    w[i+1][i] = q[i];
  }

  vector<vector<int> > root; // 记录每个子树根结点
  root.reserve(num+1);
  for (int i = 0; i <= num; i++) {
    root[i].reserve(num+1);
  }

  for (int l = 0; l < num; l++) {
    for (int i = 1; i <= num - l; i++) {
      int j = i + l;
      e[i][j] = 1.0e308;
      w[i][j] = w[i][j-1] + p[j] + q[j];
      for(int r = i; r <= j; r++) {
	if (e[i][r-1] + e[r+1][j] + w[i][j] < e[i][j]) {
	  e[i][j] = e[i][r-1] + e[r+1][j] + w[i][j];
	  root[i][j] = r;
	}
      }
    }
  }

  cout << e[1][num] << endl;
  //  cout << root[1][num] << "是根" << endl;
  //  print_tree_struct(root, 1, num);
  print_tree(root, 1, num, 0);

  return 0;
}

int print_tree_struct(vector<vector<int> > &root, int i, int j)
{
  int lchild, rchild;
  if (i > j) {
    return 0;
  }
  rchild = print_tree_struct(root, root[i][j]+1, j);
  lchild = print_tree_struct(root, i, root[i][j]-1);
  if (lchild) {
    cout << lchild << "是" << root[i][j] << "的左孩子";
    cout << endl;
  }

  if (rchild) {
    cout << rchild << "是" << root[i][j] << "的右孩子";
    cout << endl;
  }
  return root[i][j];
}

void print_tree(vector<vector<int> > &root, int i, int j, int p)
{
  int cur;
  if (p == 0) {
    cur = root[i][j];
    cout << "p" << cur << " is root." << endl;
    print_tree(root, i, cur-1, cur);
    print_tree(root, cur+1, j, cur);
  }
  else {
    if (i > j) {
      if (j < p) {
	cout << "d" << j << " is left child of " << p << endl;
      }
      else if (i > p) {
	cout << "d" << j << " is right child of " << p << endl;
      }
    }
    else {
      cur = root[i][j];
      if (j < p) {
	cout << "p" << cur << " is left child of " << p << endl;
      }
      else if (i > p) {
	cout << "p" << cur << " is right child of " << p << endl;
      }
      print_tree(root, i, cur-1, cur);
      print_tree(root, cur+1, j, cur);
    }
  }
}
