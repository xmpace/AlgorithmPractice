

struct _Node {
  int key;
  Node *left;
  Node *right;
  Node *parent;
};

typedef struct _Node Node;

void inoder_tree_walk(Node *T)
{
  if (T == NULL)
    return;
  inoder_tree_walk(T->left);
  cout << T->key << " ";
  inoder_tree_walk(T->right);
}

Node* tree_search(Node *T, int key)
{
  if (T == NULL || T->key == key)
    return T;
  if (key < T->key)
    return tree_search(T->left, key);
  else
    return tree_search(T->right, key);
}

Node* tree_minimum(Node *T)
{
  while (T->left != NULL)
    T = T->left;
  return T;
}

Node* tree_maximum(Node *T)
{
  while (T->right != NULL)
    T = T->right;
  return T;
}

Node* tree_successor(Node *T)
{
  if (T->right != NULL)
    return tree_minimum(T->right);
  
  Node *parent = T->parent;
  while (parent && parent->left != T)
  {
    T = parent;
    parent = T->parent;
  }
  return parent;
}

void tree_insert(Node *T, Node *z)
{
  Node *p = NULL;
  while (T)
  {
    p = T;
    if (z->key < T->key)
      T = T->left;
    else
      T = T->right;
  }
  
  if (p == NULL)
    T = z;
  else if (z->key < p->key)
    p->left = z;
  else
    p->right = z;
  z->parent = p;
}

Node* tree_delete(Node *T, Node *z)
{
  Node *p, *x;

  if (z->left == NULL || z->right == NULL)
    p = z;
  else
    p = tree_successor(z);

  if (p->left != NULL)
    x = p->left;
  else
    x = p->right;
  
  if (x != NULL)
  {
    x->parent = p->parent;
  }
  if (p->parent != NULL)
  {
    if (p->parent->left == p)
      p->parent->left = x;
    else
      p->parent->right = x;
  }
  else
  {
    T = x;
  }

  if (p != z)
    z->key = p->key;
  
  return p;
}
