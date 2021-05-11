import java.io.*;
import java.rmi.*;
import java.rmi.server.*;

public class CalcImpl extends UnicastRemoteObject implements CalcIntf{
    public CalcImpl() throws RemoteException{}
    public long add(long l1,long l2) throws RemoteException{
        return l1+l2;
    }
    public long sub(long l1,long l2) throws RemoteException{
        return l1-l2;
    }
    public long mul(long l1,long l2) throws RemoteException{
        return l1*l2;
    }
    public long div(long l1,long l2) throws RemoteException{
        return l1/l2;
    }
}

