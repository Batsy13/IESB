/*

Alunos:

Pedro Costa Ferreira - 2312130138
Gabriel Rodrigues - 2312130033
Felipe Ferreira - 2312130021

*/

#include <iostream>
#include <cmath>
#include <omp.h>
#include <vector>

double bhaskara(double a, double b, double c);

int main()
{
    int N = 0;
    std::cout << "Insira o número de iterações: ";
    std::cin >> N;

    double a_value, b_value, c_value;
    std::cout << "Insira a:";
    std::cin >> a_value;
    std::cout << "Insira b:";
    std::cin >> b_value;
    std::cout << "Insira c:";
    std::cin >> c_value;

    std::vector<double> a(N, a_value), b(N, b_value), c(N, c_value);
    std::vector<double> roots_sum(N);

    double total_sum = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            roots_sum[i] = bhaskara(a[i], b[i], c[i]);
            printf("Thread (id: %d) fez iteração %d\n", thread_id, i);
        }

        #pragma omp barrier

        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            #pragma omp critical
            std::cout << "roots_sum na posição " << i << " tem valor: " << roots_sum[i] << std::endl;
        }
    }

    double final_time = omp_get_wtime();
    double total_time = (final_time - start_time);
    std::cout << "Tempo Gasto: " << total_time << std::endl;

    return 0;
}

double bhaskara(double a, double b, double c)
{
    double b_squared, four_ac, delta, x1, x2;

    #pragma omp parallel 
    {
        b_squared = (b * b);
        four_ac = (4 * a * c);
    }

    delta = b_squared - four_ac;

    if (delta < 0)
    {
        return 0.0;
    }

    #pragma omp parallel
    {
        x1 = ((-b + sqrt(delta)) / (2 * a));
        x2 = ((-b - sqrt(delta)) / (2 * a));
    }

    return x1 + x2;
}