/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class Path extends StringToken{

	public static final String PATH = "[<>]";
	public static final String ERROR = "path";

	private MailBox mailbox;

	public Path(String string) throws InvalidSMTPException{

		//ignore spaces
		string = string.trim();
		int firstIndex = string.indexOf("<");
		int secondIndex = string.indexOf(">");

		//If there are no '<' or '>'
		if(firstIndex < 0 || secondIndex < 0)
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		//if '<' is not the first character
		if(firstIndex != 0)
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		//if '>' is not the last character
		if(secondIndex != string.length() - 1)
			throw new InvalidSMTPException(Token.ERROR + ERROR);

		String[] strings = string.split(PATH);

		String path = string.substring(firstIndex, secondIndex + 1);

		String newString = "";
		if(strings.length != 0)
			newString = strings[1];

		mailbox = new MailBox(newString);

		//this section is not reached if an exception is thrown before it
		token = path;
	}
	public MailBox getMailBox(){
		return mailbox;
	}
}
