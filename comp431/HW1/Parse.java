/*
 * Author: William Hipschman
 * Date: 1-23-2011
 * PID: 714228116
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Parse {

	public static void main(String[] args){

		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);


		/*
		 * This program creates objects out of every part
		 * of the smtp command.  It was built this way to make 
		 * every portion of the command extendable, able to be
		 * manipulated and used separate from the other portions.
		 * Each object contains objects that represent the pieces
		 * in the grammer below it.  For example the MailFromCommand
		 * contains a ReversePath which contains a Path which conains
		 * a MailBox which contains a LocalPart and a Domain...etc.
		 */
		try {
			String line = br.readLine();
			while(line != null){

				try {
					//If the command is successfully instantiated it is valid
					MailFromCommand c = new MailFromCommand(line);
					System.out.println(c.getToken());
					System.out.println("Sender ok");
					line = br.readLine();
				} catch (InvalidSMTPException e) {
					System.out.println(line);
					System.out.println(e.getMessage());
					line = br.readLine();
				}
			} 
		} catch (IOException e2) {
			//exit without printing debugging/status info
			System.exit(-1);
		}
	}
}
