#include <iostream>
#include <omp.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

double calculate_coeficiente_variacao_sequential(int N, const std::vector<int>& fi, const std::vector<double>& xi) {
    double sum_xi_fi = 0.0;
    int k = fi.size();

    for (int i = 0; i < k; i++) {
        sum_xi_fi += xi[i] * fi[i];
    }

    double mu = sum_xi_fi / N;

    double sum_desvio_padrao = 0.0;
    for (int i = 0; i < k; i++) {
        sum_desvio_padrao += fi[i] * pow(xi[i] - mu, 2);
    }

    double sigma = sqrt(sum_desvio_padrao / N);
    
    double coeficiente_variacao = (sigma / mu) * 100.0;
    return coeficiente_variacao;
}

double calculate_coeficiente_variacao_parallel(int N, const std::vector<int>& fi, const std::vector<double>& xi) {
    double sum_xi_fi = 0.0;
    int k = fi.size();

    #pragma omp parallel for reduction(+:sum_xi_fi)
    for (int i = 0; i < k; i++) {
        sum_xi_fi += xi[i] * fi[i];
    }

    double mu = sum_xi_fi / N;
    
    double sum_desvio_padrao = 0.0;
    #pragma omp parallel for reduction(+:sum_desvio_padrao)
    for (int i = 0; i < k; i++) {
        sum_desvio_padrao += fi[i] * pow(xi[i] - mu, 2);
    }

    double sigma = sqrt(sum_desvio_padrao / N);
    
    double coeficiente_variacao = (sigma / mu) * 100.0;
    return coeficiente_variacao;
}

int main()
{
    srand(time(NULL));
    const int NUM_PEOPLE = 1000;
    std::vector<int> altura(NUM_PEOPLE);
    std::vector<float> peso(NUM_PEOPLE);

    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        altura[i] = rand() % 60 + 140;
        peso[i] = (float)(rand() % 1000) / 10.0 + 30.0;
    }
    
    std::sort(altura.begin(), altura.end());
    std::sort(peso.begin(), peso.end());
    
    std::vector<int> fi_altura;
    std::vector<double> xi_altura;
    std::vector<int> fi_peso;
    std::vector<double> xi_peso;

    int min_altura = 140;
    int max_altura = 200;
    int step_altura = 8;

    float min_peso = 30.0f;
    float max_peso = 130.0f;
    float step_peso = 4.0f;

    for (int i = min_altura; i < max_altura; i += step_altura)
    {
        int pessoas_no_intervalo = 0;
        for (int j = 0; j < NUM_PEOPLE; j++)
        {
            if (altura[j] >= i && altura[j] < i + step_altura)
            {
                pessoas_no_intervalo++;
            }
            else if (altura[j] >= i + step_altura)
            {
                break;
            }
        }
        if (pessoas_no_intervalo > 0) {
            fi_altura.push_back(pessoas_no_intervalo);
            xi_altura.push_back((i + i + step_altura) / 2.0);
        }
    }

    for (float i = min_peso; i < max_peso; i += step_peso)
    {
        int pessoas_no_intervalo = 0;
        for (int j = 0; j < NUM_PEOPLE; j++)
        {
            if (peso[j] >= i && peso[j] < i + step_peso)
            {
                pessoas_no_intervalo++;
            }
            else if (peso[j] >= i + step_peso)
            {
                break;
            }
        }
        if (pessoas_no_intervalo > 0) {
            fi_peso.push_back(pessoas_no_intervalo);
            xi_peso.push_back((i + i + step_peso) / 2.0);
        }
    }

    std::cout << std::fixed << std::setprecision(4);

    double start_seq = omp_get_wtime();
    double coeficiente_variacao_altura_seq = calculate_coeficiente_variacao_sequential(NUM_PEOPLE, fi_altura, xi_altura);
    double coeficiente_variacao_peso_seq = calculate_coeficiente_variacao_sequential(NUM_PEOPLE, fi_peso, xi_peso);
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    double start_par = omp_get_wtime();
    double coeficiente_variacao_altura_par = calculate_coeficiente_variacao_parallel(NUM_PEOPLE, fi_altura, xi_altura);
    double coeficiente_variacao_peso_par = calculate_coeficiente_variacao_parallel(NUM_PEOPLE, fi_peso, xi_peso);
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    std::cout << "\n--- Resultados Sequenciais ---" << std::endl;
    std::cout << "coeficiente_variacao Altura: " << coeficiente_variacao_altura_seq << "%" << std::endl;
    std::cout << "coeficiente_variacao Peso: " << coeficiente_variacao_peso_seq << "%" << std::endl;
    std::cout << "Tempo Sequencial: " << time_seq << " segundos" << std::endl;

    std::cout << "\n--- Resultados Paralelos (OpenMP) ---" << std::endl;
    std::cout << "coeficiente_variacao Altura: " << coeficiente_variacao_altura_par << "%" << std::endl;
    std::cout << "coeficiente_variacao Peso: " << coeficiente_variacao_peso_par << "%" << std::endl;
    std::cout << "Tempo Paralelo: " << time_par << " segundos" << std::endl;

    std::cout << "\n--- Analise de Desempenho ---" << std::endl;
    std::cout << "Speedup: " << (time_seq / time_par) << "x" << std::endl << std::endl;

    return 0;
}