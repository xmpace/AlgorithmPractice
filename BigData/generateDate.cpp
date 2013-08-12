#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

// macros
#define NUM 100000000

int main(int argc, char **argv)
{
  int size = NUM;

  if (argc == 2) {
    size = atoi(argv[1]);
  }
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    cout << rand() << endl;
  }

  return 0;
}
