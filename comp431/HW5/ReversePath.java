/*
 * Author: William Hipschman
 */




/*
 * This class parses reverse paths
 */
public class ReversePath extends StringToken{

	public static final String ERROR = "reverse-path";

	Path path;
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid Reverse Path token
	 */
	public ReversePath(String string) throws InvalidSMTPException{

		path = new Path(string);

		//this section is not reached if an exception is thrown before it
		token = path.getToken();
	}
	public Path getPath(){
		return path;
	}
}
