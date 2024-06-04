package poleposition;

import java.net.ServerSocket;

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

    protected ServerSocket socket;
    protected Integer numCliente;
    protected Boolean isActive;

    public cliente(ServerSocket socket, int numCliente){
        this.socket = socket;
        this.numCliente = numCliente;
        this.isActive = false;
    }

    public ServerSocket getSocket(){
        return this.socket;
    }
}
