package br.edu.iesb.poo2024.devlab5;

import java.io.IOException;

import br.edu.iesb.poo2024.devlab5.exceptions.naoverificada.ExcecaoNaoVerificada;
import br.edu.iesb.poo2024.devlab5.exceptions.verificado.ManipulaArquivoTexto;
import br.edu.iesb.poo2024.devlab5.exceptions.verificado.negociais.CadastroInvalidoException;
import br.edu.iesb.poo2024.devlab5.exceptions.verificado.negociais.ContaCorrente;

public class DevLab5Main {
    
    public static void main(String[] args) {

        // Exemplo 1 : exceção não verificada ou não tratada
        System.out.println("Exemplo 1 : excecao nao verificada ou não tratada");
        ExcecaoNaoVerificada excecaoNaoVerificada = new ExcecaoNaoVerificada();
        excecaoNaoVerificada.doExemplo1();
        /* ************************************************************************** */
        
        // Exemplo 2 : exceção verificada
        System.out.println("Exemplo 2 : excecao verificada");
        ManipulaArquivoTexto manipulaArquivoTexto = new ManipulaArquivoTexto();
        manipulaArquivoTexto.processarArquivoTexto("alunos.txt");

        // Exemplo 2.1 : exceção verificada e nao tratada
        System.out.println("Exemplo 2.1 : excecao verificada");
        try {
            manipulaArquivoTexto.procArquivoTextoSemTratarExcecao("alunos.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
        /* ************************************************************************** */
        
        // Exemplo 3 : exceção negocial a nivel de construtor
        System.out.println("Exemplo 3 : excecao negocial a nivel de construtor");
        try {
            ContaCorrente contaCorrente = new ContaCorrente(null,null);
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        // Exemplo 4 : exceção negocial a nivel de construtor
        System.out.println("Exemplo 4 : excecao negocial a nivel de construtor");
        try {
            ContaCorrente contaCorrente = new ContaCorrente("");
        } catch (CadastroInvalidoException e) {
            e.printStackTrace();
        }
    }

}
