// Utility classes for dijkstra
// Kevin Newell
// 5/7/18

class NotPair{
  public:
    int node;
    float dist;

    NotPair(int i, float d): node(i), dist(d){}
};

class Comparator{
  public:
    bool operator()(NotPair left, NotPair right){return left.dist > right.dist;}
};
