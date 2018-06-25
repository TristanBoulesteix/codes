package arduino.lorann.view;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class CommandPanel extends JPanel {

	/**
	 * ID
	 */
	private static final long serialVersionUID = 8795350196694066878L;

	public CommandPanel() {
		this.setBackground(Color.BLUE);
		this.repaint();
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		this.drawCircle(g, 30, 30, 20);
	}

	private void drawCircle(Graphics cg, int xCenter, int yCenter, int r) {
		cg.drawOval(xCenter - r, yCenter - r, 2 * r, 2 * r);
	}

}
