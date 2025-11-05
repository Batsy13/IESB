/*-------------------------------------------------------------------------------------------------------------------------
 * File Name : 02send_recv_array.cpp
 * Author    : Prof. Rodrigo Gonçalves Pinto
 * Institution: IESB
 * Course    : Parallel and Distributed Programming
 * Objective : Demonstrar a comunicação ponto a ponto (point-to-point) enviando um vetor (array) de dados.
 * Semester  : 2025/2
 * Version   : 2.0
 * 
 * History:
 *   Creation date : 2025-11-02
 *   Updated by    :  Prof. Rodrigo Gonçalves Pinto
 *   Changes made  : envio de múltiplos dados (vetor).
 --------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------
 * Apache License, Version 2.0 & NOTICE
 *-------------------------------------
 * (Mantido conforme o original)
 */

/*-----------------------------------------------------------------------------------------------
 * Description:
 * Este programa é a evolução do exemplo anterior. Em vez de enviar um único número,
 * o processo 0 irá criar, preencher e enviar um VETOR (array) inteiro para o processo 1.
 * Este exemplo destaca a importância do parâmetro 'count' nas funções MPI_Send e MPI_Recv,
 * que especifica quantos elementos estão sendo transferidos.
 *
 * How to compile:
 *   mpicxx 02send_recv_array.cpp -o 02send_recv_array
 *
 * How to execute (OBRIGATORIAMENTE com 2 ou mais processos):
 *   mpirun -np 2 ./02send_recv_array
 *
 * Expected output:
 *   Processo 0 (mestre) enviando vetor para o processo 1.
 *   Processo 1 (trabalhador) aguardando para receber o vetor do processo 0...
 *   Processo 1 recebeu o vetor com sucesso! Conteúdo:
 *   Vetor[0] = 10
 *   Vetor[1] = 20
 *   Vetor[2] = 30
 *   Vetor[3] = 40
 *   Vetor[4] = 50
 *
 * Conceptual notes:
 *
 *   1. Contiguidade de Memória:
 *      Vetores em C++ são armazenados em blocos contíguos de memória. O MPI é
 *      extremamente eficiente para transferir esses blocos de uma só vez. Ao enviar
 *      um vetor, você simplesmente aponta para o seu primeiro elemento, e o MPI,
 *      sabendo a contagem e o tipo de dado, cuida do resto.
 *
 *   2. O Parâmetro `count`:
 *      No exemplo anterior, `count` era 1. Agora, ele será o número de elementos no
 *      vetor. É crucial que tanto o remetente quanto o destinatário concordem sobre
 *      a quantidade de dados. O `count` no MPI_Recv especifica o TAMANHO MÁXIMO do
 *      buffer, que deve ser grande o suficiente para conter os dados recebidos.
 *
 *   3. Sincronização e Acordo:
 *      Para que a comunicação funcione, é fundamental que haja um "acordo" entre
 *      o remetente e o destinatário:
 *      - O tipo de dado (ex: MPI_INT) deve ser o mesmo.
 *      - A etiqueta (tag) deve ser a mesma.
 *      - O buffer do receptor deve ter capacidade para, no mínimo, a quantidade de
 *        dados que o remetente está enviando, para evitar erros de 'buffer overflow'.
 *
 --------------------------------------------------------------------------------------------------------------------------*/

#include <iostream> // Para std::cout e std::cerr
#include <vector>   // Embora usemos um array C-style, <vector> é o padrão moderno em C++.
#include <mpi.h>    // Cabeçalho principal da biblioteca MPI

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            std::cerr << "Erro: Este programa precisa de pelo menos 2 processos para ser executado." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Definimos uma constante para o tamanho do vetor.
    // É uma boa prática para evitar "números mágicos" no código.
    const int TAMANHO_VETOR = 5;
    const int rank_destino = 1;
    const int rank_origem = 0;
    const int etiqueta = 0;

    if (rank == 0) {
        // --- LÓGICA DO PROCESSO REMETENTE (MESTRE) ---

        int vetor_para_enviar[TAMANHO_VETOR];

        // Preenche o vetor com dados de exemplo.
        std::cout << "Processo " << rank << " (mestre) preparando e enviando o vetor para o processo " << rank_destino << "." << std::endl;
        for (int i = 0; i < TAMANHO_VETOR; ++i) {
            vetor_para_enviar[i] = (i + 1) * 10;
        }

        /*
         * MPI_Send para um VETOR. A lógica é a mesma, mas agora o parâmetro 'count'
         * é fundamental. Ele diz ao MPI quantos elementos, a partir do ponteiro inicial,
         * devem ser enviados.
         */
        MPI_Send(
            vetor_para_enviar,   // 1. O DADO: Ponteiro para o início do vetor (o nome do array já é um ponteiro).
            TAMANHO_VETOR,       // 2. A CONTAGEM: O número de elementos no vetor. ESTE É O PONTO-CHAVE!
            MPI_INT,             // 3. O TIPO: O tipo de cada elemento no vetor.
            rank_destino,        // 4. O DESTINO: O rank do processo que deve receber.
            etiqueta,            // 5. A ETIQUETA (TAG): Identificador da mensagem.
            MPI_COMM_WORLD       // 6. O COMUNICADOR.
        );

    } else if (rank == 1) {
        // --- LÓGICA DO PROCESSO DESTINATÁRIO (TRABALHADOR) ---

        int vetor_recebido[TAMANHO_VETOR]; // Buffer para armazenar os dados recebidos.
        MPI_Status status;                 // Objeto para os metadados da mensagem.

        std::cout << "Processo " << rank << " (trabalhador) aguardando para receber o vetor do processo " << rank_origem << "..." << std::endl;

        /*
         * MPI_Recv para um VETOR. O processo ficará bloqueado aqui até que o vetor
         * do processo 0 chegue. O parâmetro 'count' informa a capacidade máxima do buffer.
         */
        MPI_Recv(
            vetor_recebido,      // 1. O BUFFER: Ponteiro para o início do vetor onde os dados serão guardados.
            TAMANHO_VETOR,       // 2. A CAPACIDADE: O número máximo de elementos que este buffer pode receber.
            MPI_INT,             // 3. O TIPO: O tipo de dado esperado.
            rank_origem,         // 4. A ORIGEM: De qual processo estamos esperando.
            etiqueta,            // 5. A ETIQUETA (TAG): Qual mensagem estamos esperando.
            MPI_COMM_WORLD,      // 6. O COMUNICADOR.
            &status              // 7. O STATUS: Para obter detalhes da recepção.
        );

        // Após o recebimento, imprimimos os dados para verificação.
        std::cout << "Processo " << rank << " recebeu o vetor com sucesso! Conteúdo:" << std::endl;
        for (int i = 0; i < TAMANHO_VETOR; ++i) {
            std::cout << "  Vetor[" << i << "] = " << vetor_recebido[i] << std::endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}