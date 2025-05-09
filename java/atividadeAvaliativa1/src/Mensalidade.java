import java.time.LocalDate;

public class Mensalidade {
    
    private LocalDate dataGeracao;
    private double valor;
    private Socio socio;
    
    public Mensalidade(Socio socio) throws Exception {
        if (socio == null) {
            throw new Exception("Sócio não pode ser null.");
        }
        this.socio = socio;
        this.valor = socio.calcularMensalidade(); // 2 - Tratamentos de exceção propagadas e que não são tratadas no método que a lança;
        this.dataGeracao = LocalDate.now();
    }

    public LocalDate getDataGeracao() {
        return dataGeracao;
    }

    public double getValor() {
        return valor;
    }

    public Socio getSocio() {
        return socio;
    }

    public void pagarMensalidade() {
        try {
            if (valor < 0) {
                throw new IllegalArgumentException("[Erro]: Valor da mensalidade não pode ser negativo.");
            }
            System.out.println("Mensalidade paga no valor de: R$" + valor);
        } catch (IllegalArgumentException e) {
            System.out.println("[Erro]: Erro ao pagar a mensalidade: " + e.getMessage());
            e.printStackTrace();
        } catch (Exception e) {
            System.out.println("[Erro]: Erro ao pagar a mensalidade: " + e.getMessage());
            e.printStackTrace();
        }
    }

}
