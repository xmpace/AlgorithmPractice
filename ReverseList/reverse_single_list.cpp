#include <iostream>
using namespace std;

void reverse_single_list();
void add_to_single_list(struct single_list_node *node);
void print_single_list(struct single_list_node *head);
void destroy_single_list();

struct single_list_node {
  int key;
  struct single_list_node *next;
};

struct single_list_node *single_list_head = NULL;

void reverse_single_list()
{
  struct single_list_node *current_point = NULL;
  struct single_list_node *next_point = single_list_head;
  struct single_list_node *third_point = next_point;
  
  while (third_point != NULL)
  {
    third_point = next_point->next;
    next_point->next = current_point;
    current_point = next_point;
    next_point = third_point;
  }

  single_list_head = current_point;
}

void add_to_single_list(struct single_list_node *node)
{
  node->next = single_list_head;
  single_list_head = node;
}

void print_single_list(struct single_list_node *head)
{
  while (head)
  {
    cout << head->key << " ";
    head = head->next;
  }
}

void destroy_single_list()
{
  struct single_list_node *p = NULL;
  while (single_list_head)
  {
    p = single_list_head;
    single_list_head = single_list_head->next;
    delete p;
  }
}
    
int main(int argc, char **argv)
{
  struct single_list_node *node;
  
  for (int i = 1; i < 20; i++)
  {
    node = new struct single_list_node;
    node->key = i;
    add_to_single_list(node);
  }
  
  print_single_list(single_list_head);
  cout << endl;

  reverse_single_list();

  print_single_list(single_list_head);
  cout << endl;

  destroy_single_list();

  return 0;
}
