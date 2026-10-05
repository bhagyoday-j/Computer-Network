import java.io.*;
import java.net.*;

public class Server {
    private static final int PORT = 5003;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(PORT);
            System.out.println("UDP Trigonometric Server started on port " + PORT);
            System.out.println("Waiting for calculations...");

            while (true) {
                // Receive request from client
                byte[] recvBuffer = new byte[1024];
                DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);
                socket.receive(recvPacket);

                DataInputStream dis = new DataInputStream(
                    new ByteArrayInputStream(recvPacket.getData(), 0, recvPacket.getLength()));

                double angle = dis.readDouble();
                String choice = dis.readUTF();

                double result = 0;
                boolean valid = true;

                double rad = Math.toRadians(angle);

                switch (choice) {
                    case "sin": result = Math.sin(rad); break;
                    case "cos": result = Math.cos(rad); break;
                    case "tan":
                        if (Math.cos(rad) != 0) result = Math.tan(rad);
                        else valid = false;
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

                System.out.println("Computed " + choice + "(" + angle + ") = " + result);
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