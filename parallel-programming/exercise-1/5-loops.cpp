#include <iostream>

int main() {

    // A )

    for(int i = 0; i < 20; i++){
        if(i % 2 != 0){
            std::cout << i << "\n";
        }
    }

    // B )
    
    int i = 10;
    while(i != 0) {
        std::cout << i << "\n";
        i--;
    }

    // C )
    
    int opt;
    do{

        std::cout << "Enter 0 to exit";
        std::cin >> opt;

        switch(opt){
            case 0:
                std::cout << "Exiting...";
                break;
            default:
                std::cout << "Enter a valid option";
                break;
        }

    }while(opt != 0);

    return 0;
}