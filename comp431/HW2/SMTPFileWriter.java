

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class SMTPFileWriter {

	public static final String BASE_FILE_NAME = "forward/";
	public static final String FROM = "From: ";
	public static final String TO = "To: ";
	public static final String NEWLINE = "\n";
	public static final String DOT_TXT = ".txt";

	public void writeFile(MailFromCommand mail, List<String> data, List<RcptToCommand> recipients) throws IOException{

		for(Token forwardPath : recipients){

			// Create file 
			File f = new File(BASE_FILE_NAME + ((RcptToCommand)forwardPath).getForwardPath().getPath().getMailBox().getToken() + DOT_TXT);

			/*if there is an error creating the file an exception is thrown
			 * and caught in main().  The program will then exit because it
			 * is not one of the errors specified in the assignment.
			 */
			if(!f.exists())
				f.createNewFile();

			FileWriter fstream = new FileWriter(f,true);
			BufferedWriter out = new BufferedWriter(fstream);

			out.write(FROM);
			out.write(mail.getReversePath().getPath().getMailBox().getToken() + NEWLINE);

			for(Token recipient : recipients)
				out.write(TO + ((RcptToCommand)recipient).getForwardPath().getPath().getMailBox().getToken() + NEWLINE);

			for(int i = 0; i < data.size(); i++)
				out.write(data.get(i) + NEWLINE);

			//Close the output stream
			out.close();
		}
	}
}
