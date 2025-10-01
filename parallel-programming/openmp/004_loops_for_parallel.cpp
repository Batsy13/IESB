#include <iostream>
#include <vector>

int main()
{
    const int N = 10;
    std::vector<int> x(N), y(N), z(N), total(N);

    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++)
    {
        total[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }

    for (int i = 0; i < N; i++)
    {
        total[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];

        std::cout << "i = " << i
                  << " | total[i]: " << total[i]
                  << " | x[i]: " << x[i]
                  << " | y[i]: " << y[i]
                  << " | z[i]: " << z[i]
                  << std::endl;
    }

    std::cout << "\nResumo dos resultados:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  i |   x[i] |   y[i] |   z[i] |   a[i]\n";
    std::cout << "----------------------------------------\n";
    for (int i = 0; i < N; i++) {
        std::cout << " " << i
                  << "  | " << x[i]
                  << "     | " << y[i]
                  << "     | " << z[i]
                  << "     | " << total[i]
                  << std::endl;
    }
    std::cout << "----------------------------------------\n";

    return 0;
}