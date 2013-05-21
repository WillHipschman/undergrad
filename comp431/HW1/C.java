/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

//this class is named after the grammar
public class C extends CharToken{

	public static final String ERROR = "c";

	public C(char c) throws InvalidSMTPException{

		if (Special.SPECIAL.indexOf(c) != -1)
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		//this section is not reached if an exception is thrown before it
		token = c;
	}
}
