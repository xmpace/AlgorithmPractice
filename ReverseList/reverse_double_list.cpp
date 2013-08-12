#include <iostream>
using namespace std;


struct double_list_node {
  int key;
  struct double_list_node *next;
  struct double_list_node *prev;
};

static struct double_list_node *double_list_head = NULL;

void add_to_double_list(struct double_list_node *node)
{
  if (!double_list_head) {
    node->next = node->prev = NULL;
    double_list_head = node;
    return;
  }
  node->next = double_list_head;
  node->prev = NULL;
  double_list_head->prev = node;
  double_list_head = node;
}

void destroy()
{
  struct double_list_node *p = NULL;
  while (double_list_head) {
    p = double_list_head;
    double_list_head = double_list_head->next;
    if (double_list_head)
      double_list_head->prev = NULL;
    delete p;
  }
}

void reverse_double_list()
{
  struct double_list_node *first = NULL;
  struct double_list_node *second = double_list_head;
  struct double_list_node *third = double_list_head;

  while (third) {
    third = third->next;
    second->next = first;
    second->prev = third;
    first = second;
    second = third;
  }
  double_list_head = first;
}

void print_double_list()
{
  struct double_list_node *p = double_list_head;
  while (p) {
    cout << p->key << " ";
    p = p->next;
  }
}

int main(int argc, char **argv)
{
  struct double_list_node *p;
  
  for (int i = 0; i < 31; i++) {
    p = new struct double_list_node;
    p->key = i;
    add_to_double_list(p);
  }
  
  print_double_list();
  cout << endl;

  reverse_double_list();

  print_double_list();
  cout << endl;

  destroy();

  return 0;
}
