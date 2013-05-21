/*
 * Author: William Hipschman
 */




/*
 * This class parses smtp Element commands
 */
public class Element extends StringToken{

	public static final String ERROR = "element";

	private Name name;
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid Element token
	 */
	public Element(String string) throws InvalidSMTPException{

		name = new Name(string);

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public Name getName(){
		return name;
	}
}
