/*
 * Author: William Hipschman
 */




/*
 * This class parses MailBox commands
 */
public class MailBox extends StringToken{

	public static final String MAILBOX_DELIMITER = "@";
	public static final String ERROR = "mailbox";

	private Domain domain;
	private LocalPart localPart;

	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid mailbox token
	 */
	public MailBox(String string) throws InvalidSMTPException{

		String[] strings = string.split(MAILBOX_DELIMITER);

		//if the string is empty
		if(strings.length == 0)
			throw new InvalidSMTPException(ERROR_501);
		//if there is more than one '@' symbol
		if(strings.length > 2)
			throw new InvalidSMTPException(ERROR_501);
		//if there is no '@' symbol
		if(strings[0].equals(string))
			throw new InvalidSMTPException(ERROR_501);

		String s1 = strings[0];
		String s2 = "";

		//we need to make sure the domain is not empty
		if(strings.length == 2)
			s2 = strings[1];

		localPart = new LocalPart(s1);
		domain = new Domain(s2);

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public LocalPart getLocalPart(){
		return localPart;
	}
	public Domain getDomain(){
		return domain;
	}
}
