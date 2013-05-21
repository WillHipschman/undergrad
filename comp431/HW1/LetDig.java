/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class LetDig extends CharToken{

	public static final String ERROR = "let-dig";

	private CharToken charToken;

	public LetDig(char c) throws InvalidSMTPException{

		//the character can either be alphabetic or numeric
		try{

			charToken = new A(c);

		}catch(InvalidSMTPException e){

			charToken = new D(c);
		}
		finally{

			//this section is not reached if an exception is thrown in the catch block
			//token is a member of the super class
			token = c;
		}
	}
	public CharToken getSubToken(){
		
		return charToken;
	}
}
