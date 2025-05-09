package br.edu.iesb.poo2024.devlab5.exceptions.verificado;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ManipulaArquivoTexto {

    public void procArquivoTextoSemTratarExcecao(String nomeArquivo)
            throws IOException {

        FileReader fileReader = new FileReader(nomeArquivo);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;

        while ((line = bufferedReader.readLine()) != null) {
            System.out.println(">> Aluno: " + line);
        }
    }

    public void processarArquivoTexto(String nomeArquivo) {

        try {

            FileReader fileReader = new FileReader(nomeArquivo);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;

            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(">> Aluno: " + line);
            }

        } catch (IOException ioException) {

            ioException.printStackTrace();

        } finally {
            System.out.println("[Log] esse código sempre será executado! " + getClass());
        }

    }

}
