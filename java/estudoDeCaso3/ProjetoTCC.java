package estudoDeCaso3;

import java.util.Date;

public class ProjetoTCC {

    private int id;
    private String tema;
    private String autor;
    private String nome;
    private Date dtInicio;
    private Date dtFim;
    
    public void ProjetoTcc() {
        
    }


    public void setTema(String tema){
        this.tema = tema;
    }

    public String getTema(){
        return this.tema;
    }

}