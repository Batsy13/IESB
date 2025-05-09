package br.edu.iesb.poo2024.devlab5.exceptions.verificado.negociais;

public class ContaCorrente {

    private String CPF;
    private String nome;
    private double saldo;

    // construtor padrão (implícito)
    // public ContaCorrente() {}

    // Exemplo 4
    public ContaCorrente(String nome) throws CadastroInvalidoException {

        if (nome == null || nome.equals("")) {
            throw new CadastroInvalidoException();
        }
        this.nome = nome;
    }

    // Exemplo 3
    public ContaCorrente(String CPF, String nome) throws Exception {
        if (CPF == null || nome == null || (!CPF.equals("") || !nome.equals(""))) {
            throw new Exception("[Erro]: É necessário um CPF e nome válidos para a"
                    + "criação da conta corrente");
        }
        this.CPF = CPF;
        this.nome = nome;
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }
}
