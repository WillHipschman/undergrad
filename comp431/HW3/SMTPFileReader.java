/*
 * Author: William Hipschman
 */



import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;



/*
 * This class reads from a properly formatted file
 * and outputs the smtp commands the send that file
 * to a server
 */
public class SMTPFileReader {

	/*
	 * Parameters: The name of the file to be read in
	 * 
	 * Precondition: If the file exists it is properly formatted
	 * 
	 * Postcondition: If the method succeeds (an exception is not thrown)
	 *     then valid smtp command that correspond to the text in the file
	 *     are written to stdout
	 */
	public void readMail(String path){

		try {

			FileReader fStream = new FileReader(path);
			BufferedReader in = new BufferedReader(fStream);

			processFile(in);
			
			System.out.println(QuitCommand.QUIT_COMMAND);

		}//quit if the file is not found 
		catch (FileNotFoundException e) {
			System.exit(-1);
		}//quit if there is an I/O exception 
		catch (IOException e) {
			System.exit(-1);
		}//quit if the smtp response headers are not ok 
		catch (InvalidSMTPResponseException e) {
			System.exit(-1);
		}
	}
	/*
	 * This method handles the main logic loop for reading from a file
	 * and writing out the smtp commands. Nested try/catch blocks are
	 * used such that the token types can be tested without uncaught
	 * exceptions if the token doesn't match one of the the valid types
	 * (but matches another valid type).
	 * 
	 * Parameters: A BufferedReader from the file in question
	 * 
	 * Precondition: The BufferedReader is valid and the file
	 *     it reads from is well-formed.
	 *     
	 * Postcondition: If the method succeeds (an exception is not thrown)
	 *     then valid smtp command that correspond to the text in the file
	 *     are written to stdout
	 * 
	 */
	private void processFile(BufferedReader in) throws InvalidSMTPResponseException, IOException{

		String line;

		boolean firstTime = true;
		boolean firstData = true;

		/*
		 * The assignment says the file will be correctly
		 * formatted so it is not necessary to create a state
		 * machine to make sure the commands are in the correct order.
		 * If the file is correct then the commands will be correct.
		 */
		while((line = in.readLine()) != null){
			try {
				MailFromLine token = new MailFromLine(line);
				
				/* 
				 * If this is not the first time through the loop then add the
				 * <CLRF>.<CLRF>
				 */
				if(firstTime)
					firstTime = false;
				else{
					System.out.println(DataCommand.DATA_TERMINATOR);
					processSMTPResponse(Token.OK_250);
				}
				firstData = true;
				System.out.println(MailFromCommand.MAIL_FROM + Path.LEFT_PATH + token.getMailBox().getToken()+ Path.RIGHT_PATH);
				
				processSMTPResponse(Token.OK_250);

			} catch (InvalidMailFileException e) {
				try {
					MailToLine token = new MailToLine(line);
					System.out.println(RcptToCommand.RCPT_TO + Path.LEFT_PATH + token.getMailBox().getToken()+ Path.RIGHT_PATH);
					processSMTPResponse(Token.OK_250);
				} catch (InvalidMailFileException e1) {

					/*
					 * If this is the first data command in the message
					 * then print out the data command.
					 */
					if(firstData){
						System.out.println(DataCommand.DATA_COMMAND);
						firstData = false;
						
						processSMTPResponse(Token.OK_354);
					}
					System.out.println(line);
				}
			}
		}
		System.out.println(DataCommand.DATA_TERMINATOR);
		processSMTPResponse(Token.OK_250);
	}

	/*
	 * This method is responsible for making sure the smtp response
	 * messages that are given through stdin allow the program to
	 * continue. If they are no 250 or 354 then the program terminates.
	 * 
	 * Parameters: A string containing the number that must must be entered
	 *     for the program to continue
	 *     
	 * Precondition: A vlid smtp command was just output to stdout
	 * 
	 * Postcondition: Either a 250 or 354 smtp response was entered
	 *     and the program continues or another number was entered
	 *     and the program terminates.
	 */
	private void processSMTPResponse(String responseNumber) throws IOException, InvalidSMTPResponseException{

		int index1 = 0;
		int index2 = 3;

		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);

		String line = br.readLine();
		
		if(!line.substring(index1, index2).equals(responseNumber))
			throw new InvalidSMTPResponseException(Token.SMTP_RESPONSE_ERROR);
		else
			System.out.println(line);
	}
}
