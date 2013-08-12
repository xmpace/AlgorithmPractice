#include <iostream>
#include <vector>

using namespace std;

void optimised_path(vector<int> &l1, vector<int> &l2, int station, int stanum);
int main(int argc, char **argv)
{
  int s1,s2;
  int e1,e2;
  int num; // 装配线条数
  cin >> s1 >> s2;
  cin >> e1 >> e2;
  cin >> num;

  vector<int> a1, a2, t1, t2;
  int tmp;
  for (int i = 0; i < num; i++) {
    cin >> tmp;
    a1.push_back(tmp);
  }

  for (int i = 0; i < num; i++) {
    cin >> tmp;
    a2.push_back(tmp);
  }

  for (int i = 0; i < num-1; i++) {
    cin >> tmp;
    t1.push_back(tmp);
  }

  for(int i = 0; i < num-1; i++) {
    cin >> tmp;
    t2.push_back(tmp);
  }

  vector<int> f1,f2,l1,l2;
  f1.reserve(num);
  f2.reserve(num);
  l1.reserve(num);
  l2.reserve(num);

  f1[0] = s1+a1[0];
  f2[0] = s2+a2[0];

  for (int i = 1; i < num; i++) {
    if (f2[i-1]+t2[i-1]+a1[i] < f1[i-1]+a1[i]) {
      f1[i] = f2[i-1]+t2[i-1]+a1[i];
      l1[i] = 2;
    }
    else {
      f1[i] = f1[i-1]+a1[i];
      l1[i] = 1;
    }

    if (f1[i-1]+t1[i-1]+a2[i] < f2[i-1]+a2[i]) {
      f2[i] = f1[i-1]+t1[i-1]+a2[i];
      l2[i] = 1;
    }
    else {
      f2[i] = f2[i-1]+a2[i];
      l2[i] = 2;
    }
  }

  int fOptm;
  int lOptm;
  if (f1[num-1] + e1 < f2[num-1] + e2) {
    fOptm = f1[num-1] + e1;
    lOptm = 1;
  }
  else {
    fOptm = f2[num-1] + e2;
    lOptm = 2;
  }

  cout << "The minimum cost is : " << fOptm << endl;
  cout << "The optimised path is : " << endl;
  optimised_path(l1, l2, num-1, lOptm);

  return 0;
}

void optimised_path(vector<int> &l1, vector<int> &l2, int station, int stanum)
{
  if (station < 0)
    return;

  if (stanum == 1) {
    optimised_path(l1, l2, station-1, l1[station]);
  }
  else if (stanum == 2) {
    optimised_path(l1, l2, station-1, l2[station]);
  }
  cout << "station :" << station+1 << " line: " << stanum << endl;
}
