/*
 * Author: William Hipschman
 */




/*
 * This class parses the first line of a file
 * that contains a mail message
 */
public class MailToLine extends MailLine{
	
	public static final String MAIL_TO_LINE = "[Tt][Oo]:";
	public static final int REGEX_BEGIN = 0;
	public static final int REGEX_END = 3;
	
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid String token
	 */
	public MailToLine(String string) throws InvalidMailFileException{
		super(string, MAIL_TO_LINE, REGEX_BEGIN, REGEX_END);
	}
}
