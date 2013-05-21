/*
 * Author: William Hipschman
 */



/*
 * This exception is thrown if a command is received
 * that is not recognized by ths smtp parser. 
 */

public class InvalidCommandException extends Exception{
	
	private static final long serialVersionUID = -7322788015955556665L;

	public InvalidCommandException(String err){
		super(err);
	}
}
