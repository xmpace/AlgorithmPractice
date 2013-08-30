#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

static const int CHILD_NUM = 26;
static const int WORD_LENGTH = 11;

struct TrieNode {
  struct TrieNode* child[CHILD_NUM];
  bool end;
  int count;
};

static struct TrieNode* CreateTrieNode()
{
  struct TrieNode *trieNode = new struct TrieNode;
  trieNode->end = false;
  trieNode->count = 0;
  memset(trieNode->child, 0, sizeof(trieNode->child));
  return trieNode;
}

bool FindAndInsert(const string &str, struct TrieNode *trie)
{
  if (!trie) {
    return false;
  }

  int strSize = str.size();
  bool found = true;
  
  for (int i = 0; i < strSize; i++) {
    if (trie->child[str[i]-'a'] == NULL) {
      struct TrieNode *temp = CreateTrieNode();
      trie->child[str[i]-'a'] = temp;
      found = false;
    } else {
    
    }
    trie = trie->child[str[i]-'a'];
  }
  trie->end = true;
  trie->count++;

  return found;
}

bool Find(const string &str, const struct TrieNode *trie)
{
  string::size_type strSize = str.size();
  for (int i = 0; i < strSize; i++) {
    if (trie->child[str[i]-'a'] == NULL) {
      return false;
    }
    trie = (trie->child)[str[i]-'a'];
  }
  if (trie->end) {
    return true;
  }
  return false;
}

void DeleteTrie(struct TrieNode *trie)
{
  if (!trie) {
    return;
  }
  for (int i = 0; i < CHILD_NUM; i++) {
    DeleteTrie(trie->child[i]);
  }
  delete trie;
}

void DFS(struct TrieNode *trie, int layer, char *str)
{
  if (!trie) {
    return;
  }
  if (trie->end) {
    string word(str, str+layer+1);
    cout << trie->count << " " << word << endl;
  }
  for (int i = 0; i < CHILD_NUM; i++) {
    str[layer+1] = 'a' + i;
    DFS(trie->child[i], layer+1, str);
  }
}

// 采用深度优先搜索
void OutputStringAndCount(const struct TrieNode *trie)
{
  if (!trie) {
    return;
  }

  char str[WORD_LENGTH];
  for (int i = 0; i < CHILD_NUM; i++) {
    if (trie->child[i]) {
      str[0] = 'a'+i;
      DFS(trie->child[i], 0, str);
    }
  }
}

int main()
{
  string word;
  struct TrieNode *trie = CreateTrieNode();

  while (cin >> word) {
    bool ret = FindAndInsert(word, trie);
  }

  OutputStringAndCount(trie);

  // string obj("xiaomi");
  // bool ret = Find(obj, trie);
  // if (ret) {
  //   cout << "xiaomi is there!" << endl;
  // } else {
  //   cout << "not found" << endl;
  // }

  DeleteTrie(trie);

  return 0;
}
