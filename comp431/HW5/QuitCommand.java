/*
 * Author: William Hipschman
 */




/*
 * This class parses the smtp quit command
 */
public class QuitCommand extends StringToken{

	public static final String QUIT_COMMAND = "QUIT";
	
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid Quit token
	 */
	public QuitCommand(String string) throws InvalidCommandException{
		
		if(!string.matches(QUIT_COMMAND))
			throw new InvalidCommandException(ERROR_500);
		token = string;
	}
}
