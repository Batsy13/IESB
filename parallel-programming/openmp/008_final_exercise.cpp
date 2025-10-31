#include <iostream>
#include <omp.h>
#include <algorithm>
#include <vector>

int main()
{

    const int NUM_PEOPLE = 1000;
    std::vector<int> altura(NUM_PEOPLE);
    std::vector<float> peso(NUM_PEOPLE);

    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        altura[i] = rand() % 60 + 140;
        peso[i] = rand() % 100 + 30;
    }
    
    std::sort(altura.begin(), altura.end());
    std::sort(peso.begin(), peso.end());
    
    int menor_altura = altura[1];
    int maior_altura = altura[NUM_PEOPLE - 1];

    std::cout << menor_altura << std::endl
              << maior_altura << std::endl;

    std::vector<int> fi_altura;
    std::vector<int> fi_peso;
    std::vector<int> xi_altura;
    std::vector<int> xi_peso;

    // Para altura ( intervalos de 8 )

    for (int i = 140; i < 200; i += 8)
    {
        int pessoas_no_intervalo = 0;
        for (int j = 0; j < NUM_PEOPLE; j++)
        {
            if (altura[j] >= i && altura[j] < i + 8)
            {
                pessoas_no_intervalo += 1;
            }
            else if (altura[j] < i)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        std::cout << "Pessoas no intervalo: " << i << " |-- " << i + 8 << ": " << pessoas_no_intervalo << std::endl;
        fi_altura.push_back(pessoas_no_intervalo);
        xi_altura.push_back((i + i + 8)/2);
    }

    float mi_altura = 0;

    for(int i = 0; i < NUM_PEOPLE; i++){
        mi_altura += fi_altura[i] * xi_altura[i];
    }

    float media_altura = mi_altura;

    std::cout << media_altura << std::endl;

    return 0;
}