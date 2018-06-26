package arduino.lorann.view;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Graphics;

import javax.swing.JPanel;

public class CommandPanel extends JPanel {

	/**
	 * ID
	 */
	private static final long serialVersionUID = 8795350196694066878L;

	public CommandPanel() {
		this.setBackground(Color.BLUE);
		this.setCursor(new Cursor(Cursor.HAND_CURSOR));
		this.repaint();
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawOval(0, 0, 2 * 30, 2 * 30);
	}

}
