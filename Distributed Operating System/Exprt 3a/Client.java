import java.net.*;
import java.io.*;

public class Client{
    public static void main(String args[]) throws IOException{
        Socket s=new Socket("localhost",5000);
        InputStreamReader r=new InputStreamReader(System.in);
        BufferedReader bfr=new BufferedReader(r);
        InputStreamReader in=new InputStreamReader(s.getInputStream());
        BufferedReader bf=new BufferedReader(in);
        String str1=""; String str="";
        str1 = bfr.readLine();
        PrintWriter pr = new PrintWriter(s.getOutputStream());
        pr.println(str1);
        pr.flush();
        //display server time to client.
        str = bf.readLine();
        System.out.println("Server Time: " + str);
        bf.close();
        r.close();
        bfr.close();
        in.close();
    }
}