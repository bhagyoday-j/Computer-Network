import java.io.*;
import java.net.*;
import java.util.*;

public class Client {
    private static final int SERVER_PORT = 5003;
    private static final int TIMEOUT = 3000;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
            socket.setSoTimeout(TIMEOUT);
            InetAddress server = InetAddress.getByName("localhost");

            Scanner sc = new Scanner(System.in);

            System.out.print("Enter Angle: ");
            double angle = sc.nextDouble();

            System.out.print("Function (sin/cos/tan): ");
            String func = sc.next();

            // Build request packet
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(bos);
            dos.writeDouble(angle);
            dos.writeUTF(func);
            dos.close();

            byte[] reqData = bos.toByteArray();
            DatagramPacket reqPacket = new DatagramPacket(
                reqData, reqData.length, server, SERVER_PORT
            );

            // Send with retry
            while (true) {
                try {
                    socket.send(reqPacket);

                    byte[] recvBuffer = new byte[1024];
                    DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);
                    socket.receive(recvPacket);

                    DataInputStream dis = new DataInputStream(
                        new ByteArrayInputStream(recvPacket.getData(), 0, recvPacket.getLength()));

                    boolean valid = dis.readBoolean();
                    double result = dis.readDouble();

                    if (valid) {
                        System.out.println("Result = " + result);
                    } else {
                        System.out.println("Error: Invalid function or undefined result");
                    }
                    break;
                } catch (SocketTimeoutException e) {
                    System.out.println("(timeout) Resending request...");
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