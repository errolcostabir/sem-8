import java.net.*;
import java.io.*;

public class Server{
    public static void main(String[] args) throws IOException{
        ServerSocket ss=new ServerSocket(5000);
        System.out.println("Server Started....Waiting for Client");
        Socket s=ss.accept();
        System.out.println("Client Connected");
        InputStreamReader in=new InputStreamReader(s.getInputStream());
        BufferedReader bf=new BufferedReader(in);
        InputStreamReader r=new InputStreamReader(System.in);
        BufferedReader bfr=new BufferedReader(r);
        String str="";
        String str1="";

        while(!str1.equals("bye")||!str.equals("bye")) {
            str = bf.readLine();
            System.out.println("Client: " + str);
            str1 = bfr.readLine();
            PrintWriter pr = new PrintWriter(s.getOutputStream());
            pr.println(str1);
            pr.flush();
        }
        bf.close();
        r.close();
        bfr.close();
        in.close();
    }
}