#include <iostream>

void insertName();
void seeNames();

int main() {

    // A )

    int grade;

    if(grade >= 6){
        std::cout << "Approved";
    } else if (4 <= grade < 6) {
        std::cout << "Retake Test";
    } else if (grade < 4){
        std::cout << "Reproved";
    }

    // B )

    int option;

    do{
        std::cout << "*************************\n";
        std::cout << "Enter a valid Option: ";
        std::cout << "1 - Insert Name";
        std::cout << "2 - See Names";
        std::cout << "3 - Exit";
        std::cout << "*************************\n";

        std::cin >> option;
        switch(option){
            case 1:
                insertName();
                break;
            case 2:
                seeNames();
                break;
            default:
                std::cout << "Insert a valid option\n";
                break;
        }
    }while(option != 3);

    return 0;
}

void insertName(){
    std::cout << "Inserting..." << "\n";
}

void seeNames(){
    std::cout << "Names: " << "\n";
}