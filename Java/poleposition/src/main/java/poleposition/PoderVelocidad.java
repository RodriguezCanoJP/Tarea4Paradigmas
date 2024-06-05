package poleposition;

public class PoderVelocidad extends Poder {
    //constructuor
    public PoderVelocidad(String tipo,int posicion,int sumaVelocidad){
        
        this.tipo = tipo;
        this.posicion = posicion;
        this.sumaVelocidad = sumaVelocidad;
    }
    @Override
    public void onDestroy(){

        //se quita sl poder de velocidad
    }

}

