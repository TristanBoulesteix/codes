public class Main {
	public static void main(String[] args) {
		int N = Graphe.ALPHA_NOTDEF ;
		int [][] matDuree={
		                   {N,1,N,N,N,1,N,N,N,N,N,N,N,N,N,N},
		                   {1,N,2,N,N,N,1,N,N,N,N,N,N,N,N,N},
		                   {N,2,N,1,N,N,N,1,N,N,N,N,N,N,N,N},
		                   {N,N,1,N,1,N,N,N,N,2,N,N,N,N,N,N},
		                   {N,N,N,1,N,N,N,N,N,N,2,N,N,N,N,N},
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
		//création du graphe			
		Graphe g0 = new Graphe(matDuree);
		//LA SUITE		
		
		
		// creation d'une instance de l'algorithme avec le graphe g0
		Dijkstra beaulieuAutresStations= new Dijkstra(15,g0);
		
		// Pour afficher le chemin le plus rapide pour aller de beaulieu a Clemenceau
		beaulieuAutresStations.afficheChemin(7);
	}

}
