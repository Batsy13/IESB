import numpy as np
import random
import matplotlib.pyplot as plt

# --- 1. BANCO DE DADOS ---
banco_alimentos = {
    "Frutas_Sobremesa": {"Banana": [90, 1, 22, 0, 1.20, 4, 1], "Maçã": [52, 0, 14, 0, 1.50, 3, 1], "Laranja": [45, 1, 11, 0, 1.00, 4, 1]},
    "Leites": {"Leite": [120, 6, 9, 7, 2.00, 1, 3], "Iogurte": [140, 6, 18, 5, 2.80, 1, 2]},
    "Paes_Cereais": {"Pão": [150, 4, 30, 3, 0.80, 4, 1], "Biscoito": [130, 3, 25, 4, 1.10, 4, 1]},
    "Entrada": {"Salada Alface": [15, 1, 2, 0, 1.50, 2, 1], "Salada Tomate": [20, 1, 4, 0, 1.80, 3, 1]},
    "Acomp_Arroz": {"Arroz Branco": [130, 2, 28, 0, 0.80, 1, 1], "Arroz Integral": [120, 3, 25, 1, 1.20, 4, 1]},
    "Acomp_Feijao": {"Feijão Preto": [100, 6, 18, 1, 1.00, 4, 1], "Feijão Carioca": [95, 5, 17, 1, 0.90, 4, 1]},
    "Guarnicao": {"Purê Batata": [120, 2, 25, 4, 1.50, 1, 2], "Couve": [50, 2, 6, 3, 1.80, 2, 1]},
    "Prato_Principal": {"Frango": [200, 25, 0, 10, 3.50, 1, 1], "Omelete": [210, 14, 2, 16, 2.00, 4, 1], "Peixe": [180, 22, 0, 8, 4.50, 1, 1]},
    "Suco": {"Suco Laranja": [90, 1, 20, 0, 1.20, 4, 3], "Suco Uva": [110, 1, 25, 0, 1.50, 3, 3]}
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

# --- 3. FUNÇÕES DE EVOLUÇÃO ---

def criar_individuo():
    ind = []
    for _ in range(DIAS):
        for ref in ORDEM_DIA:
            for cat in ESTRUTURA[ref]:
                ind.append((cat, random.choice(list(banco_alimentos[cat].keys()))))
    return ind

def calcular_fitness(ind):
    totais_n = np.zeros(4)
    custo_total = 0
    penalidade = 0
    for d in range(DIAS):
        dia_genes = ind[d*ITENS_DIA : (d+1)*ITENS_DIA]
        ptr = 0
        for ref_nome in ORDEM_DIA:
            n = len(ESTRUTURA[ref_nome])
            bloco = dia_genes[ptr : ptr+n]
            c_ref = sum(banco_alimentos[c][nm][4] for c, nm in bloco)
            cores = [banco_alimentos[c][nm][5] for c, nm in bloco]
            texts = [banco_alimentos[c][nm][6] for c, nm in bloco]
            custo_total += c_ref
            for c, nm in bloco: totais_n += banco_alimentos[c][nm][:4]
            excesso_custo = c_ref - LIMITE_CUSTO_REF
            if c_ref > LIMITE_CUSTO_REF: penalidade += excesso_custo * PESO_EXCESSO_CUSTO
            for lista in [cores, texts]:
                for item in set(lista):
                    rep = lista.count(item)
                    if rep >= LIMITE_REP_MESMO_PRATO: 
                        penalidade += PESO_REPETICAO_VISUAL * (rep - (LIMITE_REP_MESMO_PRATO - 1))
            ptr += n
    unicos = len(set([nm for c, nm in ind]))
    if unicos < META_ITENS_UNICOS:
        deficit = META_ITENS_UNICOS - unicos
        penalidade += PESO_VARIEDADE * (deficit ** 2)
    erro_n = np.sum(np.abs(totais_n - (METAS * DIAS)))
    return (0.7 * erro_n) + (0.3 * custo_total) + penalidade

def crossover_segmentado(p1, p2):
    f1, f2 = [], []
    ptr = 0
    for _ in range(DIAS):
        for ref in ORDEM_DIA:
            n = len(ESTRUTURA[ref])
            cp = random.randint(1, n-1)
            f1.extend(p1[ptr : ptr+cp] + p2[ptr+cp : ptr+n])
            f2.extend(p2[ptr : ptr+cp] + p1[ptr+cp : ptr+n])
            ptr += n
    return f1, f2

def mutacao(ind, taxa=0.1):
    novo_ind = list(ind)
    for i in range(len(novo_ind)):
        if random.random() < taxa:
            cat = novo_ind[i][0]
            novo_ind[i] = (cat, random.choice(list(banco_alimentos[cat].keys())))
    return novo_ind

# --- 4. LOOP EVOLUTIVO ---

pop = [criar_individuo() for _ in range(200)]
historico_melhor_fitness = []

for g in range(500):
    notas = [calcular_fitness(i) for i in pop]
    melhor_atual = min(notas)
    historico_melhor_fitness.append(melhor_atual)
    
    nova_pop = []
    
    # Elitismo 
    indices_elite = np.argsort(notas)[:2]
    for idx in indices_elite:
        nova_pop.append(pop[idx])

    while len(nova_pop) < 200:
        vencedores = []
        for _ in range(2):
            comp = random.sample(range(200), 3)
            vencedores.append(pop[comp[np.argmin([notas[i] for i in comp])]])
        
        f1, f2 = crossover_segmentado(vencedores[0], vencedores[1])
        nova_pop.extend([mutacao(f1), mutacao(f2)])
    
    pop = nova_pop[:200]
    if g % 50 == 0:
        print(f"Geração {g:03} | Melhor Fitness: {melhor_atual:.2f}")

# --- 5. EXIBIÇÃO DE RESULTADOS ---

melhor = pop[np.argmin([calcular_fitness(i) for i in pop])]

# Gráfico de Convergência
plt.figure(figsize=(10, 5))
plt.plot(historico_melhor_fitness, color='red', label='Melhor Fitness')
plt.title('Convergência do Algoritmo Genético')
plt.xlabel('Geração')
plt.ylabel('Valor de Fitness')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.show()

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

totais = np.zeros(4)
for c, nm in melhor: totais += banco_alimentos[c][nm][:4]
totais_dia = totais / DIAS
labels = ["Energia (kcal)", "Proteína (g)", "Carbo (g)", "Lipídios (g)"]
print("\nRESUMO NUTRICIONAL MÉDIO DIÁRIO:")
for j in range(4):
    print(f"{labels[j]:<15}: {totais_dia[j]:>7.2f} / Meta: {METAS[j]:>7.2f}")