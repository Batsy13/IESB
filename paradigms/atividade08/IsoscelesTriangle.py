import math
from EquilateralTriangle import EquilateralTriangle

class IsoscelesTriangle(EquilateralTriangle):
    def __init__(self, edgeA: float, edgeB: float):
        if edgeB <= 0 or edgeA <= 0:
            raise ValueError("Arestas devem ser maior que zero")
        if edgeA == edgeB:
            raise ValueError("Arestas precisam ser distintas")
        
        super().__init__(edgeA) 
        self.edgeB = edgeB
        
    def getEdgeB(self):
        return self.edgeB

    def area(self):
        h = math.sqrt(self.edgeA ** 2 - (self.edgeB ** 2) / 4)
        return (self.edgeB * h) / 2