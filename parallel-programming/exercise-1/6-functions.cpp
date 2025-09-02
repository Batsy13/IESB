#include <iostream>

int sum(int x, int y);
int sum(int x, int y, int z);
void increment(int &x);

int main() {

    // A )
    std::cout << sum(5,10) << "\n";

    int x = 5;

    // B )
    increment(x);
    std:: cout << x << "\n";

    // C )
    std::cout << sum(5,10,5) << "\n";

    return 0;
}

int sum(int x, int y){

    int sum = x + y;
    return sum;

}

int sum(int x, int y, int z){
    int sum = x + y + z;
    return sum;
}

void increment(int &x){
    x = x + 1;
}