
class Electre {
	private:
		// Matrice des données
		int (*donnees)[10];		///[200][10]
	
		// Poids des critères
		double p;
	
		// Valeurs de concordance
		double *concordances;	/// [4]
		
		// Valeurs de discordance
		double *discordances;	/// [5]
	
		// Indices de concordance
		double indexC[200][200];/// [200][200]
		
		// Indices de discordance
		double indexD[200][200];/// [200][200]
		
		// Le tableau des surclassement
		int nonSurclasses[200][20];
		
		// Le tableau alternatives trié des moins surclassées aux plus surclassées
		int nonSurclasseesGlobaux[200][2];
	
	public:
		// Constructeur
		Electre(int donnees[][10], double p, double *concordances, double *discordances);
		
		// Affiche les indices de concordance
		void afficherIndexC() const;
		
		// Affiche les indices de discordance
		void afficherIndexD() const;
		
		// Affiche les indices de discordance
		void afficherNonSurclasses() const;
		
		// Affiche le tableau trié dans l'ordre décroissant du nombre d'apparitions dans le noyau des alternatives
		void afficherNbSurclassee() const;

	private:
		// Calcule les indices de de concordance et de discordance en même temps 
		void calculerIndices();
		
		// Calcule pour chaque combinaison de de valeurs de discordance et de concordance si l'alternative est surclassée ou non
		// Calcule en même temps le tableau du nombre d'apparitions des alternatives dans le noyau
		void calculerNonSurclasses();
		
		// Trie le tableau du nombre d'apparitions dans le noyau dans l'ordre décroissant
		void trierNonSurclassesGlobaux();
};
