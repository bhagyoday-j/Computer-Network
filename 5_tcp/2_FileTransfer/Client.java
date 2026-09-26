import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket s = new Socket("localhost", 5001);

            InputStream is = s.getInputStream();
            FileOutputStream fos = new FileOutputStream("received.txt");

            byte[] buffer = new byte[4096];
            int count;

            while ((count = is.read(buffer)) > 0) {
                fos.write(buffer, 0, count);
            }

            System.out.println("File Received");

            fos.close();
            s.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}