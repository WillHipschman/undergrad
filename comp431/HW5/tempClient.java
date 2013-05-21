import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


public class tempClient {


    public static void main(String[] args){

	if(args.length != 2)
	    System.exit(-1);
	String hostname = args[0];
	String portNumber = args[1];


	try{
	    Socket server = new Socket(hostname, Integer.parseInt(portNumber));
	    PrintWriter out = new PrintWriter(server.getOutputStream(), true);
	    InputStreamReader isr = new InputStreamReader(server.getInputStream());
	    BufferedReader serverIn = new BufferedReader(isr);
	    
	    int i =0;
	    for(i =0; i< 10; i++)
		out.println(i);
	    out.close();
	    isr.close();
	}catch(Exception e){
	    e.printStackTrace();
	    System.exit(-1);
	}
    }   
}