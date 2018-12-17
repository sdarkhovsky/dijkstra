#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <iostream>

#define INF 9999999999

using namespace std;


class Node;

class Edge {
 public:
  Edge()
  {
    src = nullptr;
    dst = nullptr;
    cost = 0;
  }
  Edge(Node* _src, Node* _dst, float _cost)
  {
    src = _src;
    dst = _dst;
    cost = _cost;
  }
  Edge(const Edge& other)
  {
    src = other.src;
    dst = other.dst;
    cost = other.cost;
  }
  Edge& operator=(const Edge& other)
  {
    src = other.src;
    dst = other.dst;
    cost = other.cost;     
  } 
  Node* src;
  Node* dst;
  float cost;
};

class Node {
  public:
   Node(int _node_id) {
      min_predecessor = nullptr;
      min_cost = INF;
      node_id = _node_id;
   }
   Node() {
      min_predecessor = nullptr;
      min_cost = INF;
   }

   Node(const Node& other) {
      min_predecessor = other.min_predecessor;
      min_cost = other.min_cost;
      node_id = other.node_id;
   }

   Node* min_predecessor;
   float min_cost;
   vector <Edge*> outgoing_edges;
   int node_id;
};

class Graph {
   public:
   void add_node(int node_id) {
      if (nodes.find( node_id ) != nodes.end())
          throw;
      nodes[node_id] = Node(node_id);
   }

   void add_edge(int node_id1, int node_id2, float cost)
   {
       if (nodes.find( node_id1 ) == nodes.end() || nodes.find( node_id2 ) == nodes.end())
          throw;

       Node* pnode1 = &nodes[node_id1];
       Node* pnode2 = &nodes[node_id2];
       auto edge_key =  pair<Node*,Node*>(pnode1,pnode2);
       if (edges.find(edge_key) != edges.end())
          throw;
       edges[edge_key] = Edge(pnode1, pnode2, cost);
       pnode1->outgoing_edges.push_back(&edges[edge_key]);
   }
   
   map<int, Node> nodes;
   map<pair<Node*,Node*>, Edge> edges;
};


template <class T>
class NodeCostComparison
{
public:
  bool operator() (const T lhs, const T rhs) const
  {
    return (lhs->min_cost < rhs->min_cost);
  }
};

template <class T, class Compare>
class bad_priority_queue {
   public:
   bad_priority_queue() {
   }

   void push(const T& elem) {
      elems.push_back(elem);
   }

   bool empty() {
      return elems.empty();
   }

   T  pop_top() {

      auto it = min_element(elems.begin(), elems.end(), comp);
      T val = *it;
      elems.erase(it);
      return val;
   }

   Compare comp;
   list<T> elems;
};


// see Algorithms by Cormen, Leiserson, Rivest, ch.25.2
int main()
{
   Graph g;
   int num_nodes = 8;
   for (int i = 0; i < num_nodes; i++) {
      g.add_node(i);
   }
   
   g.add_edge(0,1,1);
   g.add_edge(0,2,1);
   g.add_edge(0,3,1);
   g.add_edge(1,3,1);
   g.add_edge(1,4,1);
   g.add_edge(3,4,1);
   g.add_edge(3,5,1);
   g.add_edge(4,7,1);
   g.add_edge(2,6,1);
   g.add_edge(6,5,1);
   g.add_edge(5,7,1);

   g.nodes[0].min_cost = 0;
   
   
   list<Node*> S;
   bad_priority_queue <Node*,NodeCostComparison<Node*>> Q; 
   for (auto it=g.nodes.begin(); it != g.nodes.end(); it++) {
      Q.push(&it->second);
   }      

   while (!Q.empty()) {
      Node* u = Q.pop_top();
      S.push_back(u);
      for (auto it = u->outgoing_edges.begin(); it != u->outgoing_edges.end(); it++) {
         Node* v = (*it)->dst;
         if (v->min_cost > u->min_cost + (*it)->cost) {
            v->min_cost = u->min_cost + (*it)->cost;
            v->min_predecessor = u;
         }
      }
   }

   for (int i = 0; i < num_nodes; i++) {
      Node* u = &g.nodes[i];
      cout << "Node " << i << "  Min Cost " << u->min_cost;
      Node* min_predecessor = u->min_predecessor;      
      cout << "  Min cost path ";
      while (min_predecessor != 0) {
         cout << min_predecessor->node_id << " ";
         min_predecessor = g.nodes[min_predecessor->node_id].min_predecessor;
      }
      cout << endl;
   }
   return 0;
}
       
