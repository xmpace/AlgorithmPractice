#include <iostream>
#include <vector>

using namespace std;
void recursive_select_activity(vector<int> &result, vector<int> &s,
			       vector<int> &f, int first, int last);
void iterate_select_activity(vector<int> &result, vector<int> &s,
			     vector<int> &f, int num);
void iterate_select_activity2(vector<int> &result, vector<int> &s,
			      vector<int> &f, int num);
int main(int argc, char **argv)
{
  int num;
  cin >> num;

  vector<int> s;
  vector<int> f;
  s.reserve(num+1);
  f.reserve(num+1);

  for (int i = 1; i <= num; i++) {
    cin >> s[i];
  }

  f[0] = 0;
  for (int i = 1; i <= num; i++) {
    cin >> f[i];
  }

  vector<int> result;
  //  recursive_select_activity(result, s, f, 0, num);
  // iterate_select_activity(result, s, f, num);
  iterate_select_activity2(result, s, f, num);

  cout << endl;
  for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}

void recursive_select_activity(vector<int> &result, vector<int> &s,
			       vector<int> &f, int first, int last)
{
  int m = first + 1;
  while (m <= last && s[m] < f[first]) {
    m++;
  }

  if (m <= last) { // 还有活动可选
    result.push_back(m);
    recursive_select_activity(result, s, f, m, last);
  }
  else {
    return;
  }
}

void iterate_select_activity(vector<int> &result, vector<int> &s,
			     vector<int> &f, int num)
{
  int i = 0;
  while (i < num) {
    int task = i + 1;
    while (task <= num && s[task] < f[i]) {
      task++;
    }

    if (task <= num) {
      result.push_back(task);
    }

    i = task;
  }
}

void iterate_select_activity2(vector<int> &result, vector<int> &s,
			     vector<int> &f, int num)
{
  int i = 1;
  result.push_back(i);
  for (int m = 2; m <= num; m++) {
    if (s[m] >= f[i]) {
      result.push_back(m);
      i = m;
    }
  }
}
