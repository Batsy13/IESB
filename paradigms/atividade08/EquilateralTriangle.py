import math
from Triangle import Triangle

class EquilateralTriangle(Triangle):
    def __init__(self, edgeA: float):
        if edgeA <= 0:
            raise ValueError("Aresta deve ser maior que zero")
        self.edgeA = edgeA

    def getEdgeA(self):
        return self.edgeA

    def area(self):
        return (math.sqrt(3) / 4) * (self.edgeA ** 2)