package Dijkstra;

public class Graphe {

	// Declaration de variable

	private int[][] U;
	private boolean[] valid; // sommet valide veut dire qu'il existe dans le graphe
	public final static int ALPHA_NOTDEF = -999;// on met final psk c'est une constante

	// constructeur via une matrice adjacence:

	public Graphe(int[][] mat) {
		int NMax = mat.length;
		// int NMax = 1000 + mat.length;
		U = new int[NMax][NMax];
		valid = new boolean[NMax];
		for (int i = 0; i < U.length; i++) {
			if (i < mat.length) {
				valid[i] = true;
			} else {
				valid[i] = false;
			}
			for (int j = 0; j < U.length; j++) {
				if ((j < mat.length) && (i < mat.length)) {
					U[i][j] = mat[i][j];
				} else {
					U[i][j] = ALPHA_NOTDEF;
				}
			}
		}
	}

	public boolean existeSommet(int i) {
		boolean res = false;
		if (!((i > valid.length) || (i < 0))) {
			res = valid[i];
		}
		return res;
	}

	public int nbSommet() {
		int nb = 0;
		for (int i = 0; i < U.length; i++) {
			if (valid[i]) {
				nb++;
			}
		}
		return nb;
	}

	public boolean existeArc(int i, int j) {
		return ((existeSommet(i)) && (existeSommet(j)) && (U[i][j] != ALPHA_NOTDEF));
	}

	public int[][] getU() {
		return U;
	}
}
