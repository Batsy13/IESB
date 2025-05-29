from abc import ABC, abstractmethod


class Triangle(ABC):
    def getEdges(self):
        return 3

    def getVertices(self):
        return 3

    @abstractmethod
    def area(self):
        pass