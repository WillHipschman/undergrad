/*
 * Author: William Hipschman
 */




/*
 * This class parses smtp DATA commands
 */
public class DataCommand extends StringToken{

	public static final String DATA_COMMAND = "DATA";
	public static final String DATA_TERMINATOR = ".";
	
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid data token
	 */
	public DataCommand(String string) throws InvalidCommandException{
		
		if(!string.matches(DATA_COMMAND))
			throw new InvalidCommandException(ERROR_500);
		token = string;
	}
}
