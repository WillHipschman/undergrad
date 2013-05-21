/*
 * Author: William Hipschman
 */




/*
 * This is the main class for HW3
 */
public class Client {
	
	/*
	 * This program reads from a file specified as a parameter as
	 * given in SMTPFileReader
	 */
	public static void main(String[] args){
		
		/*
		 * Incorrect number of arguments terminates without 
		 * debugging or prompt info
		*/
		if(args.length != 2)
		    System.out.println("1");
			System.exit(-1);
		String hostname = args[0];
		String portNumber = args[1];
		
		SMTPFileReader reader = new SMTPFileReader();
		
		reader.readMail(hostname, portNumber);
	}
}
