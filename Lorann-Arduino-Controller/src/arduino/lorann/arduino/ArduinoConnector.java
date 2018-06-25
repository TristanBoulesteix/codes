package arduino.lorann.arduino;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

public class ArduinoConnector {
	private static Enumeration portList;
	private static CommPortIdentifier portId;
	private static SerialPort serialPort;
	private static OutputStream outputStream;

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
						e.printStackTrace();
					}
					try {
						outputStream = serialPort.getOutputStream();
					} catch (IOException e) {
						e.printStackTrace();
					}
					try {
						serialPort.setSerialPortParams(9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
								SerialPort.PARITY_NONE);
					} catch (UnsupportedCommOperationException e) {
						e.printStackTrace();
					}
					try {
						outputStream.write(messageString.getBytes());

						outputStream.close();
						serialPort.close();

					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}
}