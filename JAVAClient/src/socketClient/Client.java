package socketClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
	public static void main(String[] args) throws IOException {

		String test = "{ \"class\" : \"vector\", \"size\" : \"3\", \"type\" : \"float\", \"value\" : { \"0\" : \"7.000000\", \"1\" : \"2.000000\", \"2\" : \"1.000000\"}}";

//		String serverHostname = InetAddress.getByName("localhost").toString();
		String serverHostname = "localhost";
		Socket echoSocket = null;
		PrintWriter out = null;
		BufferedReader in = null;

		try {
			echoSocket = new Socket(serverHostname, 55777);
			out = new PrintWriter(echoSocket.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(
					echoSocket.getInputStream()));
		} catch (UnknownHostException e) {
			System.err.println("Don't know about host: " + serverHostname);
			System.exit(1);
		} catch (IOException e) {
			System.err.println("Couldn't get I/O for " + "the connection to: "
					+ serverHostname);
			System.exit(1);
		}

		BufferedReader stdIn = new BufferedReader(new InputStreamReader(
				System.in));
		String userInput;

		out.println(test);
//		System.out.println("echo: " + in.read());
		String s = " ";
		String t = " ";
		while (s!=null) {
		    try {
		        s = in.readLine();
		    }catch(NullPointerException e) {
		        in.close();
		        break;
		    }
		    if (s!=null)
		    	t += s;
		}
		System.out.println(t);
		out.close();
		in.close();
		stdIn.close();
		echoSocket.close();
	}
}
