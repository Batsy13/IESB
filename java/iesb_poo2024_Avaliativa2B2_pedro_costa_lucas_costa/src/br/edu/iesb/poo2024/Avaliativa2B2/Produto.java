package br.edu.iesb.poo2024.Avaliativa2B2;

import java.util.Date;

public class Produto {
    private String codigoSKU;
    private String nome;
    private String categoria;
    private double preco;
    private int quantidade;
    private String status; // "Ativo" ou "Inativo"
    private Date dataCadastro;
    private Date dataAlteracao;

    public Produto(String codigoSKU, String nome, String categoria, double preco, int quantidade, String status) {
        this.codigoSKU = codigoSKU;
        this.nome = nome;
        this.categoria = categoria;
        this.preco = preco;
        this.quantidade = quantidade;
        this.status = status;
        this.dataCadastro = new Date();
        this.dataAlteracao = new Date();
    }

    public String getCodigoSKU() {
        return codigoSKU;
    }



    public void setCodigoSKU(String codigoSKU) {
        this.codigoSKU = codigoSKU;
    }



    public String getNome() {
        return nome;
    }



    public void setNome(String nome) {
        this.nome = nome;
    }



    public String getCategoria() {
        return categoria;
    }



    public void setCategoria(String categoria) {
        this.categoria = categoria;
    }



    public double getPreco() {
        return preco;
    }



    public void setPreco(double preco) {
        this.preco = preco;
    }



    public int getQuantidade() {
        return quantidade;
    }



    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }



    public String getStatus() {
        return status;
    }



    public void setStatus(String status) {
        this.status = status;
    }



    public Date getDataCadastro() {
        return dataCadastro;
    }



    public void setDataCadastro(Date dataCadastro) {
        this.dataCadastro = dataCadastro;
    }



    public Date getDataAlteracao() {
        return dataAlteracao;
    }



    public void setDataAlteracao(Date dataAlteracao) {
        this.dataAlteracao = dataAlteracao;
    }

    public boolean validarDados() {
        return codigoSKU != null && !codigoSKU.isEmpty() &&
               nome != null && !nome.isEmpty() &&
               preco > 0 &&
               quantidade >= 0;
    }

    public void registrarAlteracao(String campo) {
        this.dataAlteracao = new Date();
        System.out.println("Alteração registrada no campo: " + campo + "\n");
    }

    @Override
    public String toString() {
        return "Produto [SKU=" + codigoSKU + ", Nome=" + nome + ", Categoria=" + categoria + 
               ", Preço=" + preco + ", Quantidade=" + quantidade + ", Status=" + status + "]";
    }
}

