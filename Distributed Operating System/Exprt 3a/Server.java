import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
import java.net.*;
import java.io.*;

public class Server{
    public static void main(String args[]) throws IOException{
        ServerSocket ss=new ServerSocket(5000);
        System.out.println("Server started...Waiting for Client");
        Socket s=ss.accept();
        System.out.println("Client Connected");
        InputStreamReader in=new InputStreamReader(s.getInputStream());
        BufferedReader bf=new BufferedReader(in);
        String str=""; String str1="";
        str=bf.readLine();
        if(str.equals("Send Time")){
            DateTimeFormatter dtf=DateTimeFormatter.ofPattern("HH:mm");
            LocalDateTime now=LocalDateTime.now();
            str1=dtf.format(now);
        }
        else{
            str1="Sorry..can't help";
        }
        PrintWriter pr=new PrintWriter(s.getOutputStream());
        pr.println(str1);
        pr.flush();
        in.close();
        bf.close();
    }
}