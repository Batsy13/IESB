/*-------------------------------------------------------------------------------------------------------------------------
Disciplina: Programa��o Paralela.
Autor....: Prof. Rodrigo Gon�alves 
Objetivo..: Revis�o de conceitos b�sicos de C++.
Bimestre.: 1 Bimestre 2025
Solucao....: RevisaoCpp
--------------------------------------------------------------------------------------------------------------------------
Data Cria��o...................: 20/08/2025
Data Altera��o................. :20/08/2025 nome: xxxxxx
Altera��o Feita: Inclus�o do comando system("pause");
--------------------------------------------------------------------------------------------------------------------------
Vers�o 1.0
*/
#define PausarTexto "Pause" // define uma constante chamada PausarTexto com o valor "Pause"
#define LimparTela "cls" // define uma constante chamada LimparTela com o valor "cls"
#define Retorne return // define uma constante chamada Retorne com o valor return.


#include <iostream>
// a diretiva de pr�-processamento #include � usada para incluir o conte�do 
// de um arquivo de cabe�alho em um programa C++
// no caso vamos incluir o arquivo iostream que cont�m
// as defini��es para os objetos de entrada e sa�da padr�o como std::cin, std::cout, std::cerr

// CRTL + K + C = comenta a linha selecionada
// CRTL + K + U = descomenta a linha selecionada
// CRTL + F5 = executa o programa sem depura��o
// F5 = executa o programa com depura��o
// CRTL + SHIFT + B = compila o programa
// ALT + SHIFT + ENTER = executa o programa em tela cheia
// CRTL + D = duplica a linha selecionada.
// CRTL + C = no final da linha, copia a linha selecionada. Sem  necessidade de selecionar a linha para a c�pia.
using namespace std; //espa�o de nomes padr�o

// a diretiva using namespace std; permite o uso de elementos do namespace std
//:: � o operador de resolu��o de escopo que � usado para acessar membros de um namespace ou classe


// chaves: indicam o in�cio e o fim de um bloco de c�digo.
int main() {
	// a fun��o main � o ponto de entrada de um programa C++ - fun��o principal.
	// a fun��o main retorna um valor inteiro que indica o status de t�rmino do programa
	// o valor 0 geralmente indica que o programa terminou com sucesso 
	// a fun��o std::cout � usada para imprimir texto na sa�da padr�o (geralmente o console).

	// << � o operador de inser��o que � usado para enviar dados para a sa�da padr�o.
		std::cout << "Hello, World!" << std::endl; // endl indica para inserir um caractere de quebra de linha.

	//system("cls"); // chama o shell do windows e coloca o comando (cls) para limpar a tela do console.
	system("dir"); // chama o shell do windows e coloca o comando (dir) para listar os arquivos do diret�rio atual.
	// system("color 0A"); // chama o shell do windows e coloca o comando (color 0A) para mudar a cor do texto do console.
	system("cmatrix"); // chama o shell do windows e coloca o comando (pause) para pausar a execu��o do programa at� que o usu�rio pressione uma tecla.
	
	//system(LimparTela); // chama o shell do windows e coloca o comando (cls) para limpar a tela do console.
	return 0; // retorna para o sistema operacional o valor 0 indicando que o programa terminou com sucesso.
} // indica o fim do bloco de c�digo da fun��o main


