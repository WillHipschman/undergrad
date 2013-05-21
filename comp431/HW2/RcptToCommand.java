


public class RcptToCommand extends StringToken{

	public static final String RCPT_TO_COMMAND = "[Rr][Cc][Pp][Tt] [Tt][Oo]:";
	public static final int RCPT_TO_BEGIN = 0;
	public static final int RCPT_TO_END = 8;
	public static final int FORWARD_PATH_BEGIN = 8;

	private ForwardPath forwardPath;

	/*Every smtp.token class checks the validity of the argument
	 * in the constructor.  If the argument is not valid an exception
	 * is thrown.  Therefore if the constructor finishes and the object
	 * is instantiated the argument must be a valid token of that type.
	 */
	public RcptToCommand(String string) throws InvalidSMTPException, InvalidCommandException{
		
		try{
			//I do not use the StringTokenizer class because it is deprecated
			//and the documentation says that the split() function or regexes
			//should be used instead.

			//if the first ten characters are not some case
			//insensitive form of 'mail from:' then an exception is thrown
			if(!string.substring(RCPT_TO_BEGIN, RCPT_TO_END).matches(RCPT_TO_COMMAND))
				throw new InvalidCommandException(ERROR_500);;

			String newLine = string.substring(FORWARD_PATH_BEGIN);

			forwardPath = new ForwardPath(newLine);

		}catch(StringIndexOutOfBoundsException e){
			//If input is too short then an exception is thrown
			throw new InvalidCommandException(ERROR_500);
		}

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public ForwardPath getForwardPath(){
		return forwardPath;
	}
	
}
