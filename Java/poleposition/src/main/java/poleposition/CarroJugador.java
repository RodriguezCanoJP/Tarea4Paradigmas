package poleposition;

public class CarroJugador extends Carro {
    public CarroJugador (int velocidad,String color){
        this.velocidad = velocidad;
        this.color = color;
    }

    //metodos 
    @Override
    public void acelerar(){
        velocidad += 10;
        System.out.println("acelerando" + velocidad);
    }
    @Override
    public void frenar(){

        velocidad -= 10;
        System.out.println("Frenando..." );
        if (velocidad < 0) velocidad = 0;
            System.out.println("parado" + velocidad);
        

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
