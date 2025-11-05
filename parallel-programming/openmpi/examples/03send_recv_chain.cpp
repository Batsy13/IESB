/*-------------------------------------------------------------------------------------------------------------------------
 * File Name : 03send_recv_chain.cpp
 * Author    : Prof. Rodrigo Gonçalves Pinto
 * Institution: IESB
 * Course    : Parallel and Distributed Programming
 * Objective : Demonstrar um fluxo de comunicação em cadeia com envio e recebimento múltiplos (ida e volta).
 * Semester  : 2025/2
 * Version   : 2.0
 * 
 * History:
 *   Creation date : 2025-11-02
 *   Updated by    :Prof. Rodrigo Gonçalves Pinto
 *   Changes made  : Criado para ilustrar um padrão de comunicação P0 -> P1 -> P0 -> P2. Escrever lousa
 --------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------
 * Apache License, Version 2.0 & NOTICE
 *-------------------------------------
 * (Mantido conforme o original)
 */

/*-----------------------------------------------------------------------------------------------
 * Description:
 * Este programa simula um fluxo de trabalho distribuído mais complexo.
 * A comunicação ocorre em várias etapas, demonstrando como os processos podem colaborar
 * em uma tarefa sequencial.
 *
 * Fluxo de Execução:
 *   1. Processo 0 cria um vetor de inteiros e o envia para o Processo 1.
 *   2. Processo 1 recebe o vetor, calcula a média de seus elementos e envia o resultado
 *      (um valor 'double') de volta para o Processo 0.
 *   3. Processo 0 recebe a média, adiciona 10 a ela e envia o novo valor para o Processo 2.
 *   4. Processo 2 recebe este valor final, adiciona 20 e imprime o resultado na tela.
 *
 * How to compile:
 *   mpicxx 03send_recv_chain.cpp -o 03send_recv_chain
 *
 * How to execute (OBRIGATORIAMENTE com 3 ou mais processos):
 *   mpirun -np 3 ./03send_recv_chain
 *
 * Expected output (a ordem das mensagens de status pode variar):
 *   Processo 0 (mestre) enviando vetor [10, 20, 30, 40, 50] para o processo 1.
 *   Processo 1 (worker 1) aguardando vetor do processo 0...
 *   Processo 2 (worker 2) aguardando resultado do processo 0...
 *   Processo 1 recebeu o vetor e está calculando a média.
 *   Processo 1 calculou a média (30.00) e está enviando de volta para o processo 0.
 *   Processo 0 aguardando a média do processo 1...
 *   Processo 0 recebeu a média 30.00. Somando 10, o novo valor é 40.00.
 *   Processo 0 enviando o valor 40.00 para o processo 2.
 *   Processo 2 recebeu o valor 40.00. Somando 20.
 *   >>> Processo 2: O RESULTADO FINAL É 60.00. 
 *
 * Conceptual notes:
 *
 *   1. A Importância das Etiquetas (Tags):
 *      Neste exemplo, o Processo 0 tanto envia quanto recebe. Para evitar ambiguidade,
 *      usamos ETIQUETAS DIFERENTES para cada tipo de mensagem.
 *      - Tag 1: Usada para a mensagem "vetor de P0 para P1".
 *      - Tag 2: Usada para a mensagem "média de P1 para P0".
 *      - Tag 3: Usada para a mensagem "resultado de P0 para P2".
 *      Isso garante que o MPI_Recv capture exatamente a mensagem que está esperando.
 *
 *   2. Deadlock (Impasse):
 *      Um risco em comunicações complexas é o 'deadlock'. Ocorreria se, por exemplo,
 *      P0 tentasse receber de P1 ANTES de enviar o vetor. P0 ficaria esperando para sempre
 *      por uma mensagem que P1 só enviaria depois de receber o vetor. A ordem das
 *      operações Send/Recv é crucial para evitar impasses.
 *
 --------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <numeric> // Para std::accumulate
#include <vector>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3) {
        if (rank == 0) {
            std::cerr << "Erro: Este programa precisa de pelo menos 3 processos para ser executado." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Definimos etiquetas distintas para cada tipo de comunicação para evitar ambiguidades.
    const int TAG_VETOR_P0_P1 = 1;
    const int TAG_MEDIA_P1_P0 = 2;
    const int TAG_VALOR_P0_P2 = 3;

    if (rank == 0) {
        // --- LÓGICA DO PROCESSO 0 (MESTRE / ORQUESTRADOR) ---
        const int TAMANHO_VETOR = 5;
        int vetor_dados[TAMANHO_VETOR] = {10, 20, 30, 40, 50};
        
        // Etapa 1: Enviar o vetor para o Processo 1
        std::cout << "Processo 0 (mestre) enviando vetor para o processo 1." << std::endl;
        MPI_Send(vetor_dados, TAMANHO_VETOR, MPI_INT, 1, TAG_VETOR_P0_P1, MPI_COMM_WORLD);

        // Etapa 2: Receber a média calculada pelo Processo 1
        double media_recebida;
        MPI_Status status1;
        std::cout << "Processo 0 aguardando a média do processo 1..." << std::endl;
        MPI_Recv(&media_recebida, 1, MPI_DOUBLE, 1, TAG_MEDIA_P1_P0, MPI_COMM_WORLD, &status1);
        
        // Etapa 3: Processar o resultado e enviar para o Processo 2
        double valor_para_p2 = media_recebida + 10.0;
        std::cout << "Processo 0 recebeu a média " << media_recebida << ". Somando 10, o novo valor é " << valor_para_p2 << "." << std::endl;
        std::cout << "Processo 0 enviando o valor " << valor_para_p2 << " para o processo 2." << std::endl;
        MPI_Send(&valor_para_p2, 1, MPI_DOUBLE, 2, TAG_VALOR_P0_P2, MPI_COMM_WORLD);

    } else if (rank == 1) {
        // --- LÓGICA DO PROCESSO 1 (WORKER 1 - CÁLCULO DA MÉDIA) ---
        const int TAMANHO_VETOR_ESPERADO = 5;
        int vetor_recebido[TAMANHO_VETOR_ESPERADO];
        MPI_Status status2;

        std::cout << "Processo 1 (worker 1) aguardando vetor do processo 0..." << std::endl;
        MPI_Recv(vetor_recebido, TAMANHO_VETOR_ESPERADO, MPI_INT, 0, TAG_VETOR_P0_P1, MPI_COMM_WORLD, &status2);
        
        std::cout << "Processo 1 recebeu o vetor e está calculando a média." << std::endl;
        double soma = 0.0;
        for (int i = 0; i < TAMANHO_VETOR_ESPERADO; ++i) {
            soma += vetor_recebido[i];
        }
        double media = soma / TAMANHO_VETOR_ESPERADO;

        std::cout << "Processo 1 calculou a média (" << media << ") e está enviando de volta para o processo 0." << std::endl;
        MPI_Send(&media, 1, MPI_DOUBLE, 0, TAG_MEDIA_P1_P0, MPI_COMM_WORLD);

    } else if (rank == 2) {
        // --- LÓGICA DO PROCESSO 2 (WORKER 2 - RESULTADO FINAL) ---
        double valor_recebido;
        MPI_Status status3;

        std::cout << "Processo 2 (worker 2) aguardando resultado do processo 0..." << std::endl;
        MPI_Recv(&valor_recebido, 1, MPI_DOUBLE, 0, TAG_VALOR_P0_P2, MPI_COMM_WORLD, &status3);

        std::cout << "Processo 2 recebeu o valor " << valor_recebido << ". Somando 20." << std::endl;
        double resultado_final = valor_recebido + 20.0;
        
        // Impressão final destacada para fácil visualização
        std::cout << "\n>>> Processo " << rank << ": O RESULTADO FINAL É " << resultado_final << ". <<<\n" << std::endl;
    }

    MPI_Finalize();
    return 0;
}