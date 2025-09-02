#include <iostream>

int main() {

    // A )

    int x = 10;

    int *pX = &x;

    *pX *= 2;
    
    std::cout << x << std::endl;
    
    *pX *= 3;
    
    std::cout << x << std::endl;

    // B )

    int *pPoggers = NULL;
    pPoggers = new int;

    std::cout << "Enter a number: ";
    std::cin >> *pPoggers;
    std:: cout << *pPoggers << std::endl;

    free(pPoggers);


    return 0;
}