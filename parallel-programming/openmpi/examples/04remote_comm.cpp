/*-------------------------------------------------------------------------------------------------------------------------
 * File Name : 04remote_comm.cpp
 * Author    : Prof. Rodrigo Gonçalves Pinto
 * Course    : Parallel and Distributed Programming
 * Objective : Demonstrar que o código MPI é agnóstico à localização física dos processos.
 * Semester  : 2025/2
 * Version   : 2.0
 --------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------
 * Description:
 * Este código demonstra uma comunicação simples ponto a ponto. A sua principal lição
 * pedagógica é que ele funcionará da MESMA FORMA, sem NENHUMA alteração, quer os
 * processos 0 e 1 estejam na mesma máquina ou em máquinas diferentes em um cluster.
 *
 * A decisão de ONDE cada processo é executado é feita no momento da execução pelo
 * comando 'mpirun', geralmente com a ajuda de um 'hostfile', e não dentro do código C++.
 *
 * How to compile:
 *   mpicxx 04remote_comm.cpp -o 04remote_comm
 *
 * How to execute in a REAL CLUSTER (com um hostfile chamado 'meu_cluster.txt'):
 *   mpirun -np 2 --hostfile meu_cluster.txt ./04remote_comm
 *
 * How to SIMULATE LOCALLY (mesmo sem um cluster):
 *   (Crie um hostfile chamado 'local.txt' contendo apenas "localhost slots=2")
 *   mpirun -np 2 --hostfile local.txt ./04remote_comm
 *
 --------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            std::cerr << "Erro: Este programa precisa de pelo menos 2 processos." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        //  LÓGICA DO PROCESSO MESTRE (rank 0) 
        // Este código não sabe nem precisa saber se o processo 1 está
        // na mesma máquina ou em outra, conectada pela rede.
        // Ele apenas sabe que precisa enviar uma mensagem para o "rank 1".

        std::string mensagem = "Olá do processo mestre na máquina A!";
        int destino = 1;
        int etiqueta = 0;

        std::cout << "Processo 0 enviando mensagem para o processo " << destino << std::endl;

        // MPI_Send envia os dados. O sistema MPI se encarrega de encontrar
        // onde o processo 'destino' está fisicamente e entregar a mensagem via rede.
        MPI_Send(
            mensagem.c_str(),       // Ponteiro para os dados da string
            mensagem.length() + 1,  // Tamanho, incluindo o caractere nulo de terminação '\0'
            MPI_CHAR,               // Tipo de dado
            destino,                // Rank do destino
            etiqueta,               // Etiqueta da mensagem
            MPI_COMM_WORLD
        );

    } else if (rank == 1) {
        // --- LÓGICA DO PROCESSO TRABALHADOR (rank 1) ---
        // Este processo pode estar em qualquer máquina do cluster.
        // Ele apenas espera por uma mensagem do "rank 0".

        char buffer[256]; // Um buffer com espaço para receber a mensagem.
        int origem = 0;
        int etiqueta = 0;
        MPI_Status status;

        std::cout << "Processo 1 está aguardando uma mensagem do processo " << origem << std::endl;

        // MPI_Recv bloqueia até a mensagem chegar, seja de um processo local ou remoto.
        MPI_Recv(
            buffer,          // Buffer para armazenar a mensagem
            256,             // Tamanho máximo do buffer
            MPI_CHAR,        // Tipo de dado esperado
            origem,          // Rank da origem esperada
            etiqueta,        // Etiqueta esperada
            MPI_COMM_WORLD,
            &status
        );
        
        std::cout << "Processo 1 recebeu a mensagem: \"" << buffer << "\"" << std::endl;
    }

    MPI_Finalize();
    return 0;
}