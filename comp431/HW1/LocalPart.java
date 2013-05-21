/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class LocalPart extends StringToken{

	public static final String ERROR = "local-part";

	private SMTPString smtpString;

	public LocalPart(String string) throws InvalidSMTPException{

		smtpString = new SMTPString(string);

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public SMTPString getSMTPString(){
		return smtpString;
	}
}
