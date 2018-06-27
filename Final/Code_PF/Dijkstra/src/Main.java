import java.util.Scanner;

import Arduino.ArduinoConnector;
import Dijkstra.Dijkstra;
import Dijkstra.Direction;
import Dijkstra.Graphe;
import Dijkstra.OrderSender;

public class Main {
	public static void main(String[] args) {
		System.out.println("Enter the origin");

		Scanner scan = new Scanner(System.in);

		int origin = Integer.parseInt(scan.nextLine());

		System.out.println("Enter the destination");

		int destination = Integer.parseInt(scan.nextLine());

		int N = Graphe.ALPHA_NOTDEF;
		int[][] matDuree = { { N, 1, N, N, 1, N, N, N, N, N, N, N, N, N, N, N, N, N, N }, // 0
				{ 1, N, N, N, N, 1, N, N, N, N, N, N, N, N, N, N, N, N, N }, // 1
				{ N, N, N, 4, N, N, 1, N, N, N, N, N, N, N, N, N, N, N, N }, // 2
				{ N, N, 4, N, N, N, N, N, 1, N, N, N, N, N, N, N, N, N, N }, // 3
				{ 1, N, N, N, N, 1, N, N, N, N, N, N, N, N, N, N, N, N, N }, // 4
				{ N, 1, N, N, 1, N, 1, N, N, N, N, N, N, N, N, N, N, N, N }, // 5
				{ N, N, 1, N, N, 1, N, 2, N, N, 1, N, N, N, N, N, N, N, N }, // 6
				{ N, N, N, N, N, N, 2, N, 2, N, N, N, 1, N, N, N, N, N, N }, // 7
				{ N, N, N, 1, N, N, N, 2, N, N, N, N, N, N, N, N, N, N, 4 }, // 8
				{ N, N, N, N, N, N, N, N, N, N, 2, N, N, N, N, N, N, N, N }, // 9
				{ N, N, N, N, N, N, 1, N, N, 2, N, N, N, N, N, N, N, N, N }, // 10
				{ N, N, N, N, N, N, N, N, N, N, N, N, 1, N, 2, N, N, N, N }, // 11
				{ N, N, N, N, N, N, N, 1, N, N, N, 1, N, 1, N, N, N, N, N }, // 12
				{ N, N, N, N, N, N, N, N, N, N, N, N, 1, N, N, N, 2, N, N }, // 13
				{ N, N, N, N, N, N, N, N, N, N, N, 2, N, N, N, 1, N, N, N }, // 14
				{ N, N, N, N, N, N, N, N, N, N, N, N, N, N, 1, N, 1, 1, N }, // 15
				{ N, N, N, N, N, N, N, N, N, N, N, N, N, 2, N, 1, N, N, N }, // 16
				{ N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, 1, N, N, 2 }, // 17
				{ N, N, N, N, N, N, N, N, 4, N, N, N, N, N, N, N, N, 2, N } }; // 18
		// -------0--1--2 -3- 4- 5- 6- 7- 8- 9--10-11-12-13-14-15-16-17-18
		/*
		 * { N, 1, N, N, N, 1, N, N, N, N, N, N, N, N, N, N }, { 1, N, 2, N, N, N, 1, N,
		 * N, N, N, N, N, N, N, N }, { N, 2, N, 1, N, N, N, 1, N, N, N, N, N, N, N, N },
		 * { N, N, 1, N, 1, N, N, N, N, 2, N, N, N, N, N, N }, { N, N, N, 1, N, N, N, N,
		 * N, N, 2, N, N, N, N, N }, { 1, N, N, N, N, N, 1, N, 1, N, N, N, N, N, N, N },
		 * { N, 1, N, N, N, 1, N, 2, N, N, N, N, N, N, N, N }, { N, N, 1, N, N, N, 2, N,
		 * N, N, N, N, N, N, N, N }, { N, N, N, N, N, 1, N, N, N, 4, N, N, N, 2, N, N },
		 * { N, N, N, 2, N, N, N, N, 4, N, 1, N, 1, N, N, N }, { N, N, N, N, 2, N, N, N,
		 * N, 1, N, N, N, N, N, 2 }, { N, N, N, N, N, N, N, N, N, N, N, N, 3, N, 1, N },
		 * { N, N, N, N, N, N, N, N, N, 1, N, 3, N, N, N, N }, { N, N, N, N, N, N, N, N,
		 * 2, N, N, N, N, N, 1, N }, { N, N, N, N, N, N, N, N, N, N, N, 1, N, 1, N, 4 },
		 * { N, N, N, N, N, N, N, N, N, N, 2, N, N, N, 4, N }
		 */

		// création du graphe
		Graphe g0 = new Graphe(matDuree);
		// LA SUITE

		// creation d'une instance de l'algorithme avec le graphe g0
		Dijkstra dijkstra = new Dijkstra(origin, g0);

		OrderSender sender = new OrderSender(dijkstra.getChemin(destination), Direction.LEFT);

		ArduinoConnector.sendToArduino(sender.getFinalOrder());

		scan.close();

		dijkstra.afficheChemin(destination);
	}

}
