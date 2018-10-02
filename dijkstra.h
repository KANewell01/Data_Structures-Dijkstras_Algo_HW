// Header of Dijkstra's Algorithm
// Kevin Newell - kanm29
// 5/1/18

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <queue>

using std::vector;
using std::string;
using std::pair;

const float INF = 999;

vector<vector<float>> buildGraph(pair<string, float> *& names, int& dim, string param[]);

vector<int> findPath(vector<vector<float>> graph, int dim, string param[],
		     pair<string, float> *names, vector<float[2]> & dist);

float weight(vector<vector<float>> graph, int src, int dst);

void print(string param[], pair<string, float> *names,
           vector<int> path, vector<float[2]> & dest);

#include "dijkImp.hpp"
