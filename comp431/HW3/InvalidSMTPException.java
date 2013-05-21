/*
 * Author: William Hipschman
 */



/*
 * This exception is thrown when the parser finds a malformed
 * smtp command
 */

public class InvalidSMTPException extends Exception{

	private static final long serialVersionUID = 6266368680480940277L;

	public InvalidSMTPException(String err){
		super(err);
	}
}
