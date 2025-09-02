#include <iostream>
#include <vector>

int main() {

    // A )

    int arr[5] = {1,2,3,4,5};
    int sum = 0;

    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        sum += arr[i];
    }

    std::cout << sum << std::endl;

    // B )

    std::vector<int> v = {5, 10, 15};
    v.push_back(42);
    v.push_back(69);

    int sumVec = 0;

    for(int item:v){
        sumVec += item;
    }
    std::cout << "Size: " << v.size() << '\n';
    std::cout << "sumVec: " << sumVec;

    return 0;
}

