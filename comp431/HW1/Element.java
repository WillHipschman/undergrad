/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class Element extends StringToken{

	public static final String ERROR = "element";

	private Name name;

	public Element(String string) throws InvalidSMTPException{

		name = new Name(string);

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public Name getName(){
		return name;
	}
}
