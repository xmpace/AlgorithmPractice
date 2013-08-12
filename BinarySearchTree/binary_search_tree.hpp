#include <iostream>

template <typename T>
class BinarySearchTree;

template <typename T>
class TreeItem {
public:
  TreeItem(const T &value) : _value(value), _left(0), 
			     _right(0), _parent(0) { }

public:
  TreeItem<T> *_left;
  TreeItem<T> *_right;
  TreeItem<T> *_parent;
  T _value;
};

template <typename T>
class BinarySearchTree {
public:
  BinarySearchTree() : root(0) { }
  ~BinarySearchTree() { destroy(); }

private:
  void _insert(TreeItem<T> *item);
  void destroy();
  void _travel(TreeItem<T> *);

public:
  void insert(const T &value);
  TreeItem<T>* successor(TreeItem<T>*);
  TreeItem<T>* erase(TreeItem<T> *item);
  TreeItem<T>* find(const T &value);
  TreeItem<T>* maximum(TreeItem<T>*);
  TreeItem<T>* minimum(TreeItem<T>*);
  bool empty();
  void travel();

public:
  TreeItem<T> *root;
};

template <typename T>
void BinarySearchTree<T>::_insert(TreeItem<T> *item) {
  TreeItem<T> *p = 0;
  TreeItem<T> *q = root;
  while (q) {
    p = q;
    if (item->_value < q->_value) {
      q = q->_left;
    }
    else {
      q = q->_right;
    }
  }
  q = item;
  if (!p) {
    root = q;
  }
  else {
    q->_parent = p;
    if (q->_value < p->_value) {
      p->_left = q;
    }
    else {
      p->_right = q;
    }
  }
}
  
template <typename T>
TreeItem<T>* BinarySearchTree<T>::successor(TreeItem<T> *item) {
  TreeItem<T> *q = item;
  TreeItem<T> *p = q->_parent;
  if (q->_right) {
    return minimum(q->_right);
  }
  else {
    while (p != 0 && p->_right == q) {
      q = p;
      p = p->_parent;
    }
    return p;
  }
}
    
template <typename T>
void BinarySearchTree<T>::destroy() {
  while (!empty()) {
    erase(root);
  }
}

template <typename T>
void BinarySearchTree<T>::insert(const T &value) {
  TreeItem<T> *item = new TreeItem<T>(value);
  _insert(item);
}

template <typename T>
TreeItem<T>* BinarySearchTree<T>::erase(TreeItem<T> *item) {
  TreeItem<T> *y = 0;
  TreeItem<T> *x = 0;
  if (item->_left == 0 || item->_right == 0) {
    y = item;
  }
  else {
    y = successor(item);
  }
  if (y->_left != 0) {
    x = y->_left;
  }
  else {
    x = y->_right;
  }
  // 把x接到y的父结点上
  if (x) {
    x->_parent = y->_parent;
  }
  if (y->_parent == 0) {
    root = x;
  }
  else {
    if (y == y->_parent->_left) {
      y->_parent->_left = x;
    }
    else {
      y->_parent->_right = x;
    }
  }
  if (item != y) {
    item->_value = y->_value;
    x = item;
  }
  return x;
}

template <typename T>
TreeItem<T>* BinarySearchTree<T>::find(const T &value) {
  TreeItem<T> *item = root;
  while (!item) {
    if (item->_value == value) {
      return item;
    }
    if (value < item->_left) {
      item = item->_left;
    }
    else {
      item = item->_right;
    }
  }
  return 0;
}

template <typename T>
TreeItem<T>* BinarySearchTree<T>::maximum(TreeItem<T> *item) {
  TreeItem<T> *p = 0;
  TreeItem<T> *q = item;
  while (q) {
    p = q;
    q = q->_right;
  }
  return p;
}

template <typename T>
TreeItem<T>* BinarySearchTree<T>::minimum(TreeItem<T> *item) {
  TreeItem<T> *p = 0;
  TreeItem<T> *q = item;
  while(q) {
    p = q;
    q = q->_left;
  }
  return p;
}

template <typename T>
bool BinarySearchTree<T>::empty() {
  if (!root) {
    return true;
  }
  else {
    return false;
  }
}

template <typename T>
void BinarySearchTree<T>::travel() {
  _travel(root);
}

template <typename T>
void BinarySearchTree<T>::_travel(TreeItem<T> *p) {
  if (!p) {
    return;
  }
  _travel(p->_left);
  std::cout << p->_value << " ";
  _travel(p->_right);
}
