// Implementation of Dijkstra's Algorithm
// Kevin Newell - kanm29
// 5/1/18

#include "util.h"

using namespace std;

/*Builds the vector graph, and populates names*/
vector<vector<float>> buildGraph(pair<string, float> *& names, int& dim, string param[]){
  string line;

  //Get number of nodes
  getline(cin, line);
  for(auto i: line)
    if(i == ',')
      dim++;

  int i = 0;
  int start, end;
  vector<vector<float>> graph;
  names = new pair<string, float>[dim];

  while(getline(cin, line)){
    if(line.find(",,") != string::npos)
      break;

    //Populate names map
    start = 0;
    end = line.find('(');
    names[i].first = line.substr(start, end - 1);
    names[i].second = stof(line.substr(end + 1, line.find(')') - end));

    //Build the graph
    end = line.find(',');
    graph.push_back(vector<float>());

    for(int j = 0; j < dim; j++){
      start = end + 1;
      end = line.find(',', start);
      graph[i].push_back(stof(line.substr(start, end - start)));
    }
    i++;
  }

  //Identitify src and dest nodes
  getline(cin, line);
  param[0] = line.substr(31, (line.find(' ', 32) - 31) - 1);
  param[1] = line.substr(line.find(' ', 33 + param[0].length()) + 1, line.find('?') - (37 + param[0].length()));

  return graph;
}



/*Returns distance between nodes*/
float weight(vector<vector<float>> graph, int src, int dst){
  float dist = graph[src][dst];
  if(dist == 0)
    dist = INF;
  return dist;
}



/*Dijkstra's Algorithom*/
vector<int> findPath(vector<vector<float>> graph, int dim, string param[],
		     pair<string, float> *names, vector<float[2]> & dist){

  vector<int> path(dim);
  priority_queue<NotPair, vector<NotPair>, Comparator> unvisited;

  //Determins src node index and sets
  //to 0 in dist[]
  int src = 0;
  for(; src < dim; src++){
    if(names[src].first == param[0]){
      dist[src][0] = 0;
      break;
    }
  }

  //Sets all other nodes to infinity
  //and updates bribe values
  //and pushes src into unvisited
  for(int i = 0; i < dim; i++){
    if(i != src){
      dist[i][0] = INF;
      dist[i][1] = names[i].second;
    }else
      unvisited.push(NotPair(i, dist[i][0]));
  }

  //Calculates distances to neighboring nodes
  while(!unvisited.empty()){
    NotPair i = unvisited.top();
    unvisited.pop();

    for(int j = 0; j < dim; j++){
      float tax = dist[i.node][0] + weight(graph, i.node, j);
      if(tax < dist[j][0]){
        dist[j][0] = tax;
	path[j] = i.node;
	unvisited.push(NotPair(j, tax));
      }
    }
  }

  return path;
}



/*Makes sense of outputted info and formats output string*/
void print(string param[], pair<string, float> *names, vector<int> path, vector<float[2]> & dist){
  vector<int> walk;
  float bribe = 0;
  int src, dst;

  //Determin destination index
  for(int i = 0; i < dist.size(); i++){
    if(names[i].first == param[1])
      dst = i;
    if(names[i].first == param[0])
      src = i;
  }

  walk.push_back(dst);
  int i = dst;
  do{
    walk.push_back(path[i]);
    bribe += names[path[i]].second;
    i = path[i];
  }while(src != i);

  //Format output
  if(dist[dst][0] == INF){
    cout << "There is no path from " << (param[0] + "s") <<" to " << (param[1] + "s.") << endl;
    return;
  }

  cout << "The shortest path from " << (param[0] + "s") <<" to " << (param[1] + "s") << " is:" << endl;

  for(int i = walk.size() - 1; i >= 0; i--)
    cout << (names[walk[i]].first + "s") << ", ";

  cout << "with sum exchange cost of " << dist[dst][0] << " and bribe cost of " << bribe << "." << endl;
}
