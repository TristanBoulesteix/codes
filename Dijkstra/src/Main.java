public class Main {
	public static void main(String[] args) {
		int N = Graphe.ALPHA_NOTDEF ;
		int [][] matDuree={
		                   {N,1,N,N,N,1,N,N,N,N,N,N,N,N,N,N},
		                   {1,N,2,N,N,N,1,N,N,N,N,N,N,N,N,N},
		                   {N,2,N,1,N,N,N,1,N,N,N,N,N,N,N,N},
		                   {N,N,1,N,1,N,N,N,N,2,N,N,N,N,N,N},
		                   {N,N,1,N,N,N,N,N,N,N,2,N,N,N,N,N},
		                   {1,N,N,N,N,N,1,N,1,N,N,N,N,N,N,N},
		                   {N,1,N,N,N,1,N,2,N,N,N,N,N,N,N,N},
		                   {N,N,1,N,N,N,2,N,N,N,N,N,N,N,N,N},
		                   {N,N,N,N,N,1,N,N,N,4,N,N,N,2,N,N},
		                   {N,N,N,2,N,N,N,N,4,N,1,N,1,N,N,N},
		                   {N,N,N,N,2,N,N,N,N,1,N,N,N,N,N,2},
		                   {N,N,N,N,N,N,N,N,N,N,N,N,3,N,1,N},
		                   {N,N,N,N,N,N,N,N,N,1,N,3,N,N,N,N},
		                   {N,N,N,N,N,N,N,N,2,N,N,N,N,N,1,N},
		                   {N,N,N,N,N,N,N,N,N,N,N,1,N,1,N,4},
		                   {N,N,N,N,N,N,N,N,N,N,2,N,N,N,4,N}
		                  };
		//cr�ation du graphe			
		Graphe g0 = new Graphe(matDuree);
		//LA SUITE		
		
		
		// creation d'une instance de l'algorithme avec le graphe g0
		Dijkstra beaulieuAutresStations= new Dijkstra(0,g0);
		
		
		
		// Calcul du plus court chemin avec l'algorithme de Dijkstra 
		beaulieuAutresStations.calculePlusCourtChemin();
		

		
//		// Affichage du temps de trajet
int duree = beaulieuAutresStations.longueurChemin(11);
		System.out.println("Le temps mini pour aller de beaulieu a Clemenceau est :"+duree);
		
		// Pour afficher le chemin le plus rapide pour aller de beaulieu a Clemenceau
		beaulieuAutresStations.afficheChemin(11); // pour ça il faut un tableau de prédécesseur, il nous faudra un tableau de routage
		//il nous faudrait créer un tableau R des prédecesseurs.
		
		
		//Creation d'une nouvelle instance de l'algorithme avec un départ de Republique
		Dijkstra republiqueAutresStations= new Dijkstra(7,g0);
		republiqueAutresStations.calculePlusCourtChemin();
		int duree3 = republiqueAutresStations.longueurChemin(3);
		System.out.println("Le temps mini pour aller de republique a Clemenceau est :"+duree3);
	}

}
