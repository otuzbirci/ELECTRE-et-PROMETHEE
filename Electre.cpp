#include <iostream>
#include "Electre.hpp"

using namespace std;

Electre::Electre(int donnees[][10], double p, double *concordances, double *discordances) {
	this->donnees = donnees;
	this->p = p;
	this->concordances = concordances;
	this->discordances = discordances;
	this->calculerIndices();
	this->calculerNonSurclasses();
}

void Electre::afficherIndexC() const {
	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			cout << indexC[i][j] << "\t";
		}
		cout << endl;
	}
}

void Electre::afficherIndexD() const {
	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			cout << indexD[i][j] << "\t";
		}
		cout << endl;
	}
}

void Electre::afficherNonSurclasses() const {
	double concord, discord;
	for (int c = 0; c < 4; ++c) {				// pour chaque valeur de concordance
		concord = this->concordances[c];
		for (int d = 0; d < 5; ++d) {				// pour chaque valeur de discordance
			discord = this->discordances[d];
			cout << "(c="<<concord<<",d="<<discord<<")";
			for (int i = 0; i < 200; ++i) {
				if (this->nonSurclasses[c*5+d][i] == 1) {
					cout << "\t" << i;
				}
			}
			cout << endl;
		}
	}
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
				} else if (diff < diffMax) {
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
	for (int c = 0; c < 4; ++c) {				// pour chaque valeur de concordance
		concord = this->concordances[c];
		for (int d = 0; d < 5; ++d) {				// pour chaque valeur de discordance
			discord = this->discordances[d];
			for (i1 = 0; i1 < 200; ++i1) {
				estSurclasse = false;
				i2 = 0;
				while ((!estSurclasse) && (i2 < 200)) {
					if ((indexC[i2][i1] >= concord) && (indexD[i2][i1] <= discord) && (i1 != i2)) {
						//~ cout<<"indexC["<<i2<<"]["<<i1<<"]="<<indexC[i2][i1]<<">="<<concord<<endl;
						//~ cout<<"indexD["<<i2<<"]["<<i1<<"]="<<indexD[i2][i1]<<"<="<<discord<<endl;
						//~ cout << endl;
						estSurclasse = true;
					} else {
						i2 = i2 + 1;
					}
				}
				if (estSurclasse) {
					this->nonSurclasses[5*c+d][i1] = 0;
				} else {
					this->nonSurclasses[5*c+d][i1] = 1;
				}
			}
		}
	}
}
