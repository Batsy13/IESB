/*

Sincronização com OpenMP - conceitos

1. Pragma omp critical
    - Região crítica! Só permite que uma thread utilize-a por vez, evitando problemas de sincronização

2. Pargma omp atomic
    - Funcionamento igual a pragma omp critical
    - Não abre bloco de sincronização.
    - Utilizado para expressões simples, como uma soma.

3. Pragma omp barrier
    - Cria uma sequencia ( barreira ) entre dois processos. 
    - Um processo que dependa de outro é barrado de ser executado até que o primeiro seja concluído.

4. Pragma omp ordered
    - Garante que uma parte do código dentro de um laço paralelo seja executada na ordem original das iterações

5. omp_set_lock
6. omp_unset_lock
7. omp_init_lock
8. omp_destroy_lock

Essas funções são usadas para criar e gerenciar locks (bloqueios) em OpenMP.
Elas oferecem um controle mais fino sobre a sincronização em comparação com as diretivas pragma.
Exemplo de uso:

omp_lock_t lock;
omp_init_lock(&lock);

#pragma omp parallel
{
    omp_set_lock(&lock);
    // seção crítica
    omp_unset_lock(&lock);
}

*/