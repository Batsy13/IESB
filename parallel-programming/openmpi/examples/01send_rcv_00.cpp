/*-------------------------------------------------------------------------------------------------------------------------
 * File Name : 
 * Author    : Prof. Rodrigo Gonçalves Pinto
 * Institution: IESB
 * Course    : Parallel and Distributed Programming
 * Objective : Demonstrar a comunicação ponto a ponto (point-to-point) com as funções MPI_Send e MPI_Recv.
 * Semester  : 2025/2
 * Version   : 2.0
 * 
 * History:
 *   Creation date : 2023-05-15
 *   Update date   : 2024-04-26
 *   Updated by    : Prof. Rodrigo Gonçalves Pinto
 *   Changes made  : Adapted for C++17; general code revision and documentation update.
 --------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------
 * Apache License, Version 2.0
 *-------------------------------------
 * Copyright (c) 2023–2025 Rodrigo Gonçalves Pinto
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Modifications: Please maintain all change logs in the "History" section above.
 */

/*-------------------------------------
 * NOTICE
 *-------------------------------------
 * Parallel Programming Examples in C++ (OpenMP and MPI)
 * Copyright (c) 2023–2025 Rodrigo Gonçalves Pinto
 *
 * This product includes software developed by Rodrigo Gonçalves Pinto.
 *
 * Academic Attribution:
 * If you use this software in academic or scientific work, please cite:
 *   Pinto, R. G. (2025). Parallel Programming Examples in C++ using OpenMP and MPI.
 *   ORCID: https://orcid.org/0009-0008-8360-9538
 *   University of São Paulo (USP) or University of Brasília (UnB).
 *
 * Any distribution of this software or derivative works must reproduce
 * this NOTICE file.
 */

/*-----------------------------------------------------------------------------------------------
 * Description:
 * Este é o próximo passo fundamental após o "Olá, Mundo". Enquanto no exemplo anterior
 * cada processo executava de forma independente, aqui eles começam a cooperar.
 * O processo com rank 0 (o "mestre") enviará uma mensagem contendo um número
 * inteiro para o processo com rank 1 (o "trabalhador"). O trabalhador, por sua vez, ficará
 * esperando até receber essa mensagem para então imprimi-la.
 *
 * How to compile:
 *   mpicxx 01send_recv.cpp -o 01send_recv
 *
 * How to execute (OBRIGATORIAMENTE com 2 ou mais processos):
 *   mpirun -np 4 ./01send_recv
 *
 * Expected output:
 *   Processo 0 enviando o número 42 para o processo 1.
 *   Processo 1 recebeu o número 42 do processo 0.
 *
 * Conceptual notes:
 *
 *   1. Comunicação Ponto a Ponto:
 *      É a forma mais básica de comunicação em MPI, envolvendo um processo que envia
 *      (remetente) e um processo que recebe (destinatário).
 *
 *   2. Operações de Bloqueio (Blocking Operations):
 *      Por padrão, MPI_Send e MPI_Recv são "bloqueantes". Este é um conceito crucial.
 * 
 * 
 *      - MPI_Recv: Quando um processo chama MPI_Recv, sua execução é PAUSADA. Ele fica
 *        "bloqueado" e não continua para a próxima linha de código até que a mensagem
 *        que ele está esperando (da origem e com a tag corretas) chegue completamente.
 *     
 * 
 *      - MPI_Send: Esta função também bloqueia o remetente. Ela só retorna (desbloqueia)
 *        quando a mensagem foi enviada com segurança. Na prática, isso muitas vezes significa
 *        que o envio só se completa quando o processo de destino já iniciou a chamada MPI_Recv
 *        correspondente.
 *
 *   3. Sincronização Implícita:
 *      A natureza bloqueante dessas funções cria um ponto de sincronização. O processo 1
 *      não pode avançar antes que o processo 0 envie os dados. O processo 0 pode ter que
 *      esperar o processo 1 estar pronto para receber antes de poder continuar.
 *
 *   4. Envelope da Mensagem (Tag, Source, Destination):
 *      Toda mensagem MPI viaja com um "envelope" que a identifica.
 *      - Destination (dest): O rank do processo que deve receber a mensagem.
 *      - Source (source): O rank do processo que enviou a mensagem. O receptor pode
 *        usar o valor especial `MPI_ANY_SOURCE` para aceitar uma mensagem de qualquer remetente.
 *      - Tag (tag): Uma etiqueta numérica (inteiro) que funciona como o "assunto" da mensagem.
 *        Ajuda a diferenciar diferentes tipos de mensagens entre os mesmos processos. O receptor
 *        pode usar `MPI_ANY_TAG` para aceitar uma mensagem com qualquer etiqueta.
 *
 *   5. Objeto MPI_Status:
 *      Quando um processo chama MPI_Recv, ele fornece um ponteiro para uma variável do tipo
 *      MPI_Status. Após a mensagem ser recebida, o MPI preenche essa variável com
 *      informações sobre a mensagem que acabou de chegar, como sua origem real (útil quando
 *      se usou MPI_ANY_SOURCE), sua tag real e seu tamanho.
 --------------------------------------------------------------------------------------------------------------------------*/



