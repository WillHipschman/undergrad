/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

public class ReversePath extends StringToken{

	public static final String ERROR = "reverse-path";

	Path path;
	
	public ReversePath(String string) throws InvalidSMTPException{

		path = new Path(string);

		//this section is not reached if an exception is thrown before it
		token = path.getToken();
	}
	public Path getPath(){
		return path;
	}
}
