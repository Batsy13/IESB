#include <iostream>
#include <vector>

int main() {

    const int N = 10;
    std::vector<int> x(N), y(N), z(N), total(N);

    for(int i = 0; i < N; i++){
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    for(int i = 0; i < N; i++){
        total[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];

        std::cout << "i = " << i
                  << " | total[i]: " << total[i] 
                  << " | x[i]: " << x[i]
                  << " | y[i]: " << y[i]
                  << " | z[i]: " << z[i] 
                  << std::endl;
    }

    return 0;
}