import java.util.ArrayList;
import java.util.List;

public class Socio extends Pessoa {

    private List<Dependente> dependentes;
    private double mensalidadeBase;

    public Socio(String cpf, String nome, double mensalidadeBase) {
        super(cpf, nome);

        if (mensalidadeBase < 0) {
            throw new IllegalArgumentException("Mensalidade base não pode ser negativa."); // 4 - Um tratamento de exceção no construtor da sua classe negocial de mais importância do seu estudo de caso
        }

        if (nome == null || nome.trim().isEmpty()) {
            throw new IllegalArgumentException("Nome do sócio não pode ser vazio.");
        }

        this.mensalidadeBase = mensalidadeBase;
        this.dependentes = new ArrayList<>();
    }

    public void adicionarDependente(Dependente dependente) {
        dependentes.add(dependente);
    }

    public void removerDependente(Dependente dependente) {
        dependentes.remove(dependente);
    }

    public double calcularMensalidade() {
        return mensalidadeBase + (dependentes.size() * 20);
    }

    public List<Dependente> getDependentes() {
        return dependentes;
    }

    public double getMensalidadeBase() {
        return mensalidadeBase;
    }

    public void setMensalidadeBase(double mensalidadeBase) {
        this.mensalidadeBase = mensalidadeBase;
    }
}
