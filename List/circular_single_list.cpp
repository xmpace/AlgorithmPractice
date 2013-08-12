#include <iostream>

using namespace std;

template <typename T>
class CircSingleList;

template <typename T>
class SingleListNode {
public:
  SingleListNode() : data(0), next(0) { }
private:
  T data;
  SingleListNode<T> *next;
public:
friend class CircSingleList<T>;
};

template <typename T>
class CircSingleList {
public:
  CircSingleList() : head(0), tail(0) { }

private:
  SingleListNode<T> *head;
  SingleListNode<T> *tail;

public: // 接口
  void insert(const T &value);
  T *find(const T &value) const;
  void print_list();
  void destroy();
  void reverse();
};

template <typename T>
void CircSingleList<T>::insert(const T &value) {
  SingleListNode<T> *node = new SingleListNode<T>();
  if (head == NULL) {
    head = tail = node;
    node->next = node;
    return;
  }
  node->data = value;
  node->next = head;
  tail->next = node;
  tail = node;
}

template <typename T>
T* CircSingleList<T>::find(const T &value) const {
  if (head == NULL) {
    return NULL;
  }
  SingleListNode<T> *p = head;
  if (p->data == value) {
    return p;
  }
  p = p->next;
  while (p != head) {
    if (p->data == value) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

template <typename T>
void CircSingleList<T>::destroy() {
  if (!head) {
    return;
  }
  SingleListNode<T> *p = head;
  while (p != tail) {
    head = p->next;
    delete p;
    p = head;
  }
  delete p;
  head = tail = NULL;
}

template <typename T>
void CircSingleList<T>::reverse() {
  if (!head) {
    return;
  }
  SingleListNode<T> *first = tail;
  SingleListNode<T> *second = head;
  SingleListNode<T> *third = second;
  while (third != tail) {
    third = third->next;
    second->next = first;
    first = second;
    second = third;
  }
  second->next = first;
  first = head;
  head = tail;
  tail = first;
}
    
template <typename T>
void CircSingleList<T>::print_list() {
  SingleListNode<T> *p = head;
  while (p != tail) {
    cout << p->data << " ";
    p = p->next;
  }
  (p == NULL) ? : (cout << p->data << endl);
}

int main(int argc, char **argv)
{
  CircSingleList<int> slist;
  for (int i = 0; i < 11; i++) {
    slist.insert(i);
  }
  
  slist.print_list();
  
  slist.reverse();
  
  slist.print_list();

  slist.destroy();

  return 0;
}

