/*
 * Author: William Hipschman
 */




/*
 * This class parses local part commands
 */
public class LocalPart extends StringToken{

	public static final String ERROR = "local-part";

	private SMTPString smtpString;

	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid local part token
	 */
	public LocalPart(String string) throws InvalidSMTPException{

		smtpString = new SMTPString(string);

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public SMTPString getSMTPString(){
		return smtpString;
	}
}
