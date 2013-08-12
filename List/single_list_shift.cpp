#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
struct LinkNode {
  LinkNode *next;
  T data;
};

// local functions
void print_single_list();
void shift_single_list(int m);
void initialize_single_list();

// global variables
LinkNode<int> *head = NULL;

int main()
{
  initialize_single_list();

  print_single_list();

  int m;
  cin >> m;

  shift_single_list(m);

  print_single_list();
  return 0;
}

void initialize_single_list()
{
  LinkNode<int> *tmp;
  int data;
  string line;
  getline(cin, line);
  istringstream in(line);
  while (in >> data) {
    tmp = new LinkNode<int>;
    tmp->next = head;
    head = tmp;
    tmp->data = data;
  }
}

void shift_single_list(int m)
{
  LinkNode<int> *current = head;
  LinkNode<int> *tail = NULL;
  int listLength = 0;
  while (current != NULL) {
    listLength++;
    tail = current;
    current = current->next;
  }

  if (listLength == 0) {
    return;
  }
  m = m % listLength;
  m = listLength - m;
  LinkNode<int> *prev = NULL;
  current = head;

  while (m--) {
      prev = current;
      current = current->next;
  }

  prev->next = NULL;
  tail->next = head;
  head = current;
}

void print_single_list()
{
  LinkNode<int> *current = head;
  while (current) {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}
