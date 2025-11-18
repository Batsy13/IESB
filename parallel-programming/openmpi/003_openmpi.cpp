#include <iostream>
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

    int token;
    int dest = (rank + 1) % size;
    int source = (rank - 1 + size) % size;

    if (rank == 0)
    {
        token = 100;
        std::cout << "Processo 0 inicia o anel com o token = " << token << "." << std::endl;
        
        usleep(500);
        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        
        usleep(500);
        MPI_Recv(&token, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::cout << "Processo 0 recebeu o token de volta do processo " << source << ". Anel completo." << std::endl;
    }
    else
    {
        MPI_Recv(&token, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::cout << "Processo " << rank << " recebeu o token = " << token << "." << std::endl;
        
        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}