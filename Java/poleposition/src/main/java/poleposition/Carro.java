package poleposition;

public abstract class Carro {
    //atributos
    protected float distancia;
    protected float velocidad;
    protected float posicion;
    protected int posx;
    protected float curvatura;
    protected int vida;
    protected String color;

    //metodos
    public abstract void acelerar();
    public abstract void frenar();
    public abstract void disparar();
    public abstract void actualizar();


    public Carro(){
        this.vida = 3;
    }

    public void recibirDisparo(){
        //if de que si la bala esta en la posicion del carro 
        //entonces vida -1 
    }
    public void pasarHueco(){
        //if si esta en el rango del hueco una vida menos y velocidad=0
    }

    //getters y setters
    public int getVida(){
        return vida;
    }
    public void setVida(int vida){
        this.vida = vida;
    }
    public float  getVelocidad(){

        return velocidad;
    }
    public void setVelocidad(int velocidad){

        this.velocidad = velocidad;

    }
    public String getColor(){

        return color;
    }
    public void setColor(String color){

        this.color = color;
    }
    
}



