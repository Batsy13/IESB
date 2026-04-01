import numpy as np
import random
import matplotlib.pyplot as plt

""" Algoritmo Genético para otimização de cardápios semanais baseado no artigo "Algoritmo Genético para Elaboração de Cardápios Nutricionais para Alimentação Escolar" """

# --- 1. BANCO DE DADOS ---

banco_alimentos = {
    "Frutas_Sobremesa": {
        "Banana": [90, 1, 22, 0, 1.20, 4, 1], "Maçã": [52, 0, 14, 0, 1.50, 3, 1], "Laranja": [45, 1, 11, 0, 1.00, 4, 1]
        },
    "Leites": {
        "Leite": [120, 6, 9, 7, 2.00, 1, 3], "Iogurte": [140, 6, 18, 5, 2.80, 1, 2]
        },
    "Paes_Cereais": {
        "Pão": [150, 4, 30, 3, 0.80, 4, 1], "Biscoito": [130, 3, 25, 4, 1.10, 4, 1]
        },
    "Entrada": {
        "Salada Alface": [15, 1, 2, 0, 1.50, 2, 1], "Salada Tomate": [20, 1, 4, 0, 1.80, 3, 1]
        },
    "Acomp_Arroz": {
        "Arroz Branco": [130, 2, 28, 0, 0.80, 1, 1], "Arroz Integral": [120, 3, 25, 1, 1.20, 4, 1]
        },
    "Acomp_Feijao": {
        "Feijão Preto": [100, 6, 18, 1, 1.00, 4, 1], "Feijão Carioca": [95, 5, 17, 1, 0.90, 4, 1]
        },
    "Guarnicao": {
        "Purê Batata": [120, 2, 25, 4, 1.50, 1, 2], "Couve": [50, 2, 6, 3, 1.80, 2, 1]
        },
    "Prato_Principal": {
        "Frango": [200, 25, 0, 10, 3.50, 1, 1], "Omelete": [210, 14, 2, 16, 2.00, 4, 1], "Peixe": [180, 22, 0, 8, 4.50, 1, 1]
        },
    "Suco": {
        "Suco Laranja": [90, 1, 20, 0, 1.20, 4, 3], "Suco Uva": [110, 1, 25, 0, 1.50, 3, 3]}
}

# --- 2. CONFIGURAÇÕES TÉCNICAS ---

ESTRUTURA = {
    "Desjejum": ["Frutas_Sobremesa", "Leites", "Paes_Cereais"],
    "Almoço":   ["Entrada", "Acomp_Arroz", "Acomp_Feijao", "Guarnicao", "Prato_Principal", "Frutas_Sobremesa", "Suco"], 
    "Lanche":   ["Frutas_Sobremesa", "Leites", "Paes_Cereais", "Suco"], 
    "Jantar":   ["Entrada", "Acomp_Arroz", "Acomp_Feijao", "Guarnicao", "Prato_Principal", "Frutas_Sobremesa", "Suco"]
}
ORDEM_DIA = ["Desjejum", "Almoço", "Lanche", "Jantar"]
DIAS = 7
ITENS_DIA = 20 
METAS = np.array([2300, 80, 300, 60])
LIMITE_CUSTO_REF = 3.50

META_ITENS_UNICOS = 25 
PESO_VARIEDADE = 40 
PESO_EXCESSO_CUSTO = 50 
PESO_REPETICAO_VISUAL = 100 
LIMITE_REP_MESMO_PRATO = 3 
TAM_POP = 200

# --- 3. FUNÇÕES DE EVOLUÇÃO ---

def criar_individuo():
    """
        Cria um cardápio semanal selecionando aleatoriamente um alimento de cada categoria para cada refeição do dia.
    """
    # ind é uma lista que armazena o gene do individuo.
    ind = []
    # loop que percorre cada dia e cada refeição e seleciona aleatoriamente um alimento de cada categoria para compor o cardápio do dia.
    for _ in range(DIAS):
        for ref in ORDEM_DIA:
            for cat in ESTRUTURA[ref]:
                ind.append((cat, random.choice(list(banco_alimentos[cat].keys()))))
    return ind

