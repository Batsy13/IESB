/*---------------------------------------------------------------------------------------------------------------------
Objetivo..: Revis�o de entrada/sa�da com cin e getline.
Arquivo...: 003.cpp
--------------------------------------------------------------------------------------------------------------------------*/

// ------------------- Diretivas de Pr�-processador -------------------

// #include: � uma "diretiva de pr�-processador". Ela diz ao compilador para incluir o conte�do
// de outro arquivo neste ponto. � como copiar e colar o c�digo de uma biblioteca.

#include <iostream> // Inclui a biblioteca de Input/Output Stream. Essencial para usar cin (entrada), cout (sa�da) e endl.
#include <string>   // Inclui a biblioteca para manipula��o de strings, permitindo o uso do tipo string.
#include <limits>   // Embora n�o esteja expl�cito, <iostream> geralmente inclui <limits>, que � necess�rio para `numeric_limits`. � uma boa pr�tica inclu�-lo se for usar `numeric_limits` diretamente.

// ------------------- Declara��o de Namespace -------------------

// using namespace std;: Esta linha diz ao compilador que usaremos elementos do "namespace" (espa�o de nomes) std.
// O namespace std cont�m toda a biblioteca padr�o do C++. Sem essa linha, ter�amos que escrever `std::cout`, `std::cin`, `std::string`, etc.
// OBS) Em projetos grandes, � considerado uma m� pr�tica usar `using namespace std;` no escopo global
// para evitar conflitos de nomes. Para exemplos pequenos como este, � totalmente aceit�vel.
using namespace std;

// ------------------- Fun��o Principal -------------------

// int main(): � o ponto de entrada de todo programa C++. O c�digo dentro desta fun��o � o primeiro a ser executado.
// O `int` indica que a fun��o retornar� um valor inteiro para o sistema operacional (geralmente 0 para sucesso).
int main() {
	// ------------------- Declara��o de Vari�veis -------------------

	// string: � um tipo de dado (na verdade, uma classe) da biblioteca padr�o para armazenar sequ�ncias de caracteres (texto).
	string nome;
	// int: � um tipo de dado primitivo para armazenar n�meros inteiros.
	int idade;

	// ------------------- Entrada de Dados (Problem�tica Comum) -------------------

	// cout: (Console Output) � o objeto de fluxo de sa�da padr�o, geralmente a tela do console.
	// <<: � o "operador de inser��o". Ele "insere" os dados da direita no fluxo de sa�da � esquerda.
	cout << "Digite seu primeiro nome: ";

	// cin: (Console Input) � o objeto de fluxo deentrada padr�o, geralmente o teclado.
	// >>: � o "operador de extra��o". Ele "extrai" dados do fluxo de entrada e os armazena na vari�vel � direita.
	// IMPORTANTE: O operador `>>` para de ler no primeiro caractere de espa�o em branco (espa�o, tab, quebra de linha).
	cin >> nome;

	cout << "Digite sua idade: ";
	cin >> idade;

	// ------------------- Limpeza do Buffer de Entrada -------------------

	// O PONTO CR�TICO: Quando o usu�rio digita a idade (ex: 25) e pressiona Enter, o buffer de entrada recebe "25\n".
	// `cin >> idade;` l� o "25", mas deixa o caractere de nova linha (`\n`) no buffer.
	// A pr�xima chamada `getline` leria esse `\n` e pensaria que o usu�rio digitou uma linha vazia.
	// Para corrigir isso, limpamos o buffer.

	// cin.ignore(): � um m�todo do objeto `cin` que descarta (ignora) caracteres do buffer de entrada.
	// Ele recebe dois argumentos:
	// 1. A quantidade m�xima de caracteres a ignorar.
	// 2. O caractere delimitador onde a fun��o deve parar de ignorar.

	// numeric_limits<streamsize>::max(): � uma forma padr�o e robusta de dizer "um n�mero muito grande".
	// - `numeric_limits`: � um template de classe que fornece informa��es sobre as propriedades de tipos num�ricos.
	// - `<streamsize>`: � o tipo usado para representar o tamanho de um fluxo (stream).
	// - `::max()`: Retorna o valor m�ximo que `streamsize` pode conter.
	// Juntos, eles dizem para `ignore()` descartar um n�mero virtualmente infinito de caracteres.

	// '\n': � o caractere delimitador. `ignore()` vai parar assim que encontrar e descartar este caractere.
	// Resumo da linha: "Ignore quantos caracteres forem necess�rios at� encontrar e remover um `\n` do buffer de entrada."
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// ------------------- Leitura de Linha Completa -------------------

	string nomeCompleto;
	cout << "Digite seu nome completo: ";
	// getline(): � uma fun��o (n�o um operador) projetada para ler uma linha inteira de um fluxo de entrada.
	// Ela l� do primeiro argumento (`cin`) e armazena na vari�vel do segundo argumento (`nomeCompleto`),
	// parando quando encontra o caractere de nova linha (`\n`), que tamb�m � consumido do buffer.
	getline(cin, nomeCompleto);

	// ------------------- Sa�da Formatada -------------------

	cout << "Oi, " << nomeCompleto << ". Voc� tem " << idade << " anos." << endl;

	// ------------------- `endl` vs `\n` -------------------
	// endl: (End Line) � um "manipulador de fluxo". Ele faz duas coisas:
	// 1. Insere um caractere de nova linha (`\n`).
	// 2. For�a o "flush" (esvaziamento) do buffer de sa�da. Isso garante que o texto seja imediatamente escrito na tela.
	cout << "Linha com endl" << endl;

	// '\n': � simplesmente o caractere de nova linha.
	// Ele n�o for�a o flush do buffer. O sistema operacional pode decidir agrupar v�rias sa�das e escrev�-las
	// de uma vez s� para otimizar o desempenho.
	// Para programas interativos de console, a diferen�a � impercept�vel. Em aplica��es que escrevem
	// milh�es de linhas em um arquivo (logging, por exemplo), usar `'\n'` � significativamente mais r�pido.
	cout << "Linha com \\n" << '\n';

	// ------------------- Pausa para Visualiza��o (Espec�fico do Windows) -------------------

	// system(): � uma fun��o da biblioteca C padr�o (<cstdlib>) que executa um comando do sistema operacional.
	// "pause": � um comando do Prompt de Comando do Windows que exibe "Pressione qualquer tecla para continuar..." e aguarda uma tecla.
	// OBS) Isso n�o � port�vel (s� funciona no Windows) e � geralmente considerado uma m� pr�tica em software profissional.
	// Para fins de aprendizado no Visual Studio, � uma forma r�pida e f�cil de impedir que a janela do console feche imediatamente.
	system("pause");

	// ------------------- Retorno da Fun��o `main` -------------------

	// return: � a palavra-chave que finaliza a execu��o de uma fun��o e, opcionalmente, retorna um valor.
	// 0: Por conven��o, retornar `0` da fun��o `main` indica que o programa foi executado com sucesso.
	// Valores diferentes de zero geralmente indicam que ocorreu algum tipo de erro.

	

	return 0;
}