package poleposition;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.*;
import org.json.*;

public class InnerServer extends Thread{

    private Integer clienteServerNum;

    public InnerServer(Integer clienteServerNum){
        this.clienteServerNum = clienteServerNum;
    }

    @Override
    public void run(){
        try {
            Boolean isClosed = false;
            while (isClosed == false) {
                System.out.println("Start");
                //se lee datos de entrada
                StringBuilder texto = new StringBuilder();
                Socket inputSocket = server.getClienteAcceptSocket(clienteServerNum);
                System.out.println("Finish");
                DataInputStream input = new DataInputStream(inputSocket.getInputStream());
                String inputString = input.readUTF();
                texto.append(inputString);
                System.out.println(inputString);
                input.close(); 
                //se convierten a json 
                JSONObject inputJson = new JSONObject(inputString);
                if(inputJson.has("isActive") && inputJson.getBoolean("isActive") == true){
                    System.out.println("Activando cliente " + clienteServerNum);
                    server.setClienteActive(true, clienteServerNum);
                }
                Thread.sleep(100);
            } 
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }                
}