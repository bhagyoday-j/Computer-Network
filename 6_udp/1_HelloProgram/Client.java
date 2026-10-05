import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
    private static final int SERVER_PORT = 5000;
    private static final int TIMEOUT = 3000;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
            socket.setSoTimeout(TIMEOUT);
            InetAddress server = InetAddress.getByName("localhost");

            Scanner sc = new Scanner(System.in);
            boolean chatting = true;

            while (chatting) {
                // Send message
                System.out.print("Client: ");
                String msg = sc.nextLine();

                byte[] sendData = msg.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(
                    sendData, sendData.length, server, SERVER_PORT
                );
                socket.send(sendPacket);

                if (msg.equalsIgnoreCase("bye")) {
                    System.out.println("Chat ended.");
                    chatting = false;
                    break;
                }

                // Receive reply with retry on timeout
                while (true) {
                    try {
                        byte[] recvBuffer = new byte[1024];
                        DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);
                        socket.receive(recvPacket);

                        String reply = new String(recvPacket.getData(), 0, recvPacket.getLength());
                        System.out.println("Server: " + reply);

                        if (reply.equalsIgnoreCase("bye")) {
                            System.out.println("Server ended the chat.");
                            chatting = false;
                        }
                        break;
                    } catch (SocketTimeoutException e) {
                        System.out.println("(timeout) Resending message...");
                        socket.send(sendPacket);
                    }
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