public class Dependente {

    private Socio socioResponsavel;

    public Dependente(String cpf, String nome, Socio socioResponsavel) throws Exception{
        if(socioResponsavel == null){
            throw new Exception("[Erro]: O Sócio Responsável não pode ser nulo"); // 2 - tratamentos de exceção propagadas e que não são tratadas no método que a lança;
        }
        this.socioResponsavel = socioResponsavel;
    }

    public Socio getSocioResponsavel() {
        return socioResponsavel;
    }

    public void setSocioResponsavel(Socio socioResponsavel) {
        this.socioResponsavel = socioResponsavel;
    }

}
