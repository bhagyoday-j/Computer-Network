import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Server {
    private static final int PORT = 5000;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(PORT);
            System.out.println("UDP Server started on port " + PORT);
            System.out.println("Waiting for client messages...");

            Scanner sc = new Scanner(System.in);
            boolean chatting = true;

            while (chatting) {
                // Receive message from client
                byte[] recvBuffer = new byte[1024];
                DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);
                socket.receive(recvPacket);

                String clientMsg = new String(recvPacket.getData(), 0, recvPacket.getLength());
                System.out.println("Client: " + clientMsg);

                if (clientMsg.equalsIgnoreCase("bye")) {
                    System.out.println("Client ended the chat.");
                    chatting = false;
                    break;
                }

                // Get server reply
                System.out.print("Server: ");
                String reply = sc.nextLine();

                // Send reply to client
                byte[] sendData = reply.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(
                    sendData, sendData.length,
                    recvPacket.getAddress(), recvPacket.getPort()
                );
                socket.send(sendPacket);

                if (reply.equalsIgnoreCase("bye")) {
                    System.out.println("Chat ended.");
                    chatting = false;
                }
            }
            sc.close();
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        }
    }
}