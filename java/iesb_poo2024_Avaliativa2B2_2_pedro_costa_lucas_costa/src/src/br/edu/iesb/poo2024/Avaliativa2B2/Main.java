package src.br.edu.iesb.poo2024.Avaliativa2B2;

public class Main {
    public static void main(String[] args) {
        UsuarioView view = new UsuarioView();
        UsuarioController controller = new UsuarioController(view);

        System.out.println("Pedro Costa - 2312130138");
        System.out.println("Lucas Costa - 2312082035");
        
        String email = "usuario@example.com";
        String senha = "senha123";

        // Autenticação do usuário
        if (controller.autenticarUsuario(email, senha)) {
            String inputCodigo = view.getInput("Digite o código enviado para o seu e-mail: ");
            
            if (controller.verificarCodigo(inputCodigo)) {
                view.mostrarMensagem("Login realizado com sucesso!");
            } else {
                view.mostrarMensagem("Código inválido. Tente novamente.");
            }
        }
    }
}
