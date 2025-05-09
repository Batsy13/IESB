package src.br.edu.iesb.poo2024.Avaliativa2B2;

import java.util.Scanner;

public class UsuarioView {
    private Scanner scanner;

    public UsuarioView() {
        this.scanner = new Scanner(System.in);
    }

    public String getInput(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    public void mostrarMensagem(String mensagem) {
        System.out.println(mensagem);
    }
}
