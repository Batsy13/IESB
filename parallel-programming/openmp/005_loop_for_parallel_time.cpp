#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>

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

    std::vector<double> threads_time(omp_get_max_threads(), 0.0);

    int threads_usadas = 0;

    double T0 = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp single
        {
            threads_usadas = omp_get_num_threads();
        }

        double t0 = omp_get_wtime();

        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++)
        {
            total[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }

        double t1 = omp_get_wtime();
        threads_time[tid] = (t1 - t0);
    }

    double T1 = omp_get_wtime();
    double tempo_total = T1 - T0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "a[0]     = " << total[0] << "\n";
    std::cout << "a[N-1]   = " << total[N - 1] << "\n\n";

    std::cout << std::setprecision(6);
    std::cout << "Threads utilizadas: " << threads_usadas << "\n";
    std::cout << "Tempo TOTAL (s):    " << tempo_total << "\n";

    std::cout << "\nTempo por thread (s):\n";
    for (int t = 0; t < threads_usadas; t++)
    {
        std::cout << "  Thread " << t << ": " << threads_time[t] << "\n";
    }

    return 0;
}