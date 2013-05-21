import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class testServer{
    
    
    public static void main(String[] args){
	
	if(args.length != 1)
	    System.exit(-1);
	int portNumber = Integer.parseInt(args[0]);

	while(true){
	    try {
		ServerSocket socket = new ServerSocket(portNumber);
		
		Socket client = socket.accept();
		
		
		
		PrintWriter out = new PrintWriter(client.getOutputStream(), true);
		
				
		InputStreamReader isr = new InputStreamReader(client.getInputStream());
		BufferedReader br = new BufferedReader(isr);

		String tempLine;
		while((tempLine = br.readLine()) != null)
		    System.out.println(tempLine);
	    }
	    catch(Exception e){
		System.exit(-1);
	    }
	}
    }
}