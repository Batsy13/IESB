package br.edu.iesb.poo2024.Avaliativa2B2;

import java.util.ArrayList;
import java.util.List;

public class ProdutoController {
    private List<Produto> produtos = new ArrayList<>();

    public void cadastrarProduto(Produto produto) {
        if (!produto.validarDados()) {
            System.out.println("Preencha todos os campos obrigatórios.");
            return;
        }

        for (Produto p : produtos) {
            if (p.getCodigoSKU().equals(produto.getCodigoSKU())) {
                System.out.println("SKU já cadastrado. Informe um SKU diferente.");
                return;
            }
        }

        produtos.add(produto);
        System.out.println("Produto cadastrado com sucesso!" + "\n" + "Nome: " + produto.getNome() + "\n");
    }

    public void editarProduto(String codigoSKU, Produto produtoAtualizado) {
        for (Produto produto : produtos) {
            if (produto.getCodigoSKU().equals(codigoSKU)) {
                if (!produtoAtualizado.validarDados()) {
                    System.out.println("Preencha todos os campos obrigatórios.");
                    return;
                }

                StringBuilder alteracoes = new StringBuilder();

                if (!produto.getNome().equals(produtoAtualizado.getNome())) {
                    alteracoes.append("Nome alterado de '")
                            .append(produto.getNome())
                            .append("' para '")
                            .append(produtoAtualizado.getNome())
                            .append("'. ");
                    produto.setNome(produtoAtualizado.getNome());
                }

                if (produto.getPreco() != produtoAtualizado.getPreco()) {
                    alteracoes.append("Preço alterado de ")
                            .append(produto.getPreco())
                            .append(" para ")
                            .append(produtoAtualizado.getPreco())
                            .append(". ");
                    produto.setPreco(produtoAtualizado.getPreco());
                }

                if (produto.getQuantidade() != produtoAtualizado.getQuantidade()) {
                    alteracoes.append("Quantidade alterada de ")
                            .append(produto.getQuantidade())
                            .append(" para ")
                            .append(produtoAtualizado.getQuantidade())
                            .append(". ");
                    produto.setQuantidade(produtoAtualizado.getQuantidade());
                }

                if (!produto.getCategoria().equals(produtoAtualizado.getCategoria())) {
                    alteracoes.append("Categoria alterada de '")
                            .append(produto.getCategoria())
                            .append("' para '")
                            .append(produtoAtualizado.getCategoria())
                            .append("'. ");
                    produto.setCategoria(produtoAtualizado.getCategoria());
                }

                if (alteracoes.length() > 0) {
                    produto.registrarAlteracao(alteracoes.toString());
                } else {
                    produto.registrarAlteracao("Nenhuma alteração detectada.");
                }

                System.out.println("Produto atualizado com sucesso!" + "\n" + "Nome: " + produto.getNome() + "\n");
                return;
            }
        }
        System.out.println("Produto não encontrado.");
    }

    public void excluirProduto(String codigoSKU, Usuario usuario) {
        if (!usuario.isAutorizado()) {
            System.out.println("Você não tem permissão para excluir este registro.\n");
        }

        for (Produto produto : produtos) {
            if (produto.getCodigoSKU().equals(codigoSKU)) {
                if (produto.getStatus().equals("Inativo")) {
                    produtos.remove(produto);
                    System.out.println("Produto excluído com sucesso!\n");
                    return;
                } else {
                    System.out.println("Produto não pode ser excluído, apenas inativado.\n");
                    return;
                }
            }
        }
        System.out.println("Produto não encontrado.");
        return;
    }

    public void consultarProduto(String codigoSKU) {
        if (codigoSKU == null || codigoSKU.isEmpty()) {
            if (produtos.isEmpty()) {
                System.out.println("Nenhum produto cadastrado.\n");
            } else {
                System.out.println("Lista de produtos cadastrados:\n");
                for (Produto produto : produtos) {
                    System.out.println(produto);
                }
            }
            return;
        }
    
        for (Produto produto : produtos) {
            if (produto.getCodigoSKU().equals(codigoSKU)) {
                System.out.println("Produto encontrado: ");
                System.out.println(produto);
                return;
            }
        }
        System.out.println("Erro: Produto com SKU '" + codigoSKU + "' não encontrado.\n");
    }
}
