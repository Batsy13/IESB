from Shapes import Shapes
from EquilateralTriangle import EquilateralTriangle
from IsoscelesTriangle import IsoscelesTriangle
from ScaleneTriangle import ScaleneTriangle


if __name__ == "__main__":
    shapes = Shapes()
    shapes.add_shape(EquilateralTriangle(5))
    shapes.add_shape(IsoscelesTriangle(5, 6))
    shapes.add_shape(ScaleneTriangle(5, 6, 7))
    shapes.show_shapes()