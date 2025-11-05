#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank = 0, size = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  cout << "Processo " << rank << " de " << size << " executando." << endl;
  MPI_Finalize();
  return 0;
}