def calcular_fitness(ind):
    """
        Calcula o fitness de um indivíduo com base no erro nutricional, custo total do cardápio e penalidades por restrições.
    """
    
    # variavies para acumular os nutrientes totais, custo total do cardápio e penalidades por restrições.
    totais_nutrientes = np.zeros(4)
    custo_total_cardapio = 0
    penalidade_restricoes = 0
    
    # loop que percorre cada dia do cardápio e aplica as penalidades, calcula o custo da refeição e calcula os nutrientes totais fornecidos.
    for d in range(DIAS):
        # dia_genes é uma lista que armazena os genes dos alimentos selecionados para o dia d.
        dia_genes = ind[d*ITENS_DIA : (d+1)*ITENS_DIA]
        # variavel de referencia para percorrer os genes do dia.
        ptr = 0
        for ref_nome in ORDEM_DIA:
            
            # número de categorias da refeição
            n = len(ESTRUTURA[ref_nome])
            # lista que armazena os genes dos alimentos selecionados para a refeição atual.
            refeicao = dia_genes[ptr : ptr+n]
            
            # Cálculo de Nutrientes e Custo da Refeição
            custo_refeicao = sum(banco_alimentos[c][nm][4] for c, nm in refeicao)
            cores = [banco_alimentos[c][nm][5] for c, nm in refeicao]
            consistencias = [banco_alimentos[c][nm][6] for c, nm in refeicao]
            
            custo_total_cardapio += custo_refeicao
            for c, nm in refeicao: totais_nutrientes += banco_alimentos[c][nm][:4]
            
            # Eq (19): Penalidade de Custo Financeiro por Refeição
            # No artigo, cd é o limite estabelecido para a refeição j
            if custo_refeicao > LIMITE_CUSTO_REF: 
                excesso = custo_refeicao - LIMITE_CUSTO_REF
                penalidade_restricoes += excesso * PESO_EXCESSO_CUSTO
            
            # Eq (16): Penalidade de Características Sensoriais (Cor e Consistência)
            # Pune a repetição excessiva de uma mesma característica no prato
            for atributos in [cores, consistencias]:
                for tipo in set(atributos):
                    repeticoes = atributos.count(tipo)
                    if repeticoes >= LIMITE_REP_MESMO_PRATO: 
                        # Penalidade linear conforme o grau de repetição
                        penalidade_restricoes += PESO_REPETICAO_VISUAL * (repeticoes - (LIMITE_REP_MESMO_PRATO - 1))
            ptr += n

    # Eq (17): Penalidade de Variedade Alimentar (Quadrática)
    # Garante a diversidade de alimentos para suprir micronutrientes
    alimentos_unicos = len(set([nome for cat, nome in ind]))
    if alimentos_unicos < META_ITENS_UNICOS:
        deficit_variedade = META_ITENS_UNICOS - alimentos_unicos
        penalidade_restricoes += PESO_VARIEDADE * (deficit_variedade ** 2)
    
    # Função Objetivo f1: Minimização do Erro Nutricional
    # Diferença absoluta entre o fornecido e a referência
    erro_nutricional = np.sum(np.abs(totais_nutrientes - (METAS * DIAS)))
    
    # Função de Escalarização (Soma Ponderada)
    # Combina f1 (Erro Nutricional) e f2 (Custo Total) + Penalidades
    return (0.7 * erro_nutricional) + (0.3 * custo_total_cardapio) + penalidade_restricoes

def selecao_torneio(populacao, notas, k=3):
    selecionados = random.sample(range(len(populacao)), k)
    vencedor_idx = selecionados[np.argmin([notas[i] for i in selecionados])]
    return populacao[vencedor_idx]

def crossover_segmentado(p1, p2):
    """"
        Realiza crossover segmentado entre dois pais, trocando segmentos inteiros de refeições para preservar a estrutura do cardápio.
    """
    # variáveis onde será armazenado os filhos gerados a partir do crossover.
    f1, f2 = [], []
    # ptr é um ponteiro que indica a posição atual no individuo.
    ptr = 0
    
    # for que percorre cada refeição do dia selecionando um ponto de corte aleatório.
    for _ in range(DIAS):
        for ref in ORDEM_DIA:
            # n é o número de categorias da refeição atual.
            n = len(ESTRUTURA[ref])
            # cp é o ponto de corte aleatório entre 1 e n-1, garantindo que haja troca de pelo menos um item.
            cp = random.randint(1, n-1)
            
            # o crossover é aplicado trocando os segmentos em f1 e f2.
            f1.extend(p1[ptr : ptr+cp] + p2[ptr+cp : ptr+n])
            f2.extend(p2[ptr : ptr+cp] + p1[ptr+cp : ptr+n])
            ptr += n
    return f1, f2


