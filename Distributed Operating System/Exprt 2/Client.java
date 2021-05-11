import java.rmi.*;
import java.io.*;

public class Client{
    public static void main(String args[]){
            try{
                String s1;
                BufferedReader input;
                input =new BufferedReader(new InputStreamReader(System.in));
                int n1,n2;
                System.out.println("Enter n1: ");
                n1=Integer.parseInt(input.readLine());

                System.out.println("Enter n2: ");
                n2=Integer.parseInt(input.readLine());

                String serverURL="rmi://localhost/server";

                CalcIntf calcintf=(CalcIntf)Naming.lookup(serverURL);

                System.out.println("\nThe sum: "+calcintf.add(n1,n2));
                System.out.println("\nThe diff: "+calcintf.sub(n1,n2));
                System.out.println("\nThe Mul: "+calcintf.mul(n1,n2));
                System.out.println("\nThe Div: "+calcintf.div(n1,n2));

            }
            catch (Exception e){
                System.out.println("Exception: "+e);
            }
    }
}