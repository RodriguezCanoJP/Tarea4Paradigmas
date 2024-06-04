package poleposition;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.ArrayList;

public class server {
    private static server serverInstace;
    private static ArrayList<cliente> clientes;

    private server(){
        this.clientes = new ArrayList<cliente>();
    }

    public static server getServer(){
        if(server.serverInstace == null){
            server.serverInstace = new server();
            return serverInstace;
        } else{
            return serverInstace;
        }
    }

    public static Boolean allClientesActive(){
        Boolean allActive = true;
        for (cliente cliente : clientes) {
            if(!cliente.isActive){
                allActive = false;
            }
        }
        return allActive;
    }

    public static void serverRun(){
        try {
            Boolean close = false;
            while(close == false){ 
                if(clientes.isEmpty() || server.allClientesActive()){
                    //añada un cliente mas a la clase cliente
                    cliente.addCliente();

                    //cree un nuevo socket para el cliente
                    ServerSocket newSS = new ServerSocket(0);
                    StringBuilder port = new StringBuilder();
                    port.append(String.valueOf(newSS.getLocalPort()));
                    System.out.println("New socket at" + port.toString());

                    //guarde el valor del port y el cliente en lista
                    cliente newJugador = new cliente(newSS, cliente.getNumClientes());
                    clientes.add(newJugador);
                }
                
                for (cliente cliente : clientes) {
                    StringBuilder texto = new StringBuilder();
                    Socket inputSocket = cliente.getSocket().accept();
                    DataInputStream input = new DataInputStream(inputSocket.getInputStream());
                    String inputString = input.readUTF();
                    texto.append(inputString);
                    input.close(); 
                }                

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
