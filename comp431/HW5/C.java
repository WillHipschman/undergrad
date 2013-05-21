/*
 * Author: William Hipschman
 */




//this class is named after the grammar and parses C commands
public class C extends CharToken{

	public static final String ERROR = "c";
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid C token
	 */
	public C(char c) throws InvalidSMTPException{

		if (Special.SPECIAL.indexOf(c) != -1)
			throw new InvalidSMTPException(ERROR_501);
		//this section is not reached if an exception is thrown before it
		token = c;
	}
}
