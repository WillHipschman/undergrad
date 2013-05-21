/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class Char extends CharToken{
	
	public static final String ERROR = "char";

	private C c;

	public Char(char character) throws InvalidSMTPException{

		c = new C(character);
		
		//this section is not reached if an exception is thrown before it
		token = character;
	}
	public C getC(){
		return c;
	}
}
