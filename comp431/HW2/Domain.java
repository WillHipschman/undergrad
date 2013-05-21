

import java.util.ArrayList;
import java.util.List;


public class Domain extends StringToken{

	//this is the octal value for  a period
	//It is used because "." is a symbol for any character
	//with java regexes
	public static final String DOMAIN_DELIMITER = "\\0056";
	public static final String ERROR = "domain";

	private List<Element> elements = new ArrayList<Element>();

	public Domain(String string) throws InvalidSMTPException{

		String[] strings = string.split(DOMAIN_DELIMITER);

		//If the domain is empty
		if(strings.length == 0)
			throw new InvalidSMTPException(ERROR_501);

		for(String s: strings)
			elements.add(new Element(s));

		//this section is not reached if an exception is thrown before it
		token = string;
	}
	public List<Element> getElements(){
		
		return elements;
	}	
}
