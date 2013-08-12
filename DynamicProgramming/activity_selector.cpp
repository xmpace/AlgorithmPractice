// #include <iostream>
// #include <vector>

// using namespace std;
// int print_activity(vector<vector<int> > &act, int first, int last);
// int main(int argc, char **argv)
// {
//   int num;
//   cin >> num;

//   vector<int> s;
//   vector<int> f;
//   s.reserve(num+1);
//   f.reserve(num+1);

//   // 输入s和f
//   f[0] = 0;
//   for (int i = 1; i <= num; i++) {
//     cin >> s[i];
//   }

//   for (int i = 1; i <= num; i++) {
//     cin >> f[i];
//   }

//   vector<vector<int> > c;
//   c.reserve(num+1);
//   for (int i = 0; i <= num; i++) {
//     c[i].reserve(num+1);
//   }

//   for (int i = 0; i <= num; i++) {
//     c[i][i] = 0;
//   }

//   for (int i = 0; i < num; i++) {
//     if (s[i+1] >= f[i]) {
//       c[i][i+1] = 1;
//     }
//   }

//   vector<vector<int> > act;
//   act.resize(num+1);
//   for (int i = 0; i <= num; i++) {
//     act[i].resize(num+1);
//   }

//   for (int l = 2; l <= num; l++) {
//     for (int i = 0; i <= num - l; i++) {
//       int j = i+l;
//       if (s[j] >= f[i]) {
// 	c[i][j] = 1;
//       }
//       else {
// 	c[i][j] = 0;
//       }
//       for (int k = i+1; k < j; k++) {
// 	if (s[k] >= f[i]) {
//   	  if (c[i][k] + c[k][j] > c[i][j]) {
//   	    c[i][j] = c[i][k] + c[k][j];
//   	    act[i][j] = k;
//   	  }
// 	}
//       }
//     }
//   }

//   cout << act[0][num] << endl;
//   //  print_activity(act, 0, num);
//   // for (int i = 0; i <= num; i++) {
//   //   for (int j = 0; j <= num; j++) {
//   //     cout << c[i][j] << "\t";
//   //     if (j == num) {
//   // 	cout << endl;
//   //     }
//   //   }
//   // }


//   return 0;
// }

// int print_activity(vector<vector<int> > &act, int first, int last)
// {
//   int tmp = act[first][last];
//   if (tmp == 0) {
//     return 0;
//   }
//   cout << tmp << endl;
//   print_activity(act, tmp,last);
//   print_activity(act, first, tmp);
// }


#include <iostream>
#include <vector>

using namespace std;
void print_activity(vector<vector<int> > &act, int first, int last);
int main(int argc, char **argv)
{
  int num;
  cin >> num;

  vector<int> s;
  vector<int> f;
  s.reserve(num+2);
  f.reserve(num+2);

  // 输入s和f
  f[0] = 0;
  s[num+1] = 0x7FFFFFFF;
  for (int i = 1; i <= num; i++) {
    cin >> s[i];
  }

  for (int i = 1; i <= num; i++) {
    cin >> f[i];
  }

  vector<vector<int> > c;
  c.reserve(num+2);
  for (int i = 0; i <= num+1; i++) {
    c[i].reserve(num+2);
  }

  for (int i = 0; i <= num+1; i++) {
    c[i][i] = 0;
  }

  vector<vector<int> > act;
  act.resize(num+2);
  for (int i = 0; i <= num+1; i++) {
    act[i].resize(num+2);
  }

  for (int l = 1; l <= num+1; l++) {
    for (int i = 0; i <= num + 1 - l; i++) {
      int j = i + l;
      c[i][j] = 0;
      for (int k = i+1; k < j; k++) {
	if (s[k] >= f[i] && f[k] <= s[j]) {
	  if (c[i][k] + c[k][j] + 1 > c[i][j]) {
	    c[i][j] = c[i][k] + c[k][j] + 1;
	    act[i][j] = k;
	  }
	}
      }
    }
  }

  cout << c[0][num+1] << endl;

  print_activity(act, 0, num+1);
  cout << endl;
  return 0;
}

void print_activity(vector<vector<int> > &act, int first, int last)
{
  int cur = act[first][last];
  if (cur == 0) {
    return;
  }
  print_activity(act, first, cur);
  cout << cur << " ";
  print_activity(act, cur, last);
}
