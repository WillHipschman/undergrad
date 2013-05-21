


public class ForwardPath extends StringToken{

	public static final String ERROR = "reverse-path";

	Path path;
	
	public ForwardPath(String string) throws InvalidSMTPException{

		path = new Path(string);

		//this section is not reached if an exception is thrown before it
		token = path.getToken();
	}
	public Path getPath(){
		return path;
	}
}
