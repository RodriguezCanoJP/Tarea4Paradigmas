package poleposition;

import java.io.*;
import java.net.*;
import org.json.*;

public class InnerServer extends Thread {

    private Integer clienteServerNum;

    public InnerServer(Integer clienteServerNum){
        this.clienteServerNum = clienteServerNum;
    }

    @Override
    public void run(){
        Boolean isClosed = true;
        Socket inputSocket = server.getClienteAcceptSocket(clienteServerNum);
        try {
            InputStream in = inputSocket.getInputStream();
            while (isClosed) {
                try {

                    ByteArrayOutputStream buffer = new ByteArrayOutputStream();
                    byte[] data = new byte[1024];
                    int bytesRead;


                    while ((bytesRead = in.read(data, 0, data.length)) != -1) {
                        buffer.write(data, 0, bytesRead);
                        if (in.available() == 0) {
                            break; // Exit loop if no more data is available
                        }
                    }
                    // Convert buffer to string and print the received message
                    String receivedMessage = buffer.toString("UTF-8");
                    JSONObject inputJson = new JSONObject(receivedMessage);
                    if (inputJson.has("isActive") && inputJson.getBoolean("isActive") == true) {
                        System.out.println("Activando cliente " + clienteServerNum);
                        server.setClienteActive(true, clienteServerNum);
                    }

                    buffer.close();


                } catch (IOException e) {
                    System.err.println("IOException: " + e.getMessage());
                }
            }
            in.close();
            inputSocket.close();
        }catch (IOException e){
            System.err.println("IOException: " + e.getMessage());
        }
        //Thread.yield();


    }                
}