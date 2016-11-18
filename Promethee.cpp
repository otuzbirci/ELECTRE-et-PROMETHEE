#include <iostream>
#include "Promethee.hpp"

using namespace std;

Promethee::Promethee(int donnees[][10], double poids, int *p, int *q) {
	this->donnees = donnees;
	this->p = p;
	this->q = q;
	calculerPreferencesGlobales();
	calculerScores();
}

double Promethee::fonction_de_preference (int diff, int p, int q) const {
	if (diff <= p) {
		return 0.0;
	} else if (diff >= q) {
		return 1.0;
	} else {
		return 1.0*(diff - p)/(q - p);
	}
}

void Promethee::afficherPreferencesGlobales() {
	cout << "Préférences globales" << endl;
	for (int seuil = 0; seuil < 3; ++seuil) {
		cout << "\t{"<<this->p[seuil]<<","<<this->q[seuil]<<"}\t";
	}
	cout << endl;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << i << ":" << j << "->\t";
			for (int seuil = 0; seuil < 3; ++seuil) {
				cout << this->preferencesGlobales[i][j][seuil] << "\t\t";
			}
			cout << endl;
		}
	}
	cout << endl;
}

void Promethee::afficherScores() {
	cout << "Scores totaux" << endl;
	for (int seuil = 0; seuil < 3; ++seuil) {
		cout << "{"<<this->p[seuil]<<","<<this->q[seuil]<<"}\t\t\t\t";
	}
	cout << endl;
	for (int i = 0; i < 200; ++i) {
		for (int seuil = 0; seuil < 3; ++seuil) {
			cout << this->scores[i][seuil][0] << ":\t(" << this->scores[i][seuil][1] << ")\t\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Promethee::calculerPreferencesGlobales() {
	int diff, P, Q;
	double somme, preference;
	
	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			for (int seuil = 0; seuil < 3; ++ seuil) {
				P = this->p[seuil];
				Q = this->q[seuil];
				somme = 0;
				for (int c = 0; c < 10; ++c) {
					diff = this->donnees[i][c] - this->donnees[j][c];
					preference = fonction_de_preference(diff, P, Q);
					somme = somme + preference;
				}
				this->preferencesGlobales[i][j][seuil] = somme/10;
			}
		}
	}
}

void Promethee::calculerScores() {
	double sommePositive, sommeNegative;
	
	for (int i = 0; i < 200; ++i) {
		sommePositive = 0;
		sommeNegative = 0;
		for (int seuil = 0; seuil < 3; ++seuil) {
			for (int j = 0; j < 200; ++j) {
				sommePositive = sommePositive + this->preferencesGlobales[i][j][seuil];
				sommeNegative = sommeNegative + this->preferencesGlobales[j][i][seuil];
			}
			this->scores[i][seuil][0] = i;
			this->scores[i][seuil][1] = (sommePositive-sommeNegative)/199;
		}
	}
	this->trierScores();
}

void Promethee::trierScores() {
	bool changement;
	double tab10, tab11, tab20, tab21;
	
	for (int seuil = 0; seuil < 3; ++seuil) {
		do {
			changement = false;
			tab10 = this->scores[0][seuil][0];
			tab11 = this->scores[0][seuil][1];
			for (int i = 1; i < 200; ++i) {
				tab20 = this->scores[i][seuil][0];
				tab21 = this->scores[i][seuil][1];
				if (tab21 > tab11) {
					this->scores[i-1][seuil][0] = tab20;
					this->scores[i-1][seuil][1] = tab21;
					this->scores[i][seuil][0] = tab10;
					this->scores[i][seuil][1] = tab11;
					changement = true;
				} else {
					tab10 = tab20;
					tab11 = tab21;
				}
			}
		} while (changement);
	}
}
