import java.io.*;
import java.net.*;
import java.util.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket s = new Socket("localhost", 5002);

            DataInputStream in = new DataInputStream(s.getInputStream());
            DataOutputStream out = new DataOutputStream(s.getOutputStream());

            Scanner sc = new Scanner(System.in);

            System.out.print("Enter Number 1: ");
            double a = sc.nextDouble();

            System.out.print("Enter Number 2: ");
            double b = sc.nextDouble();

            System.out.print("Operation (+,-,*,/): ");
            String op = sc.next();

            out.writeDouble(a);
            out.writeDouble(b);
            out.writeUTF(op);

            double result = in.readDouble();

            System.out.println("Result = " + result);

            s.close();

        } catch(Exception e) {
            System.out.println(e);
        }
    }
}