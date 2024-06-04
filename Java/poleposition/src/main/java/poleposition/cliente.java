package poleposition;

import java.net.ServerSocket;

public class cliente {
    private static Integer num_clientes = 0;
    
    public static void addCliente(){ 
        cliente.num_clientes++;
    }

    public static void rmvCliente(){
        cliente.num_clientes--;
    }

    public static int getNumClientes(){
        return cliente.num_clientes;
    }

    protected ServerSocket socket;
    protected Integer num_cliente;
    protected Boolean isActive;

    public cliente(ServerSocket socket, int num_cliente){
        this.socket = socket;
        this.num_cliente = num_cliente;
        this.isActive = false;
    }

    public ServerSocket getSocket(){
        return this.socket;
    }
}
