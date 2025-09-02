#include <iostream>

int main() {

    // A )

    std::string name;
    int age;


    std::cout << "Enter your name: ";
    std::cin >> name;

    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "Hello, " << name << "!You are " << age << " years old!\n";

    // B )

    std::cout << "Enter your full name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Full Name: " << name;

    return 0;
}