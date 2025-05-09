import pandas as pd
from sklearn.model_selection import train_test_split, cross_val_score, StratifiedKFold
from sklearn.naive_bayes import GaussianNB
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# Carregar os dados do arquivo Excel
data = pd.read_excel('baseskate.xlsx')

# Exibir as primeiras linhas dos dados
# print(data.head())

data.columns = data.columns.str.strip()


data['Dificuldade'] = data['Dificuldade'].map({'Baixa': 1, 'Média': 2, 'Alta': 3})


X = data[['Dificuldade', 'Nota Juiz 1', 'Nota Juiz 2', 'Nota Juiz 3', 'Tempo de Execução (s)']]
y = data['Classificação Final']

# # Verificar desbalanceamento de classes
# print("Distribuição das classes na 'Classificação Final':")
# print(y.value_counts())

# Normalização 
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Dividir em treino e teste
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)

# Modelo Naive Bayes
nb_model = GaussianNB()
nb_model.fit(X_train, y_train)
y_pred_nb = nb_model.predict(X_test)

# Modelo Árvore de Decisão
tree_model = DecisionTreeClassifier(random_state=42, max_depth=5)
tree_model.fit(X_train, y_train)
y_pred_tree = tree_model.predict(X_test)

# Função de Avaliação
def evaluate_model(y_test, y_pred, model_name):
    print(f"Resultados para {model_name}:")
    print(f"Acurácia: {accuracy_score(y_test, y_pred):.2f}")
    print(f"Precisão: {precision_score(y_test, y_pred, average='weighted', zero_division=1):.2f}")
    print(f"Recall: {recall_score(y_test, y_pred, average='weighted', zero_division=1):.2f}")
    print(f"F1-score: {f1_score(y_test, y_pred, average='weighted', zero_division=1):.2f}")
    print("\n")

# Avaliação dos modelos
evaluate_model(y_test, y_pred_nb, "Naive Bayes")
evaluate_model(y_test, y_pred_tree, "Árvore de Decisão")

cv = StratifiedKFold(n_splits=3)

# Validação cruzada para Naive Bayes
scores_nb = cross_val_score(nb_model, X_train, y_train, cv=cv, scoring='accuracy')
print("Acurácia Naive Bayes (Cross-Validation):", scores_nb.mean())

# Validação cruzada para Árvore de Decisão
scores_tree = cross_val_score(tree_model, X_train, y_train, cv=cv, scoring='accuracy')
print("Acurácia Árvore de Decisão (Cross-Validation):", scores_tree.mean())
