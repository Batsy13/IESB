#include <iostream>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 2)
  {
    if (rank == 0)
      std::cerr << "Erro: Necessário 2 processos." << std::endl;
    MPI_Finalize();
    return 1;
  }

  int number = 0;
  int changes_per_proccess = 5;

  if (rank == 0)
  {
    for (int i = 0; i < changes_per_proccess; i++)
    {
      MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

      MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      if (i == changes_per_proccess - 1)
      {
        std::cout << "Processo 0 recebeu " << number << ", finalizando." << std::endl;
      }
      else
      {
        number++;
        std::cout << "Processo 0 recebeu " << number - 1 << ", enviando " << number << "." << std::endl;
      } 
      usleep(1000);
    }
  }
  else if (rank == 1)
  {
    for (int i = 0; i < changes_per_proccess; i++)
    {
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      std::cout << "Processo 1 recebeu " << number << ", enviando " << number + 1 << "." << std::endl;
      
      usleep(1000);

      number++;
      MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}