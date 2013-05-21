/*
 * Author: William Hipschman
 */




//this class is named after the grammar and parses A tokens
public class A extends CharToken{
	
	public static final String A_REGEX = "[a-zA-Z]";
	public static final String ERROR = "a";
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid A token
	 */
	public A(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(A_REGEX))
			throw new InvalidSMTPException(ERROR_501);
		super.token = c;
	}
}
