/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

//this class is named after the grammar
public class A extends CharToken{
	
	public static final String A_REGEX = "[a-zA-Z]";
	public static final String ERROR = "a";
	
	public A(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(A_REGEX))
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		super.token = c;
	}
}
