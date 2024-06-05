package poleposition;

public class PoderFactory extends PolePositionFactory{
    @Override
    public Poder crearPoder(){
        //logica de creacion de los poderes
        boolean logica;
        Poder poder;
        logica=true;

        if(logica){
            poder = new PoderVida(null, 0, 0);
        } else {
            poder = new PoderVelocidad(null, 0, 0);
        }
        return poder;
    }
}

