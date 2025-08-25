from abc import ABC, abstractmethod

class Graph(ABC):
    
    @abstractmethod
    def num_of_vertices(self):
        pass
    
    @abstractmethod
    def num_of_edges(self):
        pass
    
    @abstractmethod
    def degree_sequence(self):
        pass
    
    @abstractmethod
    def add_edge(self, u, v):
        pass
    
    @abstractmethod
    def remove_edge(self, u, v):
        pass
    
    @abstractmethod
    def print_graph(self):
        pass

    @abstractmethod
    def is_simple(self):
        pass

    @abstractmethod
    def is_null(self):
        pass

    @abstractmethod
    def is_complete(self):
        pass