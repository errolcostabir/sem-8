import java.io.File;
import java.io.IOException;
import org.apache.commons.io.FileUtils;
class E5{
    public static void main(String args[]) throws IOException{
           File input = new File("C:\\Users\\XAVIER MATHIAS\\Documents\\sem 8\\source.txt");
            File output = new File("C:\\Users\\XAVIER MATHIAS\\Documents\\sem 8\\dest.txt");
            long start=System.nanoTime();
            copyFileUsingApacheCommonsIO(source,dest);
            long end=System.nanoTime();
            System.out.println("Time taken by Apache Commons IO copy= "+(end-start));
    }
    private static void copyFileUsingApacheCommonsIO(File source,File dest) throws IOException{
        FileUtils.copyFile(source,dest);
    }
}