package poleposition;

import java.io.File;
import java.io.IOException;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;

import org.json.*;

import java.nio.file.Path;
import java.nio.file.Paths;

public class server{
    private static server serverInstace;
    private static ArrayList<cliente> clientes;
    private static Pista pista;

    private server(){
        //se inicializa clientes
        server.clientes = new ArrayList<cliente>();

        //se lee valores de pista del json
        try {
            Path pistaPath = Paths.get("src/main/java/poleposition/resources/pista.json");
            String pistaString = pistaPath.toAbsolutePath().toString();
            File pistaFile = new File(pistaString);
            Scanner pistaScanner = new Scanner(pistaFile);
            String data = "";
            while (pistaScanner.hasNextLine()) {
                data += pistaScanner.nextLine();
            }
            pistaScanner.close();
            System.out.println(data);

            //se crea objeto json
            JSONObject pistaJson = new JSONObject(data);

            //se inicia pista y se guardan los valores del json
            server.pista = new Pista(pistaJson.getInt("secciones"));
            for (Integer i = 0; i < server.pista.getNumSecciones(); i++) {
                String key = Integer.toString(i);
                JSONArray valores = pistaJson.getJSONArray(key);
                System.out.println(valores.toString());
                pista.addLargo(((Float)valores.getFloat(0)), i);
                pista.addCurva(((Float)valores.getFloat(1)), i);
            }

        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

    /**
     * 
     * @return instancia del server
     */
    public static server getServer(){
        if(server.serverInstace == null){
            server.serverInstace = new server();
            return serverInstace;
        } else{
            return serverInstace;
        }
    }

    /**
     * 
     * @return boolean de si todos los clientes del server estan activos
     */
    public static Boolean allClientesActive(){
        Boolean allActive = true;
        for (cliente c : server.clientes) {
            if(!c.getIsActive()){
                allActive = false;
            }
        }
        return allActive;
    }


    public static void setClienteActive(Boolean isActive, Integer numCliente){
        server.clientes.get(numCliente).setIsActive(isActive);
    }

    public static Socket getClienteAcceptSocket(Integer numCliente){
        try { 
            Socket inpuSocket = server.clientes.get(numCliente).getSocket().accept();
            return inpuSocket;
        } catch (Exception e) {
            System.out.println("getClienteAcceptSocket");
            System.out.println(e.toString());
            return null;
        }
    }

    public void serverRun(){
        try {
            Boolean close = false;
            while(close == false){ 
                server.allClientesActive();
                if((clientes.isEmpty() || server.allClientesActive()) && (clientes.size() < 4)){

                    //cree un nuevo socket para el cliente
                    ServerSocket newSS = new ServerSocket(0);
                    StringBuilder port = new StringBuilder();
                    port.append(String.valueOf(newSS.getLocalPort()));
                    System.out.println();
                    System.out.println(
                        "New socket at "
                        + InetAddress.getLocalHost() + ":"
                        + port.toString()
                    );

                    //guarde el valor del port y el cliente en lista
                    cliente newJugador = new cliente(newSS, cliente.getNumClientes());
                    clientes.add(newJugador);


                    //se crea thread para socket 
                    InnerServer newSocketWR = new InnerServer(cliente.getNumClientes());
                    newSocketWR.start();

                    cliente.addCliente();
                    System.out.println("Server " + clientes.size());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}

