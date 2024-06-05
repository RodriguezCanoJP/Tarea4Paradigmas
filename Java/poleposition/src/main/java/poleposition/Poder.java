package poleposition;

public abstract  class Poder {
    //atributos
    protected String tipo;
    protected int posicion;
    protected int sumaVida;
    protected int sumaVelocidad;
    protected Carro[] suscriptores;

    //metodos abstractos
    public abstract void onDestroy();

    public void agregarSuscriptor(Carro carro){
        //logica para agregar el suscriptor
    }
    
    public void quitarSuscriptor(Carro carro){
        //logica para quitar al suscriptor
    }

    public void notificar(){
        //logica para notificar a los suscriptores
    }

    //getters y setters
    public String getTipo(){

        return tipo;
    }

    public void setTipo(String tipo){
        this.tipo = tipo;
    }

    public int getPosition(){

        return posicion;
    }

    public void setPosition(int posicion){
        this.posicion = posicion;
    }

    public int getSumaVida(){

        return sumaVida;
    }

    public void setSumaVida(int sumaVida){
        this.sumaVida = sumaVida;
    }

    public int getSumaVelocidad(){

        return sumaVelocidad;
    }

    public void setSumaVelocidad(int sumaVelocidad){
        this.sumaVelocidad = sumaVelocidad;
    }

    public Carro[] getSuscriptores(){

        return suscriptores;
    }

    public void setSuscriptores(Carro[] suscriptores){
        this.suscriptores = suscriptores;
    }

}
