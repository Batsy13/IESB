from collections import defaultdict
from itertools import permutations
from graph import Graph

class SparseGraph(Graph):
    def __init__(self, num_vertices_or_labels):
        self.vertices_map = {}
        self.indices_map = {}
        self.number_edges = 0
        
        if isinstance(num_vertices_or_labels, int):
            
            self.num_vertices = num_vertices_or_labels
            
            for i in range(self.num_vertices):
                self.vertices_map[i] = i
                self.indices_map[i] = i  
        elif isinstance(num_vertices_or_labels, list):
            
            self.num_vertices = len(num_vertices_or_labels)
            
            for i, label in enumerate(num_vertices_or_labels):
                
                if label in self.vertices_map:
                    raise ValueError(f"Duplicated label '{label}' in the vertex list")
                
                self.vertices_map[label] = i
                self.indices_map[i] = label
            
        else:
            raise ValueError("Argument must be an integer number of vertices or a list of labels")
        
        self.adjacency_list = defaultdict(list) 
        self.vertex_list = sorted(list(self.vertices_map.keys()))
        
    def num_of_vertices(self):
        return self.num_vertices
    
    def num_of_edges(self):
        return self.number_edges
    
    def degree_sequence(self):
        return sorted([len(self.adjacency_list[row]) for row in self.adjacency_list])
        
    def _get_index(self, label):
        if label not in self.vertices_map:
            raise ValueError(f"Vertex '{label}' does not exist on graph") 
        
        return self.vertices_map[label]
        
    def add_edge(self, u, v):
        try:
            self._get_index(u)
            self._get_index(v)
        except:
            print(f"Could not add Edge ({u}, {v})")
            return
        
        self.adjacency_list[u].append(v)
        self.adjacency_list[v].append(u)
        self.number_edges += 1
        print(f"Edge added between {u} and {v}")
                     
    def remove_edge(self, u, v):
        try:
            self._get_index(u)
            self._get_index(v)
        except:
            print(f"Could not remove Edge ({u}, {v})")
            
        print(f"Removing edge between {u} and {v}")
        self.adjacency_list[u].remove(v)
        self.number_edges -= 1
        
    def print_graph(self):
        if self.num_of_edges() == 0:
            print("Graph is Empty")
            return
        
        print("\nGraph Representation (Adjacency List):")
        for vertex, neighbors in self.adjacency_list.items():
            print(f"{vertex} -> {' '.join(map(str,neighbors))}")

    def is_simple(self):
        for vertex, neighbors in self.adjacency_list.items():
            if vertex in neighbors:
                return False
            if len(set(neighbors)) != len(neighbors):
                return False
        return True

    def is_null(self):
        return self.number_edges == 0

    def is_complete(self):
        if not self.is_simple():
            return False
        
        expected_edges = self.num_vertices * (self.num_vertices - 1) // 2
        return self.number_edges == expected_edges
    
    def is_isomorphic(self, other_graph):

        if not isinstance(other_graph, SparseGraph):
            raise TypeError("Isomorphism can only be checked between two SparseGraph instances.")

        if self.num_of_vertices() != other_graph.num_of_vertices():
            return False

        if self.num_of_edges() != other_graph.num_of_edges():
            return False

        if self.degree_sequence() != other_graph.degree_sequence():
            return False

        n = self.num_of_vertices()
        
        self_nodes = [self.indices_map[i] for i in range(n)]
        other_nodes = [other_graph.indices_map[i] for i in range(n)]

        for p_other_nodes in permutations(other_nodes):
            
            mapping = {self_nodes[i]: p_other_nodes[i] for i in range(n)}
            
            is_match = True
            for i in range(n):
                for j in range(i, n):
                    u_self, v_self = self_nodes[i], self_nodes[j]
                    u_other, v_other = mapping[u_self], mapping[v_self]

                    is_edge_in_self = v_self in self.adjacency_list.get(u_self, [])
                    
                    is_edge_in_other = v_other in other_graph.adjacency_list.get(u_other, [])

                    if is_edge_in_self != is_edge_in_other:
                        is_match = False
                        break
                if not is_match:
                    break
            
            if is_match:
                return True

        return False
      
    def get_edges(self):
      edges = []
      visited = set()
      for v_source, neighbors in self.adjacency_list.items():
          for v_destination in neighbors:
              sorted_edge = tuple(sorted((v_source, v_destination)))
              if sorted_edge not in visited:
                  edges.append((v_source, v_destination))
                  visited.add(sorted_edge)
      return edges

    def _is_safe(self, vertex, color, colors):
        for neighbor in self.adjacency_list[vertex]:
            if colors.get(neighbor) == color:
                return False
        return True

    def _can_color(self, k, colors, vertex_idx):
        if vertex_idx == self.num_vertices:
            return True

        current_vertex = self.vertex_list[vertex_idx]
        
        for color in range(1, k + 1):
            print(f"Trying to color class {current_vertex} with {k} schedules...")
            if self._is_safe(current_vertex, color, colors):
                colors[current_vertex] = color
                if self._can_color(k, colors, vertex_idx + 1):
                    return True
                colors[current_vertex] = 0
        
        return False

    def color_graph(self):
        for k in range(1, self.num_vertices + 1):
            colors = {v: 0 for v in self.vertex_list}
            if self._can_color(k, colors, 0):
                return k, colors
        return None, None