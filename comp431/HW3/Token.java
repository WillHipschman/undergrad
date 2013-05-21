/*
 * Author: William Hipschman
 */



/*
 * Highest level token interface. All tokens descend from this class
 */
public interface Token {

	public static final String ERROR_500 = "500 Syntax error: command unrecognized";
	public static final String ERROR_501 = "501 Syntax error in parameters or arguments";
	public static final String ERROR_503 = "503 Bad sequence of commands";
	public static final String MAIL_FILE_ERROR = "File incorrectly formatted";
	public static final String OK_250 = "250";
	public static final String OK_354 = "354";	
	public static final String SMTP_RESPONSE_ERROR = "Invalid SMTP Response";	
}


