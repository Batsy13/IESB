package br.edu.iesb.poo2024.Avaliativa2B2;

public class ProdutoView {
    public static void main(String[] args) {

        System.out.println("Pedro Costa - 2312130138");
        System.out.println("Lucas Costa - 2312082035");
        ProdutoController controller = new ProdutoController();

        // Criando usuário Admin
        Usuario admin = new Usuario("Admin", "emailteste@gmail.com", "Admin");

        // Testando função de cadastrar produto
        Produto produto = new Produto("SKU001", "Camiseta", "Roupas", 29.99, 100, "Ativo");
        controller.cadastrarProduto(produto);

        // Testando função de atualizar produto
        Produto atualizado = new Produto("SKU002", "Camiseta Premium", "Roupas", 39.99, 80, "Ativo");
        controller.cadastrarProduto(atualizado);
        Produto atualizado2 = new Produto("SKU002", "Camiseta Premium", "Roupas", 20.99, 80, "Ativo");
        controller.editarProduto("SKU002", atualizado2);

        // Testando função de excluir
        Produto excluido = new Produto("SKU003", "Camiseta Poggers", "Roupas", 9.99, 80, "Inativo");
        controller.cadastrarProduto(excluido);
        controller.excluirProduto("SKU003", admin);

        // Testando função de consultar - Todos os produtos
        System.out.println("Consulta de todos os produtos:");
        controller.consultarProduto("");

        // Testando função de consultar - Produto existente
        System.out.println("\nConsulta de produto com SKU 'SKU002':");
        controller.consultarProduto("SKU002");

        // Testando função de consultar - Produto inexistente
        System.out.println("\nConsulta de produto com SKU 'SKU999':");
        controller.consultarProduto("SKU999");
    }
}