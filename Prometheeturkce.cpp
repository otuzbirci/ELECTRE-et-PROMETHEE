#include <iostream>
#include "Promethee.hpp"

using namespace std;

Promethee::Promethee(int veri[][10], double agirlik, int *p, int *q) {
	this->veri = veri;
	this->p = p;
	this->q = q;
	geneltercihlerihesapla();
	olcumpuanlari();
}

double Promethee::tercih_fonksiyonu (int diff, int p, int q) const {
	if (diff <= p) {
		return 0.0;
	} else if (diff >= q) {
		return 1.0;
	} else {
		return 1.0*(diff - p)/(q - p);
	}
}

void Promethee::geneltercihleriignele() {
	cout << "Genel Tercihler" << endl;
	for (int esik = 0; esik < 3; ++esik) {
		cout << "\t{"<<this->p[esik]<<","<<this->q[esik]<<"}\t";
	}
	cout << endl;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << i << ":" << j << "->\t";
			for (int esik = 0; esik < 3; ++esik) {
				cout << this->geneltercihler[i][j][esik] << "\t\t";
			}
			cout << endl;
		}
	}
	cout << endl;
}

void Promethee::ignelenentercihler() {
	cout << "Toplam Puanlar" << endl;
	for (int esik = 0; esik < 3; ++esik) {
		cout << "{"<<this->p[esik]<<","<<this->q[esik]<<"}\t\t\t\t";
	}
	cout << endl;
	for (int i = 0; i < 200; ++i) {
		for (int esik = 0; seuil < 3; ++seuil) {
			cout << this->puanlar[i][esik][0] << ":\t(" << this->puanlar[i][esik][1] << ")\t\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Promethee::geneltercihlerihesapla() {
	int diff, P, Q;
	double toplam, preference;
	
	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			for (int esik = 0; esik < 3; ++ esik) {
				P = this->p[esik];
				Q = this->q[esik];
				toplam = 0;
				for (int c = 0; c < 10; ++c) {
					diff = this->veri[i][c] - this->veri[j][c];
					preference = tercih_fonksiyonu(diff, P, Q);
					toplam = toplam + preference;
				}
				this->geneltercihler[i][j][esik] = toplam/10;
			}
		}
	}
}

void Promethee::olcumpuanlari() {
	double toplamolumlu, toplamolumsuz;
	
	for (int i = 0; i < 200; ++i) {
		toplamolumlu = 0;
		toplamolumsuz = 0;
		for (int esik = 0; esik < 3; ++esik) {
			for (int j = 0; j < 200; ++j) {
				toplamolumlu = toplamolumlu + this->geneltercihler[i][j][esik];
				toplamolumsuz = toplamolumsuz + this->geneltercihler[j][i][esik];
			}
			this->puanlar[i][esik][0] = i;
			this->puanlar[i][esik][1] = (toplamolumlu-toplamolumsuz)/199;
		}
	}
	this->CesitliPuanlar();
}

void Promethee::CesitliPuanlar() {
	bool degisim;
	double tab10, tab11, tab20, tab21;
	
	for (int esik = 0; esik < 3; ++esik) {
		do {
			degisim = false;
			tab10 = this->puanlar[0][esik][0];
			tab11 = this->puanlar[0][esik][1];
			for (int i = 1; i < 200; ++i) {
				tab20 = this->puanlar[i][esik][0];
				tab21 = this->puanlar[i][esik][1];
				if (tab21 > tab11) {
					this->puanlar[i-1][esik][0] = tab20;
					this->puanlar[i-1][esik][1] = tab21;
					this->puanlar[i][esik][0] = tab10;
					this->puanlar[i][esik][1] = tab11;
					degisim = true;
				} else {
					tab10 = tab20;
					tab11 = tab21;
				}
			}
		} while (degisim);
	}
}
