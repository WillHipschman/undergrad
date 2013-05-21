//this class is named after the grammar
public class A extends CharToken{
	
	public static final String A_REGEX = "[a-zA-Z]";
	public static final String ERROR = "a";
	
	public A(char c) throws InvalidSMTPException{
		
		if (!Character.toString(c).matches(A_REGEX))
			throw new InvalidSMTPException(ERROR_501);
		super.token = c;
	}
}
