package br.edu.iesb.poo2024.devlab5.exceptions.verificado.negociais;

public class CadastroInvalidoException extends java.lang.Exception{

    private static String mensagemErro = "[Erro]: É necessário um CPF e nome válidos para a criação da conta corrente";
    
    public CadastroInvalidoException() {
        super(mensagemErro);
    }
}
