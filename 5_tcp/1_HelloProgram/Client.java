import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {

    public static void main(String[] args) {

        try {
            Socket socket = new Socket("localhost", 5000);

            BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            PrintWriter out = new PrintWriter(
                    socket.getOutputStream(), true);

            Scanner sc = new Scanner(System.in);

            String msg;

            while (true) {

                // Send message
                System.out.print("Client: ");
                msg = sc.nextLine();

                out.println(msg);

                if (msg.equalsIgnoreCase("bye")) {
                    System.out.println("Chat ended.");
                    break;
                }

                // Receive reply
                String reply = in.readLine();
                System.out.println("Server: " + reply);

                if (reply.equalsIgnoreCase("bye")) {
                    System.out.println("Server ended the chat.");
                    break;
                }
            }

            socket.close();
            sc.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}