def mutacao(ind, taxa=0.1):
    """
        Realiza mutação em um indivíduo, alterando aleatoriamente um alimento com uma nova escolha do mesmo grupo.
    """
    # cópia do indivíduo.
    novo_ind = list(ind)
    
    # loop que percorre cada gene do individuo e realiza uma mutação com uma probabilidade n.
    for i in range(len(novo_ind)):
        if random.random() < taxa:
            cat = novo_ind[i][0]
            novo_ind[i] = (cat, random.choice(list(banco_alimentos[cat].keys())))
            
    # indivíduo com a mutação.
    return novo_ind

# --- 4. LOOP EVOLUTIVO ---

pop = [criar_individuo() for _ in range(200)]
historico_melhor_fitness = []

# For que percorre n gerações, calculando o fitness de cada indivíduo, selecionando os melhores, realizando
# crossover e mutação para criar a nova população, e armazenando o melhor fitness de cada geração para análise posterior.
for g in range(500):
    
    # notas é uma lista que armazena o valor de cada indivíduo na população.
    notas = [calcular_fitness(i) for i in pop]
    
    # melhor_atual é o menor valor de fitness encontrado.
    melhor_atual = min(notas)
    
    # historico_melhor_fitness é uma lista com os melhores fitness de cada geração.
    historico_melhor_fitness.append(melhor_atual)
    
    # nova_pop será onde os indivíduos selecionados ficara armazenados para a próxima geração.
    nova_pop = []
    
    # indices_elite é uma lista com os índices dos 2 melhores indivíduos da população atual.
    indices_elite = np.argsort(notas)[:2]
    
    # For responsável por adicionar os 2 melhores indivíduos da população atual para a nova população.
    for idx in indices_elite:
        nova_pop.append(pop[idx])

    # Loop que continua até que a nova população tenha 200 indivíduos, realizando a seleção por torneio, crossover e mutação para gerar novos indivíduos.
    while len(nova_pop) < TAM_POP:
        pai1 = selecao_torneio(pop, notas)
        pai2 = selecao_torneio(pop, notas)
        
        f1, f2 = crossover_segmentado(pai1, pai2)
        
        nova_pop.append(mutacao(f1))
        if len(nova_pop) < TAM_POP:
            nova_pop.append(mutacao(f2))
    
    # por fim a nova população é atualizada
    pop = nova_pop[:TAM_POP]
    
    # A cada 50 gerações, imprime o número da geração e o melhor fitness. Acompanhando a evolução
    if g % 50 == 0:
        print(f"Geração {g:03} | Melhor Fitness: {melhor_atual:.2f}")

# --- 5. EXIBIÇÃO DE RESULTADOS ---

melhor = pop[np.argmin([calcular_fitness(i) for i in pop])]

print("\n" + "="*195)
print(f"{'DIA':<6} | {'DESJEJUM':<25} | {'ALMOÇO':<90} | {'LANCHE':<35} | {'JANTAR':<55}")
print("-" * 195)
for d in range(DIAS):
    i = d * ITENS_DIA
    dsj = ", ".join([n for _, n in melhor[i:i+3]])
    alm = ", ".join([n for _, n in melhor[i+3:i+10]])
    lan = ", ".join([n for _, n in melhor[i+10:i+13]])
    jan = ", ".join([n for _, n in melhor[i+13:i+20]])
    print(f"D{d+1:<5} | {dsj:<25} | {alm:<90} | {lan:<35} | {jan:<55}")
print("="*195)

# Resumo Nutricional Médio Diário
totais = np.zeros(4)
# For que percorre o cardápio do melhor indivíduo e acumula os nutrientes totais para cada refeição, dividindo pelo número de dias para obter a média diária.
for c, nm in melhor: totais += banco_alimentos[c][nm][:4]
totais_dia = totais / DIAS
labels = ["Energia (kcal)", "Proteína (g)", "Carbo (g)", "Lipídios (g)"]
print("\nRESUMO NUTRICIONAL MÉDIO DIÁRIO:")
for j in range(4):
    print(f"{labels[j]:<15}: {totais_dia[j]:>7.2f} / Meta: {METAS[j]:>7.2f}")



# Gráfico de Convergência
plt.figure(figsize=(10, 5))
plt.plot(historico_melhor_fitness, color='red', label='Melhor Fitness')
plt.title('Convergência do Algoritmo Genético')
plt.xlabel('Geração')
plt.ylabel('Valor de Fitness')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.show()