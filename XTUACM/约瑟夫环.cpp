#include <iostream>
#include <list>
using namespace std;

int main(int argc, char **argv)
{
  int n, m;
  cin >> n;
  cin >> m;
  
  list<int> josephCircle;
  for (int i = 1; i <= n; i++) {
    josephCircle.push_back(i);
  }

  list<int>::iterator it = josephCircle.begin();
  while (!josephCircle.empty()) {
    int interval = m;
    while (--interval) {
      it++;
      if (it == josephCircle.end()) {
	it = josephCircle.begin();
      }
    }
    cout << *it;
    it = josephCircle.erase(it);
    if (josephCircle.size() != 0) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}
