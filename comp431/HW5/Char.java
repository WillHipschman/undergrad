/*
 * Author: William Hipschman
 */




/*
 * This class parses char tokens
 */
public class Char extends CharToken{
	
	public static final String ERROR = "char";

	private C c;
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid char token
	 */
	public Char(char character) throws InvalidSMTPException{

		c = new C(character);
		
		//this section is not reached if an exception is thrown before it
		token = character;
	}
	public C getC(){
		return c;
	}
}
