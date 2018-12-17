import math


class Edge:
  def __init__(self, src, dst, cost):
    self.src = src
    self.dst = dst
    self.cost = cost

class Node:
   def __init__(self, node_id):
      self.min_predecessor = None
      self.min_cost = math.inf
      self.node_id = node_id
      self.outgoing_edges = []

class Graph:
   def __init__(self):
      self.nodes = {}
      self.edges = {}
   def add_node(self, node_id):
      self.nodes[node_id] = Node(node_id)
      
   def add_edge(self,node_id1, node_id2, cost):
       if self.nodes[node_id1] == None or self.nodes[node_id2] == None:
          raise ValueError('Dictionary error')

       node1 = self.nodes[node_id1]
       node2 = self.nodes[node_id2]
       edge_key =  (node1,node2)
       self.edges[edge_key] = Edge(node1, node2, cost)
       node1.outgoing_edges.append(self.edges[edge_key])


def NodeCostComparison(elem):
   return elem.min_cost

class bad_priority_queue:
   def __init__(self):
      self.elems = []
   
   def push(self,elem):
      self.elems.append(elem)

   def empty(self):
      if self.elems:
         return False
      else:
         return True

   def  pop_top(self):
      val = min(self.elems, key=NodeCostComparison)
      i = self.elems.index(val)
      del self.elems[i]
      return val

# see Algorithms by Cormen, Leiserson, Rivest, ch.25.2
def main():
   g = Graph()
   num_nodes = 8
   for i in range(0, num_nodes):
      g.add_node(i)
   
   g.add_edge(0,1,1)
   g.add_edge(0,2,1)
   g.add_edge(0,3,1)
   g.add_edge(1,3,1)
   g.add_edge(1,4,1)
   g.add_edge(3,4,1)
   g.add_edge(3,5,1)
   g.add_edge(4,7,1)
   g.add_edge(2,6,1)
   g.add_edge(6,5,1)
   g.add_edge(5,7,1)

   g.nodes[0].min_cost = 0
   
   
   S = []
   Q = bad_priority_queue() 
   for key,value in g.nodes.items():
      Q.push(value)
  
   while (not Q.empty()):
      u = Q.pop_top()
      S.append(u)
      for e in u.outgoing_edges:
         v = e.dst
         if v.min_cost > u.min_cost + e.cost:
            v.min_cost = u.min_cost + e.cost
            v.min_predecessor = u

   for i in range(0, num_nodes):
      u = g.nodes[i]
      print("Node ", i, "  Min Cost ",u.min_cost, end=" ")
      min_predecessor = u.min_predecessor      
      print("  Min cost path ", end=" ")
      while min_predecessor != None:
         print(min_predecessor.node_id, end=" ")
         min_predecessor = g.nodes[min_predecessor.node_id].min_predecessor
      print("")
      
main() 
