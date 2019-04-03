////SDIZO I1 220A LAB02
//Justyna Dreger
//dj39254@zut.edu.pl
#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
using namespace std;
struct Wezel {
	int klucz;
	double x;
	char y;
	Wezel *nastepnik;
	Wezel *poprzednik;
};
//dodawanie wêz³a do listy - zrobione
Wezel *dodajE(int k, Wezel *glowa) {
	Wezel *wsk,*bierzacy,*poprzedni,*ogon;
	wsk = new Wezel;
	wsk->klucz = k;
	wsk->x = rand() + (double)rand() / RAND_MAX;
	wsk->y = 'T';
	if (glowa == NULL) {
		glowa = wsk;
		glowa->nastepnik = wsk;
		glowa->poprzednik = wsk;
		return glowa;
	}
	bierzacy = glowa;
	poprzedni=glowa->poprzednik;
	ogon = glowa->poprzednik;
	if (k < glowa->klucz) {
			glowa->poprzednik = wsk;
			wsk->nastepnik = glowa;
			wsk->poprzednik = poprzedni;
			poprzedni->nastepnik = wsk;
			glowa = wsk;
			return glowa;
		}
	if (k > ogon->klucz) {
			wsk->nastepnik = glowa;
			glowa->poprzednik = wsk;
			ogon->nastepnik = wsk;
			wsk->poprzednik = ogon;
			ogon=wsk;
			return glowa;
		}
	while (bierzacy) {
		if (k == bierzacy->klucz) {
			return 0;
		}
		if (k<bierzacy->klucz&&k>poprzedni->klucz) {
			poprzedni->nastepnik = wsk;
			wsk->poprzednik = poprzedni;
			bierzacy->poprzednik = wsk;
			wsk->nastepnik = bierzacy;
			break;
		}
		poprzedni = bierzacy;
		bierzacy = bierzacy->nastepnik;
	}
	return glowa;
}
//dodanie X elementów do listy - zrobione
Wezel *dodajX(int X, Wezel *glowa) {
	Wezel *bierzacy,*tmp;
	tmp = new Wezel;
	bierzacy = glowa;
	int klucz;
	for (int i = 0; i < X; i++) {
		klucz = rand() % 99901 + 99;
		tmp = dodajE(klucz, bierzacy);
		while(tmp == 0) {
			klucz = rand() % 99901 + 99;
			tmp = dodajE(klucz, bierzacy);
		}
		bierzacy = tmp;
	}
	return bierzacy;
}
//wyszukiwanie elementu - zrobione
bool wyszykajE(int k, Wezel *glowa) {
	Wezel *bierzacy;
	bierzacy = glowa;
	if (bierzacy) {
		do {
			if (k == bierzacy->klucz) {
				return true;
				break;
			}
			bierzacy = bierzacy->nastepnik;
		} while (bierzacy != glowa);
		return false;
	}
}
//usuwanie elementu - zrobione
Wezel *usunE(int k, Wezel *glowa) {
	if (glowa == NULL) {
		return glowa;
	}
	Wezel *bierzacy, *poprzedni, *ogon,*wsk,*nastepny;
	bierzacy = glowa;
	ogon = glowa->poprzednik;
	if (k == glowa->klucz) {
		wsk = glowa;
		ogon->nastepnik = glowa->nastepnik;
		glowa = glowa->nastepnik;
		glowa->poprzednik = ogon;
		delete wsk;
		return glowa;
	}
	if (k==ogon->klucz) {
		wsk = ogon;
		poprzedni = ogon->poprzednik;
		poprzedni->nastepnik = glowa;
		glowa->poprzednik = poprzedni;
		ogon = ogon->poprzednik;
		delete wsk;
		return glowa;
	}
	while (bierzacy) {
		if (k == bierzacy->klucz) {
			wsk = bierzacy;
			poprzedni = bierzacy->poprzednik;
			nastepny = bierzacy->nastepnik;
			poprzedni->nastepnik = nastepny;
			nastepny->poprzednik = poprzedni;
			bierzacy = bierzacy->nastepnik;
			delete wsk;
			return glowa;
		}
		poprzedni = bierzacy;
		bierzacy = bierzacy->nastepnik;
	}
	return glowa;
}
//wyswietlenie Y wez³ów od poczatku - zrobione
void wyswietlY(int X, Wezel *glowa) {
	Wezel *bierzacy;
	int i = 0;
	bierzacy = glowa;
	cout << "Wsyswietlenie " << X << " wartosci kluczowych od poczatku :" << endl;
	if (bierzacy == NULL)
		cout << "Lista jest pusta lub nie istnieje" << endl;
	if (bierzacy) {
		do {
			cout << bierzacy->klucz <<" ";
			i++;
			bierzacy = bierzacy->nastepnik;
		} while (bierzacy != glowa && i < X);
	}
}
//wyœwietlenie Z wêz³ów od koñca - zrobione
void wyswietlZ(int X, Wezel *glowa) {
	Wezel *bierzacy;
	int i = 0;
	bierzacy = glowa;
	cout << "Wsyswietlenie " << X << " wartosci kluczowych od konca :" << endl;
	if (bierzacy == NULL)
		cout << "Lista jest pusta!" << endl;
	if (bierzacy) {
		do {
			if(i==0)	bierzacy = bierzacy->poprzednik;
			cout << bierzacy->klucz << " ";
			i++;
			bierzacy = bierzacy->poprzednik;
		} while (bierzacy != glowa && i < X);
	}
}
//zliczanie wêz³ów w liœcie -zrobione
void ileE(Wezel *glowa) {
	if (glowa != NULL) {
		Wezel *bierzacy;
		bierzacy = glowa->nastepnik;
		int licznik = 1;
		while (bierzacy&&bierzacy!=glowa) {
			licznik++;
			bierzacy = bierzacy->nastepnik;
		}
		cout << "Obecna liczba wezlow w liscie : " << licznik << endl;
	}
	else
	cout << "Lista jest pusta!" << endl;
}
//usuwanie listy - zrobione
Wezel *usunL(Wezel *glowa) {
	if (glowa != NULL) {
		Wezel *bierzacy = glowa;
		Wezel *wsk = NULL;
		while (wsk && wsk != glowa) {
			wsk = bierzacy;
			bierzacy = bierzacy->nastepnik;
			delete wsk;
		}
		delete bierzacy;
		glowa = NULL;
	}
	return glowa;
}
int main()
{
	int X, k1, k2, k3, k4, k5;
	srand(time(NULL));
	clock_t begin, end;
	double time_spent;
	begin = clock();
	ifstream dane("inlab02.txt");
	while (!dane.eof()) {				//pobranie danych
		dane >> X >> k1 >> k2 >> k3 >> k4 >> k5;
	}
	Wezel *w = NULL;
	cout << "Wyszukanie wezla o kluczu " << k1 <<" : "<<endl;
	if (wyszykajE(k1, w) == true) {
		cout << "Znaleziono k1." << endl;
	}
	else cout << "Nie znaleziono k1." << endl;
	w = dodajX(X, w);
	ileE(w);
	cout << endl;
	wyswietlY(20, w);
	w = dodajE(k2, w);
	wyswietlY(20, w);
	w = dodajE(k3, w);
	wyswietlY(20, w);
	w = dodajE(k4, w);
	wyswietlY(20, w);
	w = dodajE(k5, w);
	w = usunE(k3, w);
	wyswietlY(20, w);
	w = usunE(k2, w);
	wyswietlY(20, w);
	w = usunE(k5, w);
	ileE(w);
	cout << "Wyszukanie wezla o kluczu : " << k5 << endl;
	if (wyszykajE(k5, w) == true) {
		cout << "Znaleziono k5." << endl;
	}
	else cout << "Nie znaleziono k5." << endl;
	wyswietlZ(11,w);
	w = usunL(w);
	if ( w== NULL) {
		cout << "Lista zostala usunieta." << endl<<endl;
	}
	else cout << "Lista nie zostala usunieta." << endl<<endl;
	wyswietlZ(11,w);
	cout << endl;
	ileE(w);
	cout << endl;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "czas dzialania programu: " << time_spent << endl;
	system("pause");
	return 0;
}

