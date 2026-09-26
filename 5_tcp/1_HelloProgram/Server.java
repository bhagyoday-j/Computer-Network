import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Server {

    public static void main(String[] args) {

        try {
            ServerSocket serverSocket = new ServerSocket(5000);
            System.out.println("Server started...");
            System.out.println("Waiting for client...");

            Socket socket = serverSocket.accept();
            System.out.println("Client Connected!");

            BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            PrintWriter out = new PrintWriter(
                    socket.getOutputStream(), true);

            Scanner sc = new Scanner(System.in);

            String msg;

            while (true) {

                // Receive from client
                msg = in.readLine();
                System.out.println("Client: " + msg);

                if (msg.equalsIgnoreCase("bye")) {
                    System.out.println("Client ended the chat.");
                    break;
                }

                // Send to client
                System.out.print("Server: ");
                String reply = sc.nextLine();

                out.println(reply);

                if (reply.equalsIgnoreCase("bye")) {
                    System.out.println("Chat ended.");
                    break;
                }
            }

            socket.close();
            serverSocket.close();
            sc.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}