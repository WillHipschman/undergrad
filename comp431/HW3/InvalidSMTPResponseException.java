/*
 * Author: William Hipschman
 */



/*
 * This exception is thrown if the numeric smtp responses are
 * not 250 or 354
 */
public class InvalidSMTPResponseException extends Exception{
	
	private static final long serialVersionUID = 3381888273104771707L;

	public InvalidSMTPResponseException(String err){
		super(err);
	}
}
