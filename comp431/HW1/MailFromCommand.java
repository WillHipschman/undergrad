/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class MailFromCommand extends StringToken{

	public static final String MAIL_FROM_COMMAND = "[Mm][Aa][Ii][Ll] [Ff][Rr][Oo][Mm]:";
	public static final String ERROR = "mail-from-cmd";
	public static final int MAIL_FROM_BEGIN = 0;
	public static final int MAIL_FROM_END = 10;
	public static final int REVERSE_PATH_BEGIN = 10;

	private ReversePath reversePath;

	/*Every smtp.token class checks the validity of the argument
	 * in the constructor.  If the argument is not valid an exception
	 * is thrown.  Therefore if the constructor finishes and the object
	 * is instantiated the argument must be a valid token of that type.
	 */
	public MailFromCommand(String string) throws InvalidSMTPException{

		try{
			//I do not use the StringTokenizer class because it is deprecated
			//and the documentation says that the split() function or regexes
			//should be used instead.

			//if the first ten characters are not some case
			//insensitive form of 'mail from:' then an exception is thrown
			if(!string.substring(MAIL_FROM_BEGIN, MAIL_FROM_END).matches(MAIL_FROM_COMMAND))
				throw new InvalidSMTPException(Token.ERROR + ERROR);

			String newLine = string.substring(REVERSE_PATH_BEGIN);

			reversePath = new ReversePath(newLine);

		}catch(StringIndexOutOfBoundsException e){
			//If input is too short then an exception is thrown
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		}

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public ReversePath getReverseStringToken(){
		return reversePath;
	}
}
