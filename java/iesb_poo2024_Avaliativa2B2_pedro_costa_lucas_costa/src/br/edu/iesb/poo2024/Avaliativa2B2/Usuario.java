package br.edu.iesb.poo2024.Avaliativa2B2;

public class Usuario {
    private String nome;
    private String email;
    private String permissao; // "Admin" ou "Usuario"

    public Usuario(String nome, String email, String permissao) {
        this.nome = nome;
        this.email = email;
        this.permissao = permissao;
    }

    public boolean isAutorizado() {
        return permissao.equals("Admin");
    }
}
