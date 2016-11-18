#include <iostream>
#include "Electre.hpp"

using namespace std;

Electre::Electre(int donnees[][10], double p, double *concordances, double *discordances) {
	this->donnees = donnees;
	this->p = p;
	this->concordances = concordances;
	this->discordances = discordances;
	calculerIndices();
	calculerNonSurclasses();
}

void Electre::afficherIndexC() const {
	cout << "Indices de concordance" << endl;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << indexC[i][j] << " & ";
		}
		cout << endl;
	}
}

void Electre::afficherIndexD() const {
	cout << "Indices de discordance" << endl;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << indexD[i][j] << " & ";
		}
		cout << endl;
	}
}

void Electre::afficherNonSurclasses() const {
	cout << "Non surclasses" << endl;
	double concord, discord;
	for (int c = 0; c < 4; ++c) {				// pour chaque valeur de concordance
		concord = this->concordances[c];
		for (int d = 0; d < 5; ++d) {				// pour chaque valeur de discordance
			discord = this->discordances[d];
			cout << "(c="<<concord<<",d="<<discord<<") & ";
			for (int i = 0; i < 200; ++i) {				// pour chaque alternative
				if (this->nonSurclasses[c*5+d][i] == 1) {
					cout << ", " << i;
				}
			}
			cout << endl;
		}
	}
}

void Electre::afficherNbSurclassee() const {
	cout << "Nombre d'apparition dans le noyau" << endl;
	cout << 1 << " & " << nonSurclasseesGlobaux[0][0];
	for (int i = 1; i < 200; ++i) {
		if (this->nonSurclasseesGlobaux[i][1] != this->nonSurclasseesGlobaux[i-1][1]) {
			cout << " & " << this->nonSurclasseesGlobaux[i-1][1] << endl;
			cout << i+1 << " & " << nonSurclasseesGlobaux[i][0];
		} else {
			cout << ", " << this->nonSurclasseesGlobaux[i][0];
		}
	}
	cout << " & " << this->nonSurclasseesGlobaux[199][1] << endl;
	cout << endl;
}

void Electre::calculerIndices() {
	int nbSup;
	double diffMax, diff;
	for (int i1 = 0; i1 < 200; ++i1) {
		for (int i2 = 0; i2 < 200; ++i2) {
			nbSup = 0;
			diffMax = 0;
			for (int j = 0; j < 10; ++j) {
				diff = this->donnees[i1][j] - this->donnees[i2][j];
				if (diff >= 0) {
					nbSup = nbSup + 1;
				} else if (diffMax < -diff) { 	/// C'est bon ?
					diffMax = -diff;
				}
			}
			this->indexC[i1][i2] = nbSup*this->p;
			this->indexD[i1][i2] = diffMax/100;
		}
	}
}

void Electre::calculerNonSurclasses() {
	bool estSurclasse;
	double concord, discord;
	int i1, i2;
	
	for (i1 = 0; i1 < 200; ++i1) {
		this->nonSurclasseesGlobaux[i1][0] = i1;
		this->nonSurclasseesGlobaux[i1][1] = 0;
	}
	
	for (int c = 0; c < 4; ++c) {					// pour chaque valeur de concordance
		concord = this->concordances[c];
		for (int d = 0; d < 5; ++d) {				// pour chaque valeur de discordance
			discord = this->discordances[d];
			for (i1 = 0; i1 < 200; ++i1) {
				estSurclasse = false;
				i2 = 0;
				while ((!estSurclasse) && (i2 < 200)) {
					if ((indexC[i2][i1] >= concord) && (indexD[i2][i1] <= discord) && (i1 != i2)) {
						estSurclasse = true;
					} else {
						i2 = i2 + 1;
					}
				}
				if (estSurclasse) {
					this->nonSurclasses[5*c+d][i1] = 0;
				} else {
					this->nonSurclasses[5*c+d][i1] = 1;
					this->nonSurclasseesGlobaux[i1][1] = this->nonSurclasseesGlobaux[i1][1] + 1;
				}
			}
		}
	}
	trierNonSurclassesGlobaux();
}

void Electre::trierNonSurclassesGlobaux() {
	bool changement;
	int tab10, tab11, tab20, tab21;
	
	do {
		changement = false;
		tab10 = this->nonSurclasseesGlobaux[0][0];
		tab11 = this->nonSurclasseesGlobaux[0][1];
		for (int i = 1; i < 200; ++i) {
			tab20 = this->nonSurclasseesGlobaux[i][0];
			tab21 = this->nonSurclasseesGlobaux[i][1];
			if (tab21 > tab11) {
				this->nonSurclasseesGlobaux[i-1][0] = tab20;
				this->nonSurclasseesGlobaux[i-1][1] = tab21;
				this->nonSurclasseesGlobaux[i][0] = tab10;
				this->nonSurclasseesGlobaux[i][1] = tab11;
				changement = true;
			} else {
				tab10 = tab20;
				tab11 = tab21;
			}
		}
	} while (changement);
}
