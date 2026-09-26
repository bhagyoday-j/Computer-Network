import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(5003);

            Socket s = ss.accept();

            DataInputStream in = new DataInputStream(s.getInputStream());
            DataOutputStream out = new DataOutputStream(s.getOutputStream());

            double angle = in.readDouble();
            String choice = in.readUTF();

            double result = 0;

            double rad = Math.toRadians(angle);

            switch(choice) {
                case "sin":
                    result = Math.sin(rad);
                    break;
                case "cos":
                    result = Math.cos(rad);
                    break;
                case "tan":
                    result = Math.tan(rad);
                    break;
            }

            out.writeDouble(result);

            s.close();
            ss.close();

        } catch(Exception e) {
            System.out.println(e);
        }
    }
}