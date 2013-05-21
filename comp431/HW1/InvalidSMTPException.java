/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class InvalidSMTPException extends Exception{

	private static final long serialVersionUID = 6266368680480940277L;

	public InvalidSMTPException(String err){
		super(err);
	}
}
