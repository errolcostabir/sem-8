import java.io.*;
import java.net.*;
class Udp_client
{
public static DatagramSocket clientsocket;
public static DatagramPacket dp;
public static BufferedReader dis;
public static InetAddress ia;
public static byte buf[] = new byte[1024];
public static int cport = 789, sport = 790;
public static void main(String[] a) throws IOException
{
clientsocket = new DatagramSocket(cport);
dp = new DatagramPacket(buf, buf.length);
dis = new BufferedReader(new
InputStreamReader(System.in));
ia = InetAddress.getLocalHost();
System.out.println("Client is Running... Type 'STOP/stop'to Quit");
while(true)
{
System.out.print("Client:");
String str = new String(dis.readLine());
buf = str.getBytes();
if(str.equalsIgnoreCase("STOP"))
{
System.out.println("Terminated...");
clientsocket.send(new
DatagramPacket(buf,str.length(), ia,sport));
break;
}
clientsocket.send(new DatagramPacket(buf,str.length(), ia, sport));
clientsocket.receive(dp);
String str2 = new String(dp.getData(), 0,dp.getLength());
System.out.println("Server: " + str2);
}
}
}
