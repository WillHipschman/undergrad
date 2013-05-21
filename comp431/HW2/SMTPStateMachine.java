

public class SMTPStateMachine {

	public static final int NO_COMMAND = -1;
	public static final int MAIL_FROM_COMMAND = 0;
	public static final int RCPT_TO_COMMAND = 1;
	public static final int DATA_COMMAND = 2;

	public static final String SUCCESS = "250 OK";
	public static final String DATA_MESSAGE = "354 Start mail input; end with <CRLF>.<CRLF>";


	private int lastSeenTokenType = -1;

	/*
	 * The assignment does not specify what to do if a valid command is
	 * received out of sequence.  This state machine continues waiting
	 * for the command that was expected before the command that caused
	 * the 503 error (See email.smtp.tokens.Token.ERROR_503 and 
	 * email.exceptions.BadCommandException)
	 * */
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

		//never reached because every token passed into the
		//state machine is one of the three token types above.
		return false;
	}
	public String getReturnMessage(){
		
		//this method is only called after a token has
		//successfully been instantiated.  The only time that
		//a token is instantiated and the last seen token is
		// NO_COMMAND is after a DATA command.
		if(lastSeenTokenType == NO_COMMAND)
			return DATA_MESSAGE;
		return SUCCESS;
	}


}
