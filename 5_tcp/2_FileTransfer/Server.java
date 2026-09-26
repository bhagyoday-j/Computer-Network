import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(5001);
            System.out.println("Waiting for client...");

            Socket s = ss.accept();

            FileInputStream fis = new FileInputStream("sample.txt");
            OutputStream os = s.getOutputStream();

            byte[] buffer = new byte[4096];
            int count;

            while ((count = fis.read(buffer)) > 0) {
                os.write(buffer, 0, count);
            }

            System.out.println("File Sent");

            fis.close();
            s.close();
            ss.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}