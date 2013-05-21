public class DataCommand extends StringToken{

	public static final String DATA_COMMAND = "DATA";
	public static final String DATA_TERMINATOR = ".";
	
	public DataCommand(String string) throws InvalidCommandException{
		
		if(!string.matches(DATA_COMMAND))
			throw new InvalidCommandException(ERROR_500);
		token = string;
	}
}
