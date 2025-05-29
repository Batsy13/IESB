from Triangle import Triangle


class Shapes:
    def __init__(self):
        self.figures = []

    def add_shape(self, shape: Triangle):
        self.figures.append(shape)

    def show_shapes(self):
        for i, shape in enumerate(self.figures, start=1):
            print(f"Figure {i}: {type(shape).__name__}")
            print(f" - Edges: {shape.getEdges()}")
            print(f" - Vertices: {shape.getVertices()}")
            print(f" - Area: {shape.area():.2f}")
            print()