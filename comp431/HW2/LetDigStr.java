

import java.util.ArrayList;
import java.util.List;

public class LetDigStr extends StringToken{
	
	public static final String ERROR = "let-dig-str";

	private List<LetDig> letDigits = new ArrayList<LetDig>();

	public LetDigStr(String string) throws InvalidSMTPException{
		
		if (string.isEmpty())
			throw new InvalidSMTPException(ERROR_501);
		for(char c : string.toCharArray())
			letDigits.add(new LetDig(c));
		
		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public List<LetDig>  getLetDig(){
		return letDigits;
	}
}
