#include "binary_search_tree.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
  int _data[] = {30, 20, 40, 10, 25, 35, 45};
  vector<int> data(_data, _data + sizeof(_data) / sizeof(int));
  BinarySearchTree<int> tree;
  for (vector<int>::iterator it = data.begin(); it != data.end(); it++) {
    tree.insert(*it);
  }
  TreeItem<int> *p = tree.minimum(tree.root);
  cout << "The minimum data is " << p->_value << endl;
  p = tree.maximum(tree.root);
  cout << "The maximum data is " << p->_value << endl;
  cout << "Successor " << tree.successor(tree.root)->_value << endl;

  tree.travel();
  cout << endl;

  BinarySearchTree<int> tree2;
  for (int i = 0; i < 100; i++) {
    tree2.insert(i);
  }
  tree2.travel();
  cout << endl;
  return 0;
}
