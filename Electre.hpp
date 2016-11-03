
class Electre {
	private:
		// Matrice des données
		int (*donnees)[10];			///[200][10]
	
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
		Electre(int donnees[][10], double p, double *concordances, double *discordances);
		void afficherIndexC() const;
		void afficherIndexD() const;
		void afficherNonSurclasses() const;
		void afficherNbSurclassee() const;

	private:
		void calculerIndices();
		void calculerNonSurclasses();
		void trierNonSurclassesGlobaux();
};
