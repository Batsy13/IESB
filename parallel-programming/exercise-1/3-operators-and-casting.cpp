#include <iostream>

int main() {

    // A )

    int first;
    int second;

    std::cout << "Enter your first number: ";
    std::cin >> first;

    std::cout << "Enter your second number: ";
    std::cin >> second;

    std::cout << first << " + " << second << " = " << first + second << "\n"; 
    std::cout << first << " - " << second << " = " << first - second << "\n"; 
    std::cout << first << " * " << second << " = " << first * second << "\n"; 
    std::cout << first << " / " << second << " = " << first / second << "\n"; 
    std::cout << first << " / " << second << " = " << first / (double)second << "\n"; 


    // B )

    (first > second) ? std::cout << first : std::cout << second; 

    return 0;
}