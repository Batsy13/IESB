#include <iostream>
#include <vector>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size < 2)
  {
    if (rank == 0)
      std::cerr << "Erro: Requer pelo menos 2 processos." << std::endl;
    MPI_Finalize();
    return 1;
  }

  const int TOTAL = 120;
  const int num_workers = size - 1;
  int total_sum = 0;

  if (rank == 0)
  {
    if (TOTAL % (num_workers) != 0)
    {
      std::cerr << "Erro: O tamanho do vetor não é divisível pelo número de trabalhadores." << std::endl;
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    std::cout << "Mestre (P0): Dividindo o trabalho para " << num_workers << " trabalhadores" << std::endl;
    usleep(50);

    std::vector<int> main_vector(TOTAL, 1);
    int chunk_size = TOTAL / num_workers;

    for (int dest = 1; dest <= num_workers; dest++)
    {
      int start_index = (dest - 1) * chunk_size;
      MPI_Send(&main_vector[start_index], chunk_size, MPI_INT, dest, dest, MPI_COMM_WORLD);
    }

    int partial_sum = 0;
    for (int source = 1; source <= num_workers; source++)
    {
      MPI_Status status;
      MPI_Recv(&partial_sum, 1, MPI_INT, source, source, MPI_COMM_WORLD, &status);
      total_sum += partial_sum;
    }
  
    usleep(50);
    std::cout << "Mestre (P0): Recebi todas as somas parciais." << std::endl;
    std::cout << "Mestre (P0): A SOMA TOTAL É: " << total_sum << std::endl;
  }
  else
  {
    int chunk_size = TOTAL / num_workers;
    std::vector<int> worker_vector(chunk_size);
    MPI_Status status;

    MPI_Recv(worker_vector.data(), chunk_size, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);

    int partial_sum = 0;
    for (int i = 0; i < chunk_size; i++)
    {
      partial_sum += worker_vector[i];
    }

    std::cout << "Trabalhador (P" << rank << "): Recebi minha parte, minha soma parcial é: "
              << partial_sum << std::endl;

    MPI_Send(&partial_sum, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}