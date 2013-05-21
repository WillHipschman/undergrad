/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class MailBox extends StringToken{

	public static final String MAILBOX_DELIMITER = "@";
	public static final String ERROR = "mailbox";

	private Domain domain;
	private LocalPart localPart;

	public MailBox(String string) throws InvalidSMTPException{

		String[] strings = string.split(MAILBOX_DELIMITER);

		//if the strng is empty
		if(strings.length == 0)
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		//if there is more than one '@' symbol
		if(strings.length > 2)
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		//if there is no '@' symbol
		if(strings[0].equals(string))
			throw new InvalidSMTPException(Token.ERROR + ERROR);

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
