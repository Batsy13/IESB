package src.br.edu.iesb.poo2024.Avaliativa2B2;

import java.util.Random;

public class UsuarioController {
    private UsuarioView view;
    private String codigoGerado;

    public UsuarioController(UsuarioView view) {
        this.view = view;
    }

    public boolean autenticarUsuario(String email, String senha) {

        // Simulação de autenticação (idealmente, validar em um BD)
        if ("usuario@example.com".equals(email) && "senha123".equals(senha)) {
            enviarEmailLogin(email);
            return true;
        } else {
            view.mostrarMensagem("Credenciais inválidas.");
            return false;
        }
    }

    public void enviarEmailLogin(String destinatario) {

        // Gerar um número aleatório de 5 dígitos
        Random rand = new Random();
        int codigo = rand.nextInt(90000) + 10000;  // Gera um número entre 10000 e 99999
        codigoGerado = String.valueOf(codigo);

        System.out.println("\nConfigurando o envio de e-mail...");
        System.out.println("Destinatário: " + destinatario);
        System.out.println("Assunto: Aqui está o seu código de envio");
        System.out.println("Mensagem: Seu código é: " + codigo);
        
        // Simulando o envio de e-mail
        System.out.println("E-mail de login enviado para " + destinatario + " com sucesso.");
        view.mostrarMensagem("E-mail de login enviado.");
    }

    // Método para verificar se o código inserido pelo usuário é o mesmo gerado
    public boolean verificarCodigo(String codigoInserido) {
        return codigoGerado != null && codigoGerado.equals(codigoInserido);
    }
}
