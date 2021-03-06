/*
 * Author: William Hipschman
 */




/*
 * This class parses the smtp Path command
 */
public class Path extends StringToken{

	public static final String LEFT_PATH = "<";
	public static final String RIGHT_PATH = ">";
	public static final String PATH = "[<>]";
	public static final String ERROR = "path";

	private MailBox mailbox;

	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid Path token
	 */
	public Path(String string) throws InvalidSMTPException{

		//ignore spaces
		string = string.trim();
		int firstIndex = string.indexOf("<");
		int secondIndex = string.indexOf(">");

		//If there are no '<' or '>'
		if(firstIndex < 0 || secondIndex < 0)
			throw new InvalidSMTPException(ERROR_501);
		//if '<' is not the first character
		if(firstIndex != 0)
			throw new InvalidSMTPException(ERROR_501);
		//if '>' is not the last character
		if(secondIndex != string.length() - 1)
			throw new InvalidSMTPException(ERROR_501);

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
