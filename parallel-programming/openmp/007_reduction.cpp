#include <iostream>
#include <iomanip>
#include <omp.h>
#include <math.h>
#include <cstdlib>
#include <vector>

int main (){
    const int departamentos = 500;
    const int funcionarios = 4000;

    const int N = departamentos * funcionarios;
    std::vector<double> salaries(N);

    const double start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        salaries[i] = rand() % 50000;
    }
    
    // Fazendo a média dos salários
    
    double sum_salaries = 0;
    
    #pragma omp parallel for reduction(+:sum_salaries)
    for(int i = 0; i < N; i++){
        sum_salaries += salaries[i];
    }

    double average = sum_salaries / static_cast<double>(N);
    
    // Fazendo o somatório (xi - x)

    double sum_deviation = 0;
    
    #pragma omp parallel for reduction(+:sum_deviation)
    for(int i = 0; i < N; i++){
        sum_deviation = pow((salaries[i] - average), 2);
    }

    double sample_variance = sum_deviation / static_cast<double>(N - 1);
    
    double sample_standard_deviation = sqrt(sample_variance);
    
    const double final_time = omp_get_wtime();

    const double total_time = final_time - start_time;

    std::cout << "Empresa BigPoggers" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Analise Salarial (amostral)\n";
    std::cout << "N = " << N << "\n";
    std::cout << "Media (x̄)              : R$ " << average << "\n";
    std::cout << "Variancia amostral (σ²): R$ " << sample_variance << "\n";
    std::cout << "Desvio-padrao amostral : R$ " << sample_standard_deviation << "\n";
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Tempo Gasto : " << total_time << "\n";
    
    return 0;
}