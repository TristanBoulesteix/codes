package arduino.lorann.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Shape;
import java.awt.event.ActionEvent;
import java.awt.geom.Ellipse2D;

import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;

import arduino.lorann.arduino.ArduinoConnector;

public class ControlButton extends JButton {
	/**
	* 
	*/
	private static final long serialVersionUID = 6207959287726398197L;

	private final Dimension size = new Dimension(300, 300);

	private Shape shape;
	private String name;
	private JFrame frame;
	private String stringToSend;

	public ControlButton(String name, JFrame frame, String stringToSend) {
		super(name);

		this.name = name;
		this.frame = frame;
		this.stringToSend = stringToSend;

		this.setBackground(Color.LIGHT_GRAY);
		this.setFont(new Font("Arial", Font.PLAIN, 55));
		this.setFocusable(false);
		this.setPreferredSize(size);
		this.setAction(new ButtonAction());

		this.setContentAreaFilled(false);
	}

	protected void paintComponent(Graphics g) {
		if (getModel().isArmed()) {
			g.setColor(Color.BLUE);
		} else {
			g.setColor(getBackground());
		}
		g.fillOval(0, 0, getSize().width - 1, getSize().height - 1);

		super.paintComponent(g);
	}

	protected void paintBorder(Graphics g) {
		g.setColor(Color.DARK_GRAY);
		g.drawOval(0, 0, getSize().width - 1, getSize().height - 1);
	}

	public boolean contains(int x, int y) {
		// If the button has changed size, make a new shape object.
		if (shape == null || !shape.getBounds().equals(getBounds())) {
			shape = new Ellipse2D.Float(0, 0, getWidth(), getHeight());
		}
		return shape.contains(x, y);
	}

	private class ButtonAction extends AbstractAction {
		/**
		 * 
		 */
		private static final long serialVersionUID = -4960274684361182377L;

		public ButtonAction() {
			putValue(NAME, name);
		}

		public void actionPerformed(ActionEvent e) {
			ArduinoConnector.sendToArduino(stringToSend);
			frame.setFocusable(true);
		}
	}
}
