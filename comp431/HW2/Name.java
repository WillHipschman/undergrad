

public class Name extends StringToken{
	
	public static final String NAME_REGEX = "[a-zA-Z]";
	public static final String ERROR = "name";

	private LetDigStr letDigStr;

	public Name(String string) throws InvalidSMTPException{

		//the grammer says a name must contain an a to z character AND and let-dig-str
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
