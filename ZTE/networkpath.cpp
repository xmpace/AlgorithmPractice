#include <iostream>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <fstream>
using namespace std;

// conditional compiles
#define _DEBUG

// data structures
typedef struct _EdgeNode {
  struct _EdgeNode *next;
  int ver;
} EdgeNode;

typedef struct {
  int u;
  int v;
} Edge;

enum COLOR {WHITE = 0, BLACK};

// constant variables
const int N = 5000;

//global variables
EdgeNode* G[N+1] = {0,};
COLOR color[N+1] = {WHITE,};
int parent[N+1] = {0,};
queue<int> Q;
int *main_point = NULL;
int main_path_length = 0;
Edge *main_edge = NULL;
ofstream outfile;

// command lines
char *input_filename = NULL;
char *output_filename = NULL;
int start_point = 0;
int end_point = 0;
int condition = 1;

// local functions
void print_path(int pt);
void get_path();
void get_argv(char **argv);
void get_main_path();
bool get_backup_path();
bool is_not_mainpt(int pt);
void record_main_path();
void get_main_path_length();
bool is_not_maineg(int u, int v);

int main(int argc, char **argv)
{
  // 获取命令行参数
  get_argv(argv);

  ifstream infile(input_filename);

  if (!infile) {
    cerr << "error: unable to open input file: "
	 << input_filename << endl;
    return -1;
  }

  string line;
  getline(infile, line);   // 去掉第一行没用的数据
  int u, v;
  char c;
  EdgeNode *edge = NULL;
  while (infile >> u >> c >> v) {
    edge = new EdgeNode;
    edge->ver = v;
    edge->next = G[u];
    G[u] = edge;
    edge = new EdgeNode;
    edge->ver = u;
    edge->next = G[v];
    G[v] = edge;
  }

  // 计算主用和备用路径
  get_path();

  // release memory
  delete[] main_point;
  delete[] main_edge;
  for (int i = 0; i < N+1; i++) {
    edge = G[i];
    G[i] = NULL;
    while (edge) {
      EdgeNode *tmp = edge;
      edge = edge->next;
      delete tmp;
    }
  }
  return 0;
}

// 解析命令行参数
void get_argv(char **argv)
{
  char *command = NULL;
  while (*argv) {
    command = *argv;

    switch (command[1]) {
    case 'f':
      input_filename = &command[2];
      break;

    case 'o':
      output_filename = &command[2];
      outfile.open(output_filename);
      break;

    case 's':
      start_point = atoi(&command[2]);
      break;

    case 'd':
      end_point = atoi(&command[2]);
      break;

    case 'c':
      condition = atoi(&command[2]);
      break;

    default:
      break;
    } // switch
    argv++;
  }
}

// 计算路径
void get_path()
{
  // 计算主用路径
  get_main_path();

  // 获取主用路径长度，存到全局变量main_path_length里
  get_main_path_length();

  outfile << "main: ";
  print_path(end_point);
  outfile << endl;

  // 计算备用路径
  if (get_backup_path()) {
    outfile << "backup: ";
    print_path(end_point);
    outfile << endl;
  } else {
    outfile << "No backup path under condition " << condition << endl;
  }
}

// 计算主用路径，用广度优先搜索
void get_main_path()
{
  memset(color, 0, sizeof(color));
  memset(parent, 0, sizeof(parent));
  while (!Q.empty()) {
    Q.pop();
  }

  color[start_point] = BLACK;
  parent[start_point] = 0;
  Q.push(start_point);

  EdgeNode *edge = NULL;
  while (!Q.empty()) {
    int pt = Q.front();
    Q.pop();
    edge = G[pt];
    while (edge) {
      if (color[edge->ver] == WHITE) {
	color[edge->ver] = BLACK;
	parent[edge->ver] = pt;
	if (edge->ver == end_point) {
	  return;
	}
	Q.push(edge->ver);
      }
      edge = edge->next;
    }
  }
}

bool get_backup_path()
{
  // 将主用路径所经过的点和边存到下面两个数组中，以便计算备用路径时避开他们
  main_point = new int[main_path_length+1];
  main_edge = new Edge[main_path_length];
  record_main_path();

  memset(color, 0, sizeof(color));
  memset(parent, 0, sizeof(parent));
  while (!Q.empty()) {
    Q.pop();
  }

  // 仍然用深度优先，不过要根据condition约束避开主用路径的中间点或边
  if (condition == 1) {
    color[start_point] = BLACK;
    parent[start_point] = 0;
    Q.push(start_point);

    EdgeNode *edge = NULL;
    while (!Q.empty()) {
      int pt = Q.front();
      Q.pop();
      edge = G[pt];
      while (edge) {
	if (color[edge->ver] == WHITE && is_not_mainpt(edge->ver)) {
	  color[edge->ver] = BLACK;
	  parent[edge->ver] = pt;
	  if (edge->ver == end_point) {
	    return true;
	  }
	  Q.push(edge->ver);
	}
	edge = edge->next;
      } // while (edge)
    } // while (!Q.empty())
  } // if (condition == 1)
  else if (condition == 2) {
    color[start_point] = BLACK;
    parent[start_point] = 0;
    Q.push(start_point);

    EdgeNode *edge = NULL;
    while (!Q.empty()) {
      int pt = Q.front();
      Q.pop();
      edge = G[pt];
      while (edge) {
	if (color[edge->ver] == WHITE && is_not_maineg(pt, edge->ver)) {
	  color[edge->ver] = BLACK;
	  parent[edge->ver] = pt;
	  if (edge->ver == end_point) {
	    return true;
	  }
	  Q.push(edge->ver);
	}
	edge = edge->next;
      } // while (edge)
    } // while (!Q.empty())
  } // else if (condition == 2)
  return false;
}

// 判断点pt是否主用路径的中间点，不是返回true
bool is_not_mainpt(int pt)
{
  for (int i = 1; i < main_path_length; i++) {
    if (pt == main_point[i]) {
      return false;
    }
  }
  return true;
}

// 判断边<u,v>是否主用路径的边，不是返回true
bool is_not_maineg(int u, int v)
{
  for (int i = 0; i < main_path_length; i++) {
    if (u == main_edge[i].u && v == main_edge[i].v) {
      return false;
    }
  }
  return true;
}

// 记录主用路径所经过的中间点和边
void record_main_path()
{
  int pt = end_point;
  for (int i = 0; i <= main_path_length; i++) {
    main_point[i] = pt;
    pt = parent[pt];
  }

  pt = end_point;
  for (int i = 0; i < main_path_length; i++) {
    if (parent[pt] != 0) {
      main_edge[i].u = parent[pt];
      main_edge[i].v = pt;
      pt = parent[pt];
    }
  }
}

// 打印从start_point到end_point的路径
void print_path(int pt)
{
  if (pt != 0) {
    print_path(parent[pt]);
    if (pt != end_point) {
      outfile << pt << ",";
    } else {
      outfile << pt;
    }
  }
}

// 获取主用路径长度（路径的边数）
void get_main_path_length()
{
  int pt = parent[end_point];
  while (pt != 0) {
    main_path_length++;
    pt = parent[pt];
  }
}
