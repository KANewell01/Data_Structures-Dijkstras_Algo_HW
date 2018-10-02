// Main file of Dijkstra's Algorithm
// Kevin Newell - kanm29
// 5/1/18

#include "dijkstra.h"

using namespace std;

int main(){
  int dim = 0;
  string param[2]; // src/dest
  pair<string, float> *names = nullptr; // node id's
  vector<vector<float>> graph = buildGraph(names, dim, param);
  vector<float[2]> dist(dim);
  vector<int> path;

  path = findPath(graph, dim, param, names, dist);

  print(param, names, path, dist);

  delete[] names;
  return 0;
}
