from graph import Graph
from collections import defaultdict

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
            print(f"{vertex} -> {" ".join(map(str,neighbors))}")

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
