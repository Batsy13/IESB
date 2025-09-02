#include <iostream>

int main() {

    // A )

    std::string name;
    int age;
    double height;
    bool aproved;

    name = "Pedro";
    age = 20;
    height = 1.75;
    aproved = true;

    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Height: " << height << "\n";
    std::cout << "Aproved? " << aproved << "\n";

    // B )

    const double pi = 3.14159;

    double radius = 5;
    double circle = pi * (radius * radius);

    std::cout << "Area: " << circle << "\n";

    return 0;
}