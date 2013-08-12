// 二叉查找树测试用例

template <typename T>
class SearchTree;

template <typename T>
void BFS_print(const SearchTree<T> &tree );

template <typename T>
class TreeItem {
public:
  TreeItem() : _value(0), _lchild(0), _rchild(0) { }

public:
  T _value;
  TreeItem<T> *_lchild;
  TreeItem<T> *_rchild;

public:
friend class SearchTree<T>;
friend void BFS_print<T>(const SearchTree<T>&);
};

template <typename T>
class SearchTree {
public:
  SearchTree() : root(0), height(0) { }
  ~SearchTree() { destroy(); }

public: // 成员变量
  TreeItem<T> *root;
  int height;

private: // 成员函数
  void destroy();

public: // 接口
  void insert(const T &value);
  TreeItem<T>* find(const T &value) const;
  // delete方法以后再实现

friend void BFS_print<T>(const SearchTree<T>&);
};

template <typename T>
void SearchTree<T>::destroy() {
  // 以后再实现
}

template <typename T>
void SearchTree<T>::insert(const T &value) {
  TreeItem<T> *p = 0;
  TreeItem<T> *q = root;
  int num = 1;
  while (q) {
    num++;
    if (num > height) {
      height = num;
    }
    p = q;
    if (value < q->_value) {
      q = q->_lchild;
    } else {
      q = q->_rchild;
    }
  }
  q = new TreeItem<T>();
  q->_value = value;
  if (!p) {
    root = q;
    return;
  }
  else if (q->_value < p->_value) {
    p->_lchild = q;
  }
  else {
    p->_rchild = q;
  }
}

template <typename T>
TreeItem<T>* SearchTree<T>::find(const T &value) const {
  TreeItem<T> *p = root;
  while (!p) {
    if (p->_value == value) {
      return p;
    }
    else if (value < p->_value) {
      p = p->_lchild;
    }
    else {
      p = p->_rchild;
    }
  }
  return 0;
}

#include <iostream>
#include <queue>
using namespace std;

template <typename T>
void BFS_print(const SearchTree<T> &tree ) {
  queue<TreeItem<T>*> que;
  que.push(tree.root);
  while (!que.empty()) {
    TreeItem<T>* it = que.front();
    if (it->_lchild) {
      que.push(it->_lchild);
    }
    if (it->_rchild) {
      que.push(it->_rchild);
    }
    cout << it->_value << " ";
    que.pop();
  }
  cout << endl;
}

template <typename T>  
class TreePrinter {
public:
  TreePrinter() {
    currentItem = new queue<TreeItem<T>*>();
    childItem = new queue<TreeItem<T>*>();
    currentPos = new queue<struct POS>();
    childPos = new queue<struct POS>();
  }
  ~TreePrinter() {
    delete currentItem;
    delete childItem;
    delete currentPos;
    delete childPos;
  }

private:
  struct POS {
    int row;
    int col;
  };
  queue<TreeItem<T>*> *currentItem;
  queue<TreeItem<T>*> *childItem;
  queue<struct POS> *currentPos;
  queue<struct POS> *childPos;
  vector<int> linkPos; // 上一层节点的col坐标，用来绘制连接符用

private:
  void print_spaces(int num);

public:
  void print(TreeItem<T> *root, size_t height);
};

template <typename T>
void TreePrinter<T>::print_spaces(int num) {
  if (num < 0)
    return;
  while (num--) {
    cout << " ";
  }
}

template <typename T>
void TreePrinter<T>::print(TreeItem<T> *root, size_t height) {
  currentItem->push(root);
  struct POS pos, tmpPos;
  int layer = 1;
  pos.row = 1;
  pos.col = (height - 1)*height;
  currentPos->push(pos);

  while (layer <= height) {
    // 打印结点层
    int prevCol = -1;
    while (!currentItem->empty()) {
      TreeItem<T> *cur = currentItem->front();
      pos = currentPos->front();
      currentItem->pop();
      currentPos->pop();

      // 打印当前结点与同行上一结点的空格距离
      print_spaces(pos.col - prevCol - 1);
      // 打印当前结点数据
      cout << cur->_value;
      // 记录当前结点的位置到连接符队列，以供接下来打印连接符
      linkPos.push_back(pos.col);
      // 当前结点的子结点入队列
      if (cur->_lchild) {
	childItem->push(cur->_lchild);
	tmpPos.row = pos.row + 1;
	// tmpPos.col = pos.col - interval - 1;
	// interval = 2*(height - pos.row) - 1;
	tmpPos.col = pos.col - 2*(height - pos.row);
	childPos->push(tmpPos);
      }
      if (cur->_rchild) {
	childItem->push(cur->_rchild);
	tmpPos.row = pos.row + 1;
	tmpPos.col = pos.col + 2*(height - pos.row) - 1;
	childPos->push(tmpPos);
      }
      prevCol = pos.col;
    }

    // 交换当前结点队列与子结点队列
    queue<TreeItem<T>*> *tmp = currentItem;
    currentItem = childItem;
    childItem = tmp;
    queue<struct POS> *tmp1 = currentPos;
    currentPos = childPos;
    childPos = tmp1;

    cout << endl;

    // 打到最后一行结点就退出，不打符号
    if (layer == height) {
      return;
    }

    // 打印连接符
    int interval = (height - layer)*2 - 1;
    int spacenum = 0;
    while (interval--) {
      int prevCcol = -1;
      vector<int>::iterator it = linkPos.begin();
      print_spaces(spacenum+1);
      while (it != linkPos.end()) {
	// 打印符号之前的空格
	print_spaces(*it - spacenum*2 - 1 - prevCcol - 2);

	cout << "/";
	print_spaces(spacenum*2+1);
	cout << "\\";
	prevCcol = *it;      
	it++;
      }
      spacenum += 1;
      cout << endl;
    }
    // 打印完两层之间的符号就清除掉
    linkPos.clear();
    layer++;
  }
}

int main(int argc, char **argv)
{
  int _data[] = {12, 6, 24, 3, 8, 16, 30, 1, 5, 7, 9, 20, 23, 26, 32};
  vector<int> data(_data, _data + sizeof(_data)/sizeof(int));
  SearchTree<int> tree;

  vector<int>::iterator it = data.begin();
  for (; it != data.end(); it++) {
    tree.insert(*it);
  }

  BFS_print<int>(tree);
  cout << endl;
  cout << tree.height << endl;

  TreePrinter<int> tree_printer;
  tree_printer.print(tree.root, tree.height);

  return 0;
}

