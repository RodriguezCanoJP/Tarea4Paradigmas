package poleposition;

import java.net.ServerSocket;

import javax.print.DocFlavor.INPUT_STREAM;

public class cliente {
    private static Integer numClientes = 0;
    
    public static void addCliente(){ 
        cliente.numClientes++;
    }

    public static void rmvCliente(){
        cliente.numClientes--;
    }

    public static int getNumClientes(){
        return cliente.numClientes;
    }

    private ServerSocket socket;
    private Integer numCliente;
    private Boolean isActive;

    public cliente(ServerSocket socket, int numCliente){
        this.socket = socket;
        this.numCliente = numCliente;
        this.isActive = false;
    }

    public ServerSocket getSocket(){
        return this.socket;
    }

    public void setIsActive(Boolean isActive){
        this.isActive = isActive;
    }

    public Boolean getIsActive(){
        return this.isActive;
    }

    public Integer getNumCliente(){
        return this.numCliente;
    }
}
