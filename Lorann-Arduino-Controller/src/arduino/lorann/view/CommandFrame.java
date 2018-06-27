package arduino.lorann.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;

public class CommandFrame extends JFrame implements KeyListener {

	/**
	 * ID
	 */
	private static final long serialVersionUID = -5853832954211297232L;

	private static final Dimension panelDimension = new Dimension(1000, 1000);

	private ControlButton buttonLeft;
	private ControlButton buttonUp;
	private ControlButton buttonDown;
	private ControlButton buttonRight;

	public CommandFrame() {
		this.setTitle("Commands");
		this.setResizable(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(new BorderLayout());
		this.setPreferredSize(new Dimension(1200, 1000));
		this.setBackground(Color.CYAN);
		this.initComponents();
		this.pack();
		this.setLocationRelativeTo(null);
		this.setFocusable(true);
		this.addKeyListener(this);
	}

	private void initComponents() {
		this.buttonLeft = new ControlButton("LEFT", this, "L");
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(buttonLeft, BorderLayout.WEST);

		this.buttonRight = new ControlButton("RIGHT", this, "R");
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(buttonRight, BorderLayout.EAST);

		this.buttonUp = new ControlButton("STRAIGHT", this, "S");
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(buttonUp, BorderLayout.NORTH);

		this.buttonDown = new ControlButton("BACK", this, "H");
		this.setPreferredSize(panelDimension);
		this.getContentPane().add(buttonDown, BorderLayout.SOUTH);
	}

	@Override
	public void keyTyped(KeyEvent e) {

	}

	@Override
	public void keyPressed(KeyEvent e) {
		int keyDetected = e.getKeyCode();

		switch (keyDetected) {
		case KeyEvent.VK_UP:
			this.buttonUp.doClick();
			break;

		case KeyEvent.VK_LEFT:
			this.buttonLeft.doClick();
			break;

		case KeyEvent.VK_RIGHT:
			this.buttonRight.doClick();
			break;

		case KeyEvent.VK_DOWN:
			this.buttonDown.doClick();
			break;

		default:
			break;
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {

	}

}
