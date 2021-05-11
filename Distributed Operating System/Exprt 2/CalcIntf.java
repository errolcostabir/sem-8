import java.rmi.*;
public interface CalcIntf extends Remote
{
    public long add(long l1,long l2) throws RemoteException;
    public long sub(long l1,long l2) throws RemoteException;
    public long mul(long l1,long l2) throws RemoteException;
    public long div(long l1,long l2) throws RemoteException;
}
