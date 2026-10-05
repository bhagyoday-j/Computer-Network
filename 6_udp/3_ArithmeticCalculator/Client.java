import java.io.*;
import java.net.*;
import java.util.*;

public class Client {
    private static final int SERVER_PORT = 5002;
    private static final int TIMEOUT = 3000;

    public static void main(String[] args) {
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
            socket.setSoTimeout(TIMEOUT);
            InetAddress server = InetAddress.getByName("localhost");

            Scanner sc = new Scanner(System.in);

            System.out.print("Enter Number 1: ");
            double a = sc.nextDouble();

            System.out.print("Enter Number 2: ");
            double b = sc.nextDouble();

            System.out.print("Operation (+,-,*,/): ");
            String op = sc.next();

            // Build request packet
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(bos);
            dos.writeDouble(a);
            dos.writeDouble(b);
            dos.writeUTF(op);
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
                        System.out.println("Error: Invalid operation or division by zero");
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