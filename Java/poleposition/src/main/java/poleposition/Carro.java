package poleposition;

public abstract class Carro {
    //atributos
    protected Float distancia;
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
        this.velocidad = 0;
        this.color = "rojo";
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
        if (vida >= 0){
            this.vida = vida;
        }
    }
    public float  getVelocidad(){

        return velocidad;
    }
    public void setVelocidad(int velocidad){

        if(velocidad >= 0){
            this.velocidad = velocidad;
        }
        
    }
    public String getColor(){

        return color;
    }
    public void setColor(String color){

        this.color = color;
    }
    
}



