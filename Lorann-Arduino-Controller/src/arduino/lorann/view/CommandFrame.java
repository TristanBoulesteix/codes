package arduino.lorann.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;

import arduino.lorann.arduino.ArduinoConnector;

public class CommandFrame extends JFrame implements KeyListener {

	/**
	 * ID
	 */
	private static final long serialVersionUID = -5853832954211297232L;

	private static final Dimension panelDimension = new Dimension(200, 200);

	private CommandPanel panelLeft;
	private CommandPanel panelUp;
	private CommandPanel panelDown;
	private CommandPanel panelRight;

	public CommandFrame() {
		this.setTitle("Commands");
		this.setResizable(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(new BorderLayout());
		this.setPreferredSize(new Dimension(1200, 1000));
		this.initComponents();
		this.pack();
		this.setLocationRelativeTo(null);
		this.setFocusable(true);
	}

	private void initComponents() {
		this.panelLeft = new CommandPanel();
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(panelLeft, BorderLayout.WEST);

		this.panelRight = new CommandPanel();
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(panelRight, BorderLayout.EAST);

		this.panelUp = new CommandPanel();
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(panelUp, BorderLayout.NORTH);

		this.panelDown = new CommandPanel();
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(panelDown, BorderLayout.SOUTH);
	}

	@Override
	public void keyTyped(KeyEvent e) {

	}

	@Override
	public void keyPressed(KeyEvent e) {
		int keyDetected = e.getKeyCode();

		switch (keyDetected) {
		case KeyEvent.VK_UP:
			ArduinoConnector.sendToArduino("A");
			break;

		case KeyEvent.VK_LEFT:
			ArduinoConnector.sendToArduino("L");
			break;

		case KeyEvent.VK_RIGHT:
			ArduinoConnector.sendToArduino("R");
			break;

		case KeyEvent.VK_DOWN:
			ArduinoConnector.sendToArduino("B");
			break;

		default:
			break;
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {

	}

}
