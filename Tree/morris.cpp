#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// data structurers
template <typename T>
struct TreeNode {
  TreeNode *left;
  TreeNode *right;
  T data;
};

// global variables
TreeNode<int> *root;

// local functions
void construct_bst();
template <typename T>
void insert_to_bst(TreeNode<T> *node);
void print_bst();
template <typename T>
void inorder_traverse_bst(TreeNode<T> *node);
void morris_inorder_traverse_bst();
void morris_preorder_traverse_bst();

int main()
{
  construct_bst();

  print_bst();

  morris_inorder_traverse_bst();

  morris_preorder_traverse_bst();

  return 0;
}

void construct_bst()
{
  int data;
  while (cin >> data) {
    TreeNode<int> *tmp = new TreeNode<int>;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    insert_to_bst(tmp);
  }

}

template <typename T>
void insert_to_bst(TreeNode<T> *node)
{
  if (root == NULL) {
    root = node;
    return;
  }

  TreeNode<T> *current = root;
  TreeNode<T> *parent = NULL;
  while (current) {
    parent = current;
    if (node->data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (node->data < parent->data) {
    parent->left = node;
  }
  else {
    parent->right = node;
  }
}

void print_bst()
{
  // Inorder traverse BST
  inorder_traverse_bst(root);
  cout << endl;
}

template <typename T>
void inorder_traverse_bst(TreeNode<T> *node)
{
  if (!node) {
    return;
  }
  inorder_traverse_bst(node->left);
  cout << node->data << " ";
  inorder_traverse_bst(node->right);
}

void morris_inorder_traverse_bst()
{
  TreeNode<int> *current = root;
  TreeNode<int> *tmp;
  while (current) {
    if (current->left == NULL) {
      cout << current->data << " ";
      current = current->right;
    }
    else {
      tmp = current->left;
      while (tmp->right != NULL && tmp->right != current) {
	tmp = tmp->right;
      }
      if (tmp->right == NULL) {
	tmp->right = current;
	current = current->left;
      } else if (tmp->right == current) {
	tmp->right = NULL;
	cout << current->data << " ";
	current = current->right;
      }
    }
  }
  cout << endl;
}

void morris_preorder_traverse_bst()
{
  TreeNode<int> *current = root;
  TreeNode<int> *tmp;

  while (current) {
    if (current->left == NULL) {
      cout << current->data << " ";
      current = current->right;
    }
    else {
      tmp = current->left;
      while (tmp->right != NULL && tmp->right != current) {
	tmp = tmp->right;
      }
      if (tmp->right == NULL) {
	tmp->right = current;
	cout << current->data << " ";
	current = current->left;
      }
      else if (tmp->right == current) {
	tmp->right = NULL;
	current = current->right;
      }
    }
  }
  cout << endl;
}

// 暂时作废
void morris_postorder_traverse_bst()
{
  TreeNode<T> *current = root;
  TreeNode<T> *tmp;
  while (current) {
    if (current->left != NULL) {
      tmp = current->left;
      while (tmp->right != NULL && tmp->right != current) {
	tmp = tmp->right;
      }
      if (tmp->right == NULL) {
	tmp->right = current;
	current = current->left;
      } else if (tmp->right == current) {
	tmp->right = NULL;
	// traverse right side
      }
    }
  }
}
