
class Promethee {
	private:
		// Matrice des données
		int (*donnees)[10];		///[200][10]
		
		// Poids des critères
		double poids;
		
		// Seuils d'indifférence p
		int *p;
		
		// Seuils d'indifférence q
		int *q;
		
		// Préférences globales entre deux alternatives
		double preferencesGlobales[200][200][3];
		
		// Scores totaux
		double scores[200][3][2];
		
	public:
		// Constructeur
		Promethee(int donnees[][10], double poids, int *p, int *q);
		
		// Affiche les préférences globales de chaque 
		void afficherPreferencesGlobales();
		void afficherScores();
		
	private:
		// Fonction de préférence donnée
		double fonction_de_preference (int diff, int p, int q) const;
		
		// Calcule les préférences globales entre chaque alternative pour chaque seuil
		void calculerPreferencesGlobales();
		
		// Calcule le score de chaque alternative
		void calculerScores();
		
		// Trie le tableau du score dans l'ordre décroissant
		void trierScores();
};
