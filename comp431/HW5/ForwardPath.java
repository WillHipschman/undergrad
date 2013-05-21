/*
 * Author: William Hipschman
 */




/*
 * This path parses forward paths
 */
public class ForwardPath extends StringToken{

	public static final String ERROR = "reverse-path";

	Path path;
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid forward path token
	 */
	public ForwardPath(String string) throws InvalidSMTPException{

		path = new Path(string);

		//this section is not reached if an exception is thrown before it
		token = path.getToken();
	}
	public Path getPath(){
		return path;
	}
}
