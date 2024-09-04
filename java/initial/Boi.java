package initial;

public class Boi {
    private static final double PRECO_ARROBA = 232.60;
    private static final int PESO_IDEAL = 600;
    private double peso;

    public Boi(double peso){
        this.peso = peso;
    }

    public boolean isAptoParaAbate(){
        return (this.peso >= PESO_IDEAL);
    }

    public double calcularReceita() {
        if(isAptoParaAbate()){
            double quantidadeArrobas = this.peso / 15;
            return quantidadeArrobas * PRECO_ARROBA;
        }
        else{
            return 0;
        }
    }
    
    public double getPeso() {
        return peso;
    }

    public void setPeso(double peso){
        this.peso = peso;
    }
}
