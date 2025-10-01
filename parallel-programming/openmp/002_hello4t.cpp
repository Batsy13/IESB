#include <iostream>
#include <sstream>
#include <omp.h>

int main() {

  #pragma omp parallel num_threads(4)
  {
    int tid = omp_get_thread_num();
    int tot = omp_get_num_threads();

    std::ostringstream oss;

    oss << "Hello, world from thread " << tid + 1
        << " of " << tot << "\n";

    #pragma omp critical
    {
      std::cout << oss.str();
    }
  }

  return 0;
}