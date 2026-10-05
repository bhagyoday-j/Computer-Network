import java.io.*;
import java.net.*;

public class Server {
    private static final int PORT = 5002;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(PORT);
            System.out.println("UDP Arithmetic Server started on port " + PORT);
            System.out.println("Waiting for calculations...");

            while (true) {
                // Receive request from client
                byte[] recvBuffer = new byte[1024];
                DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);
                socket.receive(recvPacket);

                DataInputStream dis = new DataInputStream(
                    new ByteArrayInputStream(recvPacket.getData(), 0, recvPacket.getLength()));

                double a = dis.readDouble();
                double b = dis.readDouble();
                String op = dis.readUTF();

                double result = 0;
                boolean valid = true;

                switch (op) {
                    case "+": result = a + b; break;
                    case "-": result = a - b; break;
                    case "*": result = a * b; break;
                    case "/":
                        if (b != 0) result = a / b;
                        else { valid = false; }
                        break;
                    default: valid = false;
                }

                // Send result back
                ByteArrayOutputStream bos = new ByteArrayOutputStream();
                DataOutputStream dos = new DataOutputStream(bos);
                dos.writeBoolean(valid);
                dos.writeDouble(result);
                dos.close();

                byte[] sendData = bos.toByteArray();
                DatagramPacket sendPacket = new DatagramPacket(
                    sendData, sendData.length,
                    recvPacket.getAddress(), recvPacket.getPort()
                );
                socket.send(sendPacket);

                System.out.println("Computed: " + a + " " + op + " " + b + " = " + result);
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        }
    }
}