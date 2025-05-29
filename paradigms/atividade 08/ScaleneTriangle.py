import math
from IsoscelesTriangle import IsoscelesTriangle


class ScaleneTriangle(IsoscelesTriangle):
    def __init__(self, edgeA: float, edgeB: float, edgeC: float):
        if edgeA <= 0 or edgeB <= 0 or edgeC <= 0:
            raise ValueError("Arestas precisam ser maior que zero")
        if len({edgeA, edgeB, edgeC}) < 3:
            raise ValueError("Todas as arestas devem ser distintas")
        
        super().__init__(edgeA, edgeB)
        self.edgeC = edgeC

    def getEdgeC(self):
        return self.edgeC

    def area(self):
        a, b, c = self.edgeA, self.edgeB, self.edgeC
        s = (a + b + c) / 2
        return math.sqrt(s * (s - a) * (s - b) * (s - c))
