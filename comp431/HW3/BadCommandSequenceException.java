/*
 * Author: William Hipschman
 */



/*
 * This exception is thrown when an smtp command is received
 * that is not the correct one given the state of the state machine.
 */

public class BadCommandSequenceException extends Exception{

	private static final long serialVersionUID = -2977766435212168762L;

	public BadCommandSequenceException(String err){
		super(err);
	}
}
