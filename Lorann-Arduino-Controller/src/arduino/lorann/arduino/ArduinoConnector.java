package arduino.lorann.arduino;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

public class ArduinoConnector {
	private static final int ID = 6500;

	private static Enumeration portList;
	private static CommPortIdentifier portId;
	private static SerialPort serialPort;
	private static OutputStream outputStream;

	private static StringBuilder stringToBuild;

	private static int calcCheckSum(String message) {
		int checkSum = 0;
		for (int i = 0; i < message.length(); i++) {
			checkSum = checkSum + (((int) message.charAt(i)) * (i + 1));
		}
		return checkSum;
	}

	public static void sendToArduino(String messageString) {
		stringToBuild = new StringBuilder();

		stringToBuild.append(ID);
		stringToBuild.append("|");
		stringToBuild.append(messageString);
		stringToBuild.append("|");
		stringToBuild.append(calcCheckSum(messageString));

		portList = CommPortIdentifier.getPortIdentifiers();

		while (portList.hasMoreElements()) {

			portId = (CommPortIdentifier) portList.nextElement();
			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {

				if (portId.getName().equals("COM7")) {

					try {
						serialPort = (SerialPort) portId.open("SimpleWriteApp", 2000);
						Thread.sleep(1550);
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
						outputStream.write(stringToBuild.toString().getBytes());
						System.out.println("Instruction envoyée :" + messageString);

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
