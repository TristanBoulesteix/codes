package Dijkstra;

import java.util.ArrayList;

public class OrderSender {
	private final static int INFINITE = 99999999;

	private ArrayList<Integer> finalPath;
	private Direction currentDirection;
	private String finalOrder = "";

	public String getFinalOrder() {
		return finalOrder;
	}

	private int map[][] = { { 13, 14, INFINITE, INFINITE, INFINITE, 15 },
			{ INFINITE, 11, INFINITE, INFINITE, 12, INFINITE }, { 8, INFINITE, INFINITE, INFINITE, 9, 10 },
			{ 5, 6, INFINITE, 7, INFINITE, INFINITE }, { 0, 1, INFINITE, 2, 3, 4 } };
	/*
	 * 
	 * { 0, 1, INFINITE, 2, 3, 4 }, { 5, 6, INFINITE, 7, INFINITE, INFINITE }, { 8,
	 * INFINITE, INFINITE, INFINITE, 9, 10 }, { INFINITE, 11, INFINITE, INFINITE,
	 * 12, INFINITE }, { 13, 14, INFINITE, INFINITE, INFINITE, 15 }
	 */

	public OrderSender(ArrayList<Integer> finalPath, Direction currentDirection) {
		this.finalPath = finalPath;
		this.currentDirection = currentDirection;

		this.generateOrderString();
	}

	private void generateOrderString() {
		int origin = finalPath.get(finalPath.size() - 1);
		finalPath.remove(finalPath.size() - 1);

		for (int j = finalPath.size() - 1; j > 0; j--) {
			finalOrder += compareCoordinate(origin, finalPath.get(j));
			origin = finalPath.get(j);
		}
	}

	private Order compareCoordinate(int origin, int destination) {
		int comparedX = getX(destination) - getX(origin);
		Order orderToSend = Order.HALF_TURN;

		if (comparedX > 0) {
			switch (currentDirection) {
			case LEFT:
				orderToSend = Order.HALF_TURN;
				break;

			case UP:
				orderToSend = Order.RIGHT;
				break;

			case RIGHT:
				orderToSend = Order.STRAIGHT;
				break;

			case DOWN:
				orderToSend = Order.LEFT;
				break;

			default:
				break;
			}

			this.currentDirection = Direction.RIGHT;

		} else if (comparedX < 0) {
			switch (currentDirection) {
			case LEFT:
				orderToSend = Order.STRAIGHT;
				break;

			case UP:
				orderToSend = Order.LEFT;
				break;

			case RIGHT:
				orderToSend = Order.HALF_TURN;
				break;

			case DOWN:
				orderToSend = Order.RIGHT;
				break;

			default:
				break;
			}

			currentDirection = Direction.LEFT;

		} else {
			int yCompared = getY(destination) - getY(origin);

			if (yCompared > 0) {
				switch (currentDirection) {
				case LEFT:
					orderToSend = Order.RIGHT;
					break;

				case UP:
					orderToSend = Order.STRAIGHT;
					break;

				case RIGHT:
					orderToSend = Order.LEFT;
					break;

				case DOWN:
					orderToSend = Order.HALF_TURN;
					break;

				default:
					break;
				}

				this.currentDirection = Direction.UP;

			} else if (yCompared < 0) {
				switch (currentDirection) {
				case LEFT:
					orderToSend = Order.LEFT;
					break;

				case UP:
					orderToSend = Order.HALF_TURN;
					break;

				case RIGHT:
					orderToSend = Order.RIGHT;

				case DOWN:
					orderToSend = Order.STRAIGHT;
					break;

				default:
					break;
				}

				this.currentDirection = Direction.DOWN;
			}
		}

		return orderToSend;
	}

	@SuppressWarnings("null")
	private int getX(int n) {
		for (int i = 0; i < map.length; i++) {
			for (int j = 0; j < map[i].length; j++) {
				if (map[i][j] == n) {
					return j;
				}
			}
		}

		return (Integer) null;
	}

	@SuppressWarnings("null")
	private int getY(int n) {
		for (int i = 0; i < map.length; i++) {
			for (int j = 0; j < map[i].length; j++) {
				if (map[i][j] == n) {
					return i;
				}
			}
		}

		return (Integer) null;
	}

	private enum Order {
		STRAIGHT("S"), RIGHT("R"), LEFT("L"), HALF_TURN("H");

		String orderCharacter;

		private Order(String orderCharacter) {
			this.orderCharacter = orderCharacter;
		}

		@Override
		public String toString() {
			return orderCharacter;
		}
	}
}
