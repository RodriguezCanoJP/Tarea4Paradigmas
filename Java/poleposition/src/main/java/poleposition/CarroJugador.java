package poleposition;

public class CarroJugador extends Carro {
    public CarroJugador (int velocidad,String color){
        this.velocidad = velocidad;
        this.color = color;
    }

    //metodos 
    @Override
    public void acelerar(){
        //logica
    }
    @Override
    public void frenar(){

        //logica para frenar
        System.out.println("Frenando...");

    }
    @Override
    public void disparar(){

        //logica  para disparar
        System.out.println("Disparando...");

    }
    @Override
    public void actualizar(){

        //logica para actualizar el estado
        System.out.println("Actualizado...");
        
    }

}
