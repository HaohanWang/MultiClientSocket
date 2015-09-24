package socketClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * @author haohanwang
 *
 */
public class Client {
	private String serverHostname;
	private int portnum;
	private Socket echoSocket = null;
	private PrintWriter out = null;
	private BufferedReader in = null;

	public Client(String serverHostname, int portnum) {
		this.serverHostname = serverHostname;
		this.portnum = portnum;
	}

	public void connect() {
		try {
			echoSocket = new Socket(serverHostname, portnum);
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
	}

	public void send_message(String message) {
		out.println(message);
	}

	public String get_message() {
		String s = " ";
		String t = "";
		while (s != null) {
			try {
				s = in.readLine();
			} catch (NullPointerException e) {
				try {
					in.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				break;
			} catch (IOException e) {
				e.printStackTrace();
			}
			if (s != null)
				t += s;
		}
		return t;
	}
}
