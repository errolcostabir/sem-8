import java.io.*;
import java.rmi.*;

public class Server
{
    public static void main(String args[])
    {
        try{
            CalcImpl calcimpl = new CalcImpl();
            Naming.rebind("server",calcimpl);
        }
        catch(Exception e)
        {
            System.out.println("Execption:"+e);
        }
    }
}
