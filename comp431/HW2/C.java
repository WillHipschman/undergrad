//this class is named after the grammar
public class C extends CharToken{

	public static final String ERROR = "c";

	public C(char c) throws InvalidSMTPException{

		if (Special.SPECIAL.indexOf(c) != -1)
			throw new InvalidSMTPException(ERROR_501);
		//this section is not reached if an exception is thrown before it
		token = c;
	}
}
