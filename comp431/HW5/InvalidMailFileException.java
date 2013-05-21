/*
 * Author: William Hipschman
 */



/*
 * This exception is thrown if the file format is not correct
 * when being read in.
 */
public class InvalidMailFileException extends Exception{
	
	private static final long serialVersionUID = -2411782825644533328L;

	public InvalidMailFileException(String err){
		super(err);
	}
}
