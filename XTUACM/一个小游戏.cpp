#include <iostream>
#include <list>

using namespace std;

int main(int argc, char **argv)
{
  int instance;
  int n,m;

  cin >> instance;
  while (instance--) {
    cin >> n >> m;
    list<int> josephCircle;
    for (int i = 1; i <= n; i++) {
      josephCircle.push_back(i);
    }
    
    bool direction = true;
    list<int>::iterator it = josephCircle.begin();
    while (!josephCircle.empty()) {
      int interval = m;
      if (direction) { // 正方向
	while (--interval) {
	  it++;
	  if (it == josephCircle.end()) {
	    it = josephCircle.begin();
	  }
	}
	if (josephCircle.size() == 1) {
	  cout << *it;
	}
	it = josephCircle.erase(it);
      }
      else { // 反方向
	while (--interval) {
	  if (it == josephCircle.begin()) {
	    it = josephCircle.end();
	  }
	  it--;
	}
	if (josephCircle.size() == 1) {
	  cout << *it;
	}
	it = josephCircle.erase(it);
	if (it == josephCircle.begin()) {
	  it = josephCircle.end();
	  it--;
	}
      }
      if (direction) {
	direction = false;
      } else {
	direction = true;
      }
    }
    cout << endl;
  }
  return 0;
}
