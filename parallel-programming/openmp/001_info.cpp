#include <iostream>
#include <omp.h>

int main() {

  int num_procs = omp_get_num_procs();
  int max_threads = omp_get_max_threads();

  std::cout << "Processadores lógicos disponíveis: " << num_procs << std::endl;
  std::cout << "Máximo de threads padrão (omp_get_max_threads): " << max_threads << std::endl;


  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int total = omp_get_num_threads();

    #pragma omp criticial
    std::cout << "Sou a thread " << tid << " de " << total << std::endl;
  }


  return 0;
}