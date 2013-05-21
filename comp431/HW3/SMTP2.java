/*
 * Author: William Hipschman
 */




/*
 * This is the main class for HW3
 */
public class SMTP2 {
	
	/*
	 * This program reads from a file specified as a parameter as
	 * given in SMTPFileReader
	 */
	public static void main(String[] args){
		
		/*
		 * Incorrect number of arguments terminates without 
		 * debugging or prompt info
		*/
		if(args.length != 1)
			System.exit(-1);
		String file = args[0];
		
		SMTPFileReader reader = new SMTPFileReader();
		
		reader.readMail(file);
	}
}
