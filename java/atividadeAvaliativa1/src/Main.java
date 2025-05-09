public class Main {
    public static void main(String[] args) {
        System.out.println("\n/* ******************************************************* */\n");
        System.out.println("Pedro Costa Ferreira - 2312130138");
        System.out.println("\n/* ******************************************************* */\n");
        
        try {
            
            // Erro proposital: criação de um Sócio com mensalidade negativa
            // Isso vai gerar uma exceção no método `calcularMensalidade`
            Socio socio = new Socio("123.456.789-00", "João Silva", -100.0);
            
            // Erro proposital: adição de um dependente nulo
            // Isso vai gerar uma exceção no método `adicionarDependente`
            socio.adicionarDependente(null);
            System.out.println("\n/* ******************************************************* */\n");
            
            // Erro proposital: criação de um dependente com sócio responsável null
            // Isso vai gerar uma exceção no construtor da classe `Dependente`
            Dependente filho1 = new Dependente("234.567.890-01", "Carlos Silva", null); // 3 - Um exemplo de exceção não tratada em Java.
            socio.adicionarDependente(filho1);
            
            // Esse trecho de código nunca será executado devido à exceção acima
            Dependente filho2 = new Dependente("345.678.901-02", "Maria Silva", socio);
            socio.adicionarDependente(filho2);
            
            // Criação da mensalidade, que também vai propagar a exceção devido à mensalidade base negativa
            Mensalidade mensalidade = new Mensalidade(socio);
            
            System.out.println("Valor da mensalidade: R$ " + mensalidade.getValor());
            
            // Tentativa de pagamento de uma mensalidade inválida
            // Se a mensalidade tivesse sido criada com sucesso, o valor seria negativo e geraria uma exceção
            mensalidade.pagarMensalidade();

        } catch (Exception e) {

            // 2 - Tratamentos de exceção propagadas e que não são tratadas no método que a lança:
            System.out.println("Ocorreu um erro: " + e.getMessage());
            e.printStackTrace();
            System.out.println("\n/* ******************************************************* */\n");    

        }
    }
}
