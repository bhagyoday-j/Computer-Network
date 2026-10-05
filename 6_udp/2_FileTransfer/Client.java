import java.io.*;
import java.net.*;

public class Client {
    private static final int SERVER_PORT = 5001;
    private static final int MAX_PACKET_SIZE = 65507;
    private static final int TIMEOUT = 3000; // 3 seconds timeout for receiving

    public static void main(String[] args) {
        String serverAddress = "localhost";
        String[] filesToRequest = {
            "sample.txt",
            "sample.script",
            "sample.mp3",
            "sample.mp4"
        };

        try {
            DatagramSocket socket = new DatagramSocket();
            socket.setSoTimeout(TIMEOUT);

            for (String fileName : filesToRequest) {
                System.out.println("\nRequesting file: " + fileName);
                receiveFile(socket, serverAddress, SERVER_PORT, fileName);
            }

            socket.close();
            System.out.println("\nAll file transfers complete.");

        } catch (Exception e) {
            System.out.println("Client error: " + e);
            e.printStackTrace();
        }
    }

    private static void receiveFile(DatagramSocket socket, String serverAddr, int port, String fileName) {
        try {
            InetAddress server = InetAddress.getByName(serverAddr);

            // Send request
            byte[] reqData = fileName.getBytes();
            DatagramPacket reqPacket = new DatagramPacket(reqData, reqData.length, server, port);
            socket.send(reqPacket);

            // Receive packets
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            int expectedTotal = -1;
            int lastSeq = -1;
            int packetsReceived = 0;

            while (true) {
                byte[] recvBuffer = new byte[MAX_PACKET_SIZE];
                DatagramPacket recvPacket = new DatagramPacket(recvBuffer, recvBuffer.length);

                try {
                    socket.receive(recvPacket);
                } catch (SocketTimeoutException e) {
                    System.out.println("Timeout waiting for packet, retrying request...");
                    socket.send(reqPacket);
                    continue;
                }

                DataInputStream dis = new DataInputStream(
                    new ByteArrayInputStream(recvPacket.getData(), 0, recvPacket.getLength()));

                int seq = dis.readInt();
                int totalPackets = dis.readInt();
                int dataLength = dis.readInt();
                String fileType = dis.readUTF();
                String recvFileName = dis.readUTF();

                // Error packet
                if (seq == -1) {
                    String errorMsg = dis.readUTF();
                    System.out.println("Server error: " + errorMsg);
                    return;
                }

                // First packet - set expected total
                if (expectedTotal == -1) {
                    expectedTotal = totalPackets;
                    System.out.println("Receiving " + recvFileName + " (" + fileType + ")");
                    System.out.println("Expected " + totalPackets + " packets");
                }

                // Write data
                byte[] data = new byte[dataLength];
                dis.read(data, 0, dataLength);
                bos.write(data);

                packetsReceived++;
                System.out.println("Received packet " + (seq + 1) + "/" + totalPackets +
                    " (" + dataLength + " bytes)");

                lastSeq = seq;

                // Check if all packets received
                if (packetsReceived == expectedTotal) {
                    break;
                }
            }

            // Write to file
            String outputFileName = "received_" + fileName;
            FileOutputStream fos = new FileOutputStream(outputFileName);
            fos.write(bos.toByteArray());
            fos.close();

            System.out.println("File saved as: " + outputFileName + " (" + bos.size() + " bytes)");

        } catch (Exception e) {
            System.out.println("Error receiving " + fileName + ": " + e);
            e.printStackTrace();
        }
    }
}