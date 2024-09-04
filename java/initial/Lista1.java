package initial;
import java.util.Scanner;

public class Lista1 {

    public Lista1(){

    }

    public void executarExercicio01() {
        Scanner scanner = new Scanner(System.in);
        int pares = 0;
        while(pares < 3){
            int num = scanner.nextInt();
            if(num % 2 == 0){
                pares++;
                System.out.println("Par");
            }
            else{
                System.out.println("Impar");
            }
        }
        System.out.println("3 números pares encontrados. Finalizando programa...");
    }

    public void executarExercicio02() {
        Scanner scanner = new Scanner(System.in);
        int impares = 0;
        int primeiro= 0, ultimo = 0;
        int qtd = 0;
        while(impares < 5){
            int num = scanner.nextInt();
            if(num % 2 != 0){
                impares++;
                if(impares == 1){
                    primeiro = num;
                }
                if(impares == 5){
                    ultimo = num;
                }
            }
            qtd++;
        }
        System.out.printf("Primeiro impar: %d\n", primeiro);
        System.out.printf("Último impar: %d\n", ultimo);
        System.out.printf("Quantidade de vezes: %d\n", qtd);
    }

    public void executarExercicio03() {

        Scanner scanner = new Scanner(System.in);

        float y = 0;
        System.out.println("Digite o m:");
        float m = scanner.nextFloat();
        System.out.println("Digite o x:");
        float x = scanner.nextFloat();
        System.out.println("Digite o n");
        float n = scanner.nextFloat();

        y = m*x + n;
        System.out.println("Y = " + y);
    }

    public void executarExercicio04() {
        
        Scanner scanner = new Scanner(System.in);
        int qtd = 0;
        int menor = 0, maior = 0;
        while( qtd < 10){

            int num = scanner.nextInt();

            if(qtd == 0){
                menor = num;
                maior = num;
            }
            else{
                if(menor > num){
                    menor = num;
                }
                if(maior < num){
                    maior = num;
                }
            }
            qtd++;
        }
        System.out.println("Menor Número: " + menor);
        System.out.println("Maior Número: " + maior);
    }

    public void executarExercicio05() {

        Boi[] bois = new Boi[5];

        bois[0] = new Boi(640);
        bois[1] = new Boi(540);
        bois[2] = new Boi(800);
        bois[3] = new Boi(860);
        bois[4] = new Boi(600);

        int aptos = 0;
        double receitaTotal = 0;

        for(Boi boi : bois){
            if(boi.isAptoParaAbate()){
                receitaTotal += boi.calcularReceita();
                aptos++;
            }
        }

        System.out.println("Bois pesados: " + bois.length);
        if (aptos >= 2 ){
            System.out.printf("Receita Total: R$ %.2f\n", receitaTotal);
            System.out.println("Processo foi bem sucedido");
        }
        else{
            System.out.println("Seus bois não são nada poggers");
        }
    }
}