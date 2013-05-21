/*
 * Author: William Hipschman
 */




/*
 * This class parses the smtp name command
 */
public class Name extends StringToken{
	
	public static final String NAME_REGEX = "[a-zA-Z]";
	public static final String ERROR = "name";

	private LetDigStr letDigStr;

	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid name token
	 */
	public Name(String string) throws InvalidSMTPException{

		//the grammar says a name must contain an a to z character AND a let-dig-str
		if (string.length() < 2)
			throw new InvalidSMTPException(ERROR_501);
		
		//the first character must be alphabetic
		char first = string.charAt(0);

		if(!Character.toString(first).matches(NAME_REGEX))
			throw new InvalidSMTPException(ERROR_501);

		
		String newString = string.substring(1);
		letDigStr = new LetDigStr(newString);
			
		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public LetDigStr getLetDigStr(){
		return letDigStr;
	}
}
