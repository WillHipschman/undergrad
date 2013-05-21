/*
 * Author: William Hipschman
 */



/*
 * This class parses files that contain email messages
 */
public class MailFromLine extends MailLine{

	public static final String MAIL_FROM_LINE = "[Ff][Rr][Oo][Mm]:";
	public static final int REGEX_BEGIN = 0;
	public static final int REGEX_END = 5;
	
	/*
	 * The constructor only terminates and instantiates if the
	 * string parameter is a valid MailFromLine token
	 */
	public MailFromLine(String string) throws InvalidMailFileException{
		super(string, MAIL_FROM_LINE, REGEX_BEGIN, REGEX_END);
	}
}



