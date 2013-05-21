/*
 * Author: William Hipschman
 */




//This class is named after the grammar and parses D tokens
public class D extends CharToken{
	
	public static final String D_REGEX = "[1234567890]";
	public static final String ERROR = "d";
	
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid D token
	 */
	public D(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(D_REGEX))
			throw new InvalidSMTPException(ERROR_501);
		super.token = c;
	}
}
