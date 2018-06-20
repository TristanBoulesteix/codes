package Arduino;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

public class ArduinoConnector {
	static Enumeration portList;
	static CommPortIdentifier portId;
	static SerialPort serialPort;
	static OutputStream outputStream;

	public static void sendToArduino(String messageString) {
		portList = CommPortIdentifier.getPortIdentifiers();

		while (portList.hasMoreElements()) {

			portId = (CommPortIdentifier) portList.nextElement();
			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {

				if (portId.getName().equals("COM3")) {

					try {
						serialPort = (SerialPort) portId.open("SimpleWriteApp", 2000);
						Thread.sleep(4000);
					} catch (PortInUseException | InterruptedException e) {
						System.out.println("err");
					}
					try {
						outputStream = serialPort.getOutputStream();
					} catch (IOException e) {
						System.out.println("err1");
					}
					try {
						serialPort.setSerialPortParams(9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
								SerialPort.PARITY_NONE);
					} catch (UnsupportedCommOperationException e) {
						System.out.println("err2");
					}
					try {
						outputStream.write(messageString.getBytes());
						System.out.println(messageString);

						outputStream.close();
						serialPort.close();

					} catch (IOException e) {
						System.out.println("err3");
					}
				}
			}
		}
	}
}
