/*
 * Author: William Hipschman
 */



/*
 * This class is the base class for all tokens that are
 * represented by a character
 */
public abstract class CharToken implements Token{
	
	protected char token;
	
	public char getToken() {

		return token;
	}
}
