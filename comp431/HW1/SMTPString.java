/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

import java.util.ArrayList;
import java.util.List;

public class SMTPString extends StringToken{
	
	public static final String ERROR = "string";

	private List<Char> chars = new ArrayList<Char>();

	public SMTPString(String string) throws InvalidSMTPException{
		
		if (string.isEmpty())
			throw new InvalidSMTPException(Token.ERROR + ERROR);
		for(char c : string.toCharArray())
			chars.add(new Char(c));
		
		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public List<Char> getChar(){
		return chars;
	}
}
