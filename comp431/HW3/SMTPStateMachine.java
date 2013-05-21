/*
 * Author: William Hipschman
 */




/*
 * This class is responsible for maintaining the state of the client.
 * A MailFromCommand must be seen first, followed by one or more
 * RcptToCommands, followed by a DataCommand.  If commands are received
 * out of order than a BadCommandSequenceException is thrown.
 *	
 * The assignment does not specify what to do if a valid command is
 * received out of sequence.  This state machine continues waiting
 * for the command that was expected before the command that caused
 * the 503 error 
 */
public class SMTPStateMachine {

	public static final int NO_COMMAND = -1;
	public static final int MAIL_FROM_COMMAND = 0;
	public static final int RCPT_TO_COMMAND = 1;
	public static final int DATA_COMMAND = 2;

	public static final String SUCCESS = "250 OK";
	public static final String DATA_MESSAGE = "354 Start mail input; end with <CRLF>.<CRLF>";

	private int lastSeenTokenType = -1;

	/*
	 * This method tests to make sure a command is valid.
	 * 
	 * Parameters: The token to test for validity
	 * 
	 * Precondition: lastSeenTokenType corresponds to the type of the last
	 *     token that this method was called on.
	 *     
	 * Postcondition: lastSeenTokenType corresponds to the type of the token
	 *     passed in as a parameter if the token is valid for the state machine
	 *     otherwise an exception is thrown and lastSeenTokenType is unchanged.
	 */
	public boolean validToken(Token token) throws BadCommandSequenceException{

		if(token instanceof MailFromCommand)
			switch(lastSeenTokenType){
			case NO_COMMAND:
				lastSeenTokenType = MAIL_FROM_COMMAND;
				return true;
				//no break is used because the return ends the method
			case MAIL_FROM_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			case RCPT_TO_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			case DATA_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			}
		if(token instanceof RcptToCommand)
			switch(lastSeenTokenType){
			case NO_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			case MAIL_FROM_COMMAND:
				lastSeenTokenType = RCPT_TO_COMMAND;
				return true;
				//no break is used because the exception ends the method
			case RCPT_TO_COMMAND:
				lastSeenTokenType = RCPT_TO_COMMAND;
				return true;
				//no break is used because the return ends the method
			case DATA_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the return ends the method
			}
		if(token instanceof DataCommand)
			switch(lastSeenTokenType){
			case NO_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			case MAIL_FROM_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			case RCPT_TO_COMMAND:
				lastSeenTokenType = NO_COMMAND;
				return true;
				//no break is used because the return ends the method
			case DATA_COMMAND:
				throw new BadCommandSequenceException(Token.ERROR_503);
				//no break is used because the exception ends the method
			}

		/*
		 * This return is never reached because every token passed into the
		 * state machine is one of the three token types above.
		 */
		return false;
	}

	/*
	 * This method determines the smtp response command
	 * that needs to be given based on the state of the
	 * state machine
	 */
	public String getReturnMessage(){

		/* This method is only called after a token has
		 * successfully been instantiated.  The only time that
		 * a token is instantiated and the last seen token is
		 * NO_COMMAND is after a DATA command.
		 */
		if(lastSeenTokenType == NO_COMMAND)
			return DATA_MESSAGE;
		return SUCCESS;
	}
}
