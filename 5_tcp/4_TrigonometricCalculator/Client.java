import java.io.*;
import java.net.*;
import java.util.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket s = new Socket("localhost", 5003);

            DataInputStream in = new DataInputStream(s.getInputStream());
            DataOutputStream out = new DataOutputStream(s.getOutputStream());

            Scanner sc = new Scanner(System.in);

            System.out.print("Enter Angle: ");
            double angle = sc.nextDouble();

            System.out.print("Function (sin/cos/tan): ");
            String func = sc.next();

            out.writeDouble(angle);
            out.writeUTF(func);

            double result = in.readDouble();

            System.out.println("Result = " + result);

            s.close();

        } catch(Exception e) {
            System.out.println(e);
        }
    }
}