/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class D extends CharToken{
	
	public static final String D_REGEX = "[1234567890]";
	public static final String ERROR = "d";
	
	public D(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(D_REGEX))
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		super.token = c;
	}
}
