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
    
    double total_sum = 0;

    double T0 = omp_get_wtime();

    omp_lock_t lock_soma;
    omp_init_lock(&lock_soma);

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < N; i++)
    {
        double local_sum = bhaskara(a[i], b[i], c[i]);

        omp_set_lock(&lock_soma);
        total_sum += local_sum;
        omp_unset_lock(&lock_soma);
    }

    double T1 = omp_get_wtime();

    omp_destroy_lock(&lock_soma);

    double total_time = (T1 - T0);

    std::cout << "Soma total: " << total_sum << std::endl;
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

    if (delta < 0){
        return 0.0;
    }

    #pragma omp parallel 
    {
        x1 = ((-b + sqrt(delta)) / (2 * a));
        x2 = ((-b - sqrt(delta)) / (2 * a));
    }

    return x1 + x2;
}