#include <iostream> // Para std::cout (saída padrão) e std::cerr (saída de erro).
#include <mpi.h>    // Cabeçalho principal da biblioteca MPI (Message Passing Interface).

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verificação de segurança: Este exemplo foi desenhado para uma comunicação
    // específica entre o processo 0 e o 1. Se não tivermos pelo menos 2 processos,
    // a lógica falhará. É uma boa prática verificar as condições mínimas de execução.
    if (size < 2) {
        // Apenas o processo mestre (rank 0) imprime a mensagem de erro para evitar
        // que 'size' mensagens idênticas poluam a saída.
        if (rank == 0) {
            std::cerr << "Erro: Este programa requer no mínimo 2 processos para funcionar." << std::endl;
            std::cerr << "Execute com: mpirun -np N ./seu_programa (onde N >= 2)" << std::endl;
        }
        MPI_Finalize();
        return 1; // Retornar um valor diferente de 0 sinaliza que o programa terminou com erro.
    }

    // A lógica do programa é dividida com base no 'rank' de cada processo.
    // Este é o padrão mais comum em programação MPI: cada processo descobre quem é
    // e então decide qual papel deve desempenhar.

    if (rank == 0) {
        // LÓGICA DO PROCESSO REMETENTE (MESTRE)
        // Este bloco de código será executado APENAS pelo processo de rank 0.

        int numero_para_enviar = 42; // O dado que queremos comunicar.
        int rank_destino = 1;        // O ID do processo para o qual queremos enviar a mensagem.
        int etiqueta = 0;            // Um "selo" ou "assunto" numérico para a mensagem. Ajuda a diferenciar mensagens.

        std::cout << "Processo " << rank << " (mestre) está enviando o número " << numero_para_enviar 
                  << " para o processo " << rank_destino << "." << std::endl;

        /*
         * MPI_Send: Envia uma mensagem para outro processo. É uma operação BLOQUEANTE.
         * O processo 0 irá pausar nesta linha e só continuará sua execução após ter certeza
         * de que a mensagem foi entregue com segurança (o que geralmente significa que o
         * processo de destino já chamou o MPI_Recv correspondente).
         *
         * Seus parâmetros podem ser lidos como uma frase:
         * "MPI, envie os dados que estão em [1], são [2] elementos do tipo [3],
         *  para o processo [4], com a etiqueta [5], dentro do grupo de comunicação [6]."
         */
        MPI_Send(
            &numero_para_enviar, // 1. O DADO: Ponteiro para a variável que contém a informação a ser enviada.
            1,                   // 2. A CONTAGEM: Quantos elementos estamos enviando? (Neste caso, apenas um inteiro).
            MPI_INT,             // 3. O TIPO: O tipo de dado MPI correspondente ao que estamos enviando.
            rank_destino,        // 4. O DESTINO: O rank do processo que deve receber a mensagem.
            etiqueta,            // 5. A ETIQUETA (TAG): Um número inteiro para identificar a mensagem. O receptor deve usar a mesma tag.
            MPI_COMM_WORLD       // 6. O COMUNICADOR: O grupo de processos no qual a comunicação ocorre.
        );

    } else if (rank == 1) {
        // LÓGICA DO PROCESSO DESTINATÁRIO (TRABALHADOR)
        // Este bloco de código será executado APENAS pelo processo de rank 1.

        int numero_recebido;   // Uma "caixa" vazia para guardar o dado que chegará.
        int rank_origem = 0;   // De qual processo estamos esperando receber a mensagem?
        int etiqueta = 0;      // Qual a etiqueta da mensagem que estamos aguardando?
        MPI_Status status;     // Objeto que guardará informações sobre a mensagem recebida (metadados).

        /*
         * MPI_Recv: Recebe uma mensagem de outro processo. É uma operação BLOQUEANTE.
         * O processo 1 ficará "congelado" nesta linha, esperando indefinidamente, até que
         * uma mensagem que corresponda à origem (source) e à etiqueta (tag) especificadas chegue.
         *
         * Seus parâmetros podem ser lidos como:
         * "MPI, estou preparado para receber dados. Guarde-os em [1], minha capacidade é de [2] elementos
         *  do tipo [3]. Estou esperando que venham do processo [4] com a etiqueta [5], dentro do
         *  grupo [6]. Por favor, preencha os detalhes da entrega no meu 'recibo' [7]."
         */
        MPI_Recv(
            &numero_recebido,    // 1. O BUFFER: Ponteiro para a variável onde o dado recebido será armazenado.
            1,                   // 2. A CAPACIDADE: O tamanho máximo do buffer (quantos elementos ele pode receber).
            MPI_INT,             // 3. O TIPO: O tipo de dado que esperamos receber.
            rank_origem,         // 4. A ORIGEM: O rank do processo do qual esperamos a mensagem. (Poderia ser MPI_ANY_SOURCE para aceitar de qualquer um).
            etiqueta,            // 5. A ETIQUETA (TAG): A etiqueta da mensagem que esperamos. (Poderia ser MPI_ANY_TAG).
            MPI_COMM_WORLD,      // 6. O COMUNICADOR: O grupo de processos.
            &status              // 7. O STATUS: Ponteiro para o objeto de status que será preenchido. É o "recibo" da mensagem.
        );

        // Esta linha só será executada DEPOIS que a mensagem for completamente recebida.
        // Usamos status.MPI_SOURCE para confirmar de quem recebemos a mensagem.
        // Isso é especialmente útil quando usamos MPI_ANY_SOURCE na chamada de MPI_Recv.
        std::cout << "Processo " << rank << " (trabalhador) recebeu o número " << numero_recebido 
                  << " do processo " << status.MPI_SOURCE << "." << std::endl;
    }
    
    // E os outros processos (rank 2, 3, ...)?
    // Neste programa, eles não fazem nada de útil. Eles são inicializados,
    // descobrem que seu rank não é 0 nem 1, e pulam diretamente para o MPI_Finalize.
    // Mesmo sem realizar trabalho, sua participação no ambiente MPI é obrigatória.

    MPI_Finalize();
    return 0;
}