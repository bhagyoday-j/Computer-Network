import java.io.*;
import java.net.*;

public class Server {
    private static final int PORT = 5001;
    private static final int MAX_PACKET_SIZE = 65507; // Max UDP datagram size
    private static final int HEADER_SIZE = 20; // seq(4) + totalPackets(4) + dataLen(4) + fileType(4) + fileNameLen(4)
    private static final int DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;

    public static void main(String[] args) {
        try {
            DatagramSocket socket = new DatagramSocket(PORT);
            System.out.println("UDP Server started on port " + PORT);
            System.out.println("Waiting for client request...");

            // Receive request from client
            byte[] reqBuffer = new byte[MAX_PACKET_SIZE];
            DatagramPacket reqPacket = new DatagramPacket(reqBuffer, reqBuffer.length);
            socket.receive(reqPacket);

            String requestedFile = new String(reqPacket.getData(), 0, reqPacket.getLength()).trim();
            System.out.println("Client requested file: " + requestedFile);

            // Check if file exists
            File file = new File(requestedFile);
            if (!file.exists()) {
                System.out.println("File not found: " + requestedFile);
                // Send error packet
                sendError(socket, reqPacket.getAddress(), reqPacket.getPort());
                socket.close();
                return;
            }

            // Determine file type
            String fileType = getFileType(requestedFile);
            System.out.println("File type: " + fileType);

            // Read file into byte array
            byte[] fileData = new byte[(int) file.length()];
            FileInputStream fis = new FileInputStream(file);
            fis.read(fileData);
            fis.close();

            // Split into packets
            int totalPackets = (int) Math.ceil((double) fileData.length / DATA_SIZE);
            System.out.println("Total packets to send: " + totalPackets);

            // Send each packet
            for (int seq = 0; seq < totalPackets; seq++) {
                int start = seq * DATA_SIZE;
                int length = Math.min(DATA_SIZE, fileData.length - start);
                byte[] packetData = createPacket(seq, totalPackets, length, fileType, requestedFile, fileData, start);

                DatagramPacket sendPacket = new DatagramPacket(
                    packetData, packetData.length,
                    reqPacket.getAddress(), reqPacket.getPort()
                );
                socket.send(sendPacket);
                System.out.println("Sent packet " + (seq + 1) + "/" + totalPackets +
                    " (" + length + " bytes data)");
            }

            System.out.println("File transfer complete: " + requestedFile);
            socket.close();

        } catch (Exception e) {
            System.out.println("Server error: " + e);
            e.printStackTrace();
        }
    }

    private static byte[] createPacket(int seq, int totalPackets, int dataLength,
                                       String fileType, String fileName, byte[] fileData, int start) {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

        try {
            // Header
            dos.writeInt(seq);
            dos.writeInt(totalPackets);
            dos.writeInt(dataLength);
            dos.writeUTF(fileType);
            dos.writeUTF(fileName);
            // Data
            dos.write(fileData, start, dataLength);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return bos.toByteArray();
    }

    private static void sendError(DatagramSocket socket, InetAddress addr, int port) {
        try {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(bos);
            dos.writeInt(-1); // seq = -1 indicates error
            dos.writeUTF("ERROR: File not found");
            byte[] data = bos.toByteArray();
            DatagramPacket errPacket = new DatagramPacket(data, data.length, addr, port);
            socket.send(errPacket);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String getFileType(String fileName) {
        String ext = fileName.substring(fileName.lastIndexOf(".") + 1).toLowerCase();
        switch (ext) {
            case "txt": case "script": case "sh": case "java": case "py": return "TEXT";
            case "mp3": case "wav": case "aac": return "AUDIO";
            case "mp4": case "avi": case "mov": case "mkv": return "VIDEO";
            default: return "UNKNOWN";
        }
    }
}