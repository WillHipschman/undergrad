/*
 * Author: William Hipschman
 */




/*
 * This class is extended by MailToLine and MailFromLine.
 * The logic is the same for both classes, the only differences are
 * in the regex and the indices used for regex matching
 */
public abstract class MailLine extends StringToken{
	
	private MailBox mailBox;
	
	/*Every smtp.token class checks the validity of the argument
	 * in the constructor.  If the argument is not valid an exception
	 * is thrown.  Therefore if the constructor finishes and the object
	 * is instantiated the argument must be a valid token of that type.
	 */
	public MailLine(String string, String regex, int index1, int index2) throws InvalidMailFileException{

		try{
			if(!string.substring(index1, index2).matches(regex))
				throw new InvalidMailFileException(MAIL_FILE_ERROR);

			String newLine = string.substring(index2 + 2, string.length() - 1).trim();

			mailBox = new MailBox(newLine);

		}catch(StringIndexOutOfBoundsException e){
			//If input is too short then an exception is thrown
			throw new InvalidMailFileException(MAIL_FILE_ERROR);
		} catch (InvalidSMTPException e) {
			/*
			 * If the file does not contain a valid reverse path
			 * then it is formatted incorrectly and an exception is
			 * thrown.
			 */
			throw new InvalidMailFileException(MAIL_FILE_ERROR);
		}

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public MailBox getMailBox(){
		return mailBox;
	}
}
