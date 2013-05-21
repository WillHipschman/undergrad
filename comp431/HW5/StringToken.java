/*
 * Author: William Hipschman
 */



/*
 * This class is the base for all tokens that are represented by a string as
 * opposed to a character
 */
public abstract class StringToken implements Token{
	
	protected String token;
	
	public String getToken() {

		return token;
	}
}
