import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(5002);
            System.out.println("Waiting...");

            Socket s = ss.accept();

            DataInputStream in = new DataInputStream(s.getInputStream());
            DataOutputStream out = new DataOutputStream(s.getOutputStream());

            double a = in.readDouble();
            double b = in.readDouble();
            String op = in.readUTF();

            double result = 0;

            switch(op) {
                case "+": result = a + b; break;
                case "-": result = a - b; break;
                case "*": result = a * b; break;
                case "/": result = a / b; break;
            }

            out.writeDouble(result);

            s.close();
            ss.close();

        } catch(Exception e) {
            System.out.println(e);
        }
    }
}