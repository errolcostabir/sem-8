import java.net.*;
import java.io.*;

public class Client{
    public static void main(String[] args) throws IOException{
        Socket s=new Socket("localhost",5000);

        //read input of client from user
        InputStreamReader r=new InputStreamReader(System.in);
        BufferedReader bfr=new BufferedReader(r);
        InputStreamReader in=new InputStreamReader(s.getInputStream());
        BufferedReader bf=new BufferedReader(in);
        String str1="";
        String str="";

        while(!str.equals("bye")) {
            str1 = bfr.readLine();
            PrintWriter pr = new PrintWriter(s.getOutputStream());
            pr.println(str1);
            pr.flush();
            //display server message to user.
            str = bf.readLine();
            System.out.println("Server: " + str);
        }
        bf.close();
        r.close();
        bfr.close();
        in.close();
    }
}
