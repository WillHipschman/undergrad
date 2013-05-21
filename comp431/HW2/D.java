//This class is named after the grammar
public class D extends CharToken{
	
	public static final String D_REGEX = "[1234567890]";
	public static final String ERROR = "d";
	
	public D(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(D_REGEX))
			throw new InvalidSMTPException(ERROR_501);
		super.token = c;
	}
}
