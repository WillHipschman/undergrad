/*
 * Author: William Hipschman
 */



import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;



/*
 * This class is the main executable class for HW1 and HW2
 * It reads smtp commands from stdin. If the commands are valid
 * and given in the correct order (as specified in SMTPStateMachine)
 * then they are echoed to stdout along with a smtp response number.
 * 
 * Finally the contents of the mail message are written to file as
 * specified in SMTPFileWriter
 */
public class SMTP1 {

	/*
	 * This program creates objects out of every part
	 * of the smtp command.  It was built this way to make 
	 * every portion of the command extendible, able to be
	 * manipulated and used separate from the other portions.
	 * Each object contains objects that represent the pieces
	 * in the grammar below it.  For example the MailFromCommand
	 * contains a ReversePath which contains a Path which contains
	 * a MailBox which contains a LocalPart and a Domain...etc.
	 *
	 * We nest the try catch blocks because if one
	 * command instantiation fails it might be the
	 * case that another command instantiation
	 * will succeed.  i.e.  It is not a valid mail
	 * command but it is a valid rcpt command.
	 */
	public static void main(String[] args){

		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);
		List<String> fileWritingData = new ArrayList<String>();
		List<RcptToCommand> fileWritingRecipients = new ArrayList<RcptToCommand>();
		MailFromCommand mail = null;

		SMTPFileWriter writer = new SMTPFileWriter();

		try {
			String line = br.readLine();
			SMTPStateMachine stateMachine = new SMTPStateMachine();
			while(line != null){

				try{
					try {

						//If the command is successfully instantiated it is valid
						MailFromCommand c = new MailFromCommand(line);

						stateMachine.validToken(c);

						System.out.println(c.getToken());
						System.out.println(stateMachine.getReturnMessage());

						//used for file writing
						mail = c;

						line = br.readLine();
					} catch (InvalidCommandException e) {
						//it is not a valid mail from command
						try {
							RcptToCommand c = new RcptToCommand(line);

							stateMachine.validToken(c);

							System.out.println(c.getToken());
							System.out.println(stateMachine.getReturnMessage());

							fileWritingRecipients.add(c);

							line = br.readLine();
						} catch (InvalidCommandException e1) {
							//it is not a valid mail from or rcpt to command
							try {
								DataCommand c = new DataCommand(line);

								stateMachine.validToken(c);

								System.out.println(c.getToken());
								System.out.println(stateMachine.getReturnMessage());

								processData(br, fileWritingData);

								System.out.println(SMTPStateMachine.SUCCESS);

								writer.writeFile(mail, fileWritingData, fileWritingRecipients);

								fileWritingData.clear();
								fileWritingRecipients.clear();

								line = br.readLine();
							} catch (InvalidCommandException e2) {
								//it is not a valid command

								/*
								 * We do not need to clear the file writing
								 * data because the previous successful commands
								 * are still valid.
								 */
								System.out.println(line);
								System.out.println(e.getMessage());
								line = br.readLine();
							}
						}
					}
				}catch (InvalidSMTPException e) {
					//if this catch block is reached then the command was
					//valid but had incorrect parameters

					/*
					 * We do not need to clear the file writing
					 * data because the previous successful commands
					 * are still valid.
					 * */
					System.out.println(line);
					System.out.println(e.getMessage());
					line = br.readLine();
				} catch (BadCommandSequenceException e){
					//valid command, out of sequence

					/*
					 * We do not need to clear the file writing
					 * data because the previous successful commands
					 * are still valid.
					 * */
					System.out.println(line);
					System.out.println(e.getMessage());
					line = br.readLine();
				}
			} 
		} catch (IOException e) {
			//exit without printing debugging/status info
			System.exit(-1);
		}
	}
	/*
	 * This method reads data from stdin until a 
	 * <CLRF>.<CLRF> is encountered
	 */
	private static void processData(BufferedReader br, List<String> fileWritingData) throws IOException{
		String line;
		while(!(line = br.readLine()).equals(DataCommand.DATA_TERMINATOR)){
			System.out.println(line);
			fileWritingData.add(line);
		}
		System.out.println(line);
	}
}