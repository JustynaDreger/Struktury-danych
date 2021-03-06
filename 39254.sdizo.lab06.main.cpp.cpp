// 39254.sdizo.lab06.main.cpp : Defines the entry point for the console application.
// 
//SDIZO I1 220A LAB06
//Justyna Dreger
//dj39254@zut.edu.pl

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;
//adresowanie liniowe - zrobione
int al(int k) {
	k=(k % 1000) + pow(2, k % 10) + 1;
	k= k % 997;
	return k;
}
//mieszanie podwójne - zrobione
int mp(int klucz) {
	klucz = (3 * klucz);
	klucz=(klucz % 19)+1;
	return klucz;
}
//inicjacja tablicy - zrobione
void inicjacja(int tab[]) {
	for (int i = 0; i < 997; i++) {
		tab[i] = 0;
	}
}
//wyszukanie elementu
bool wyszukajE(int tab[], int klucz, string a) {
	int k = al(klucz);
	int i = k + 1;
	if (a == "al") {
		if (tab[k] == klucz) return true;
		do {
			if (tab[i] == klucz) return true;
			i++;
		} while (i < 997);
		return false;
	}
	else {
		if (a == "mp") {
			k = mp(klucz);
			if (tab[k] == klucz) return true;
			i = k+1;
			do {
				if (tab[i] == klucz) return true;
				i++;
			} while (i < 997);
			return false;
		}
	}
}

//usuniecie z tablicy obiektu
void usunE(int tab[], int klucz, string a) {
	cout << "Usuwanie elementu o kluczu: " << klucz << endl;
	bool czy = wyszukajE(tab, klucz, a);
	if (czy== false) {
		cout << "Nie znaleziono danego klucza" << endl << endl;
	}
	else {
		int k1;
		if (a == "mp") {
			k1 = mp(klucz);
		}
		else k1 = 1;
		int d = 0;
		int k2 = al(klucz);
		while (d<997) {
			d++;
			if (tab[k2] == klucz) {
				tab[k2] = -1;
			}
			else if (tab[k2] != klucz)
			{
				if (a == "al") {
					if (k2 == 996) {
						k2 = 0;
					}
					else k2 = k2 + k1;
				}
				else {
					if (k2 + k1 > 996) {
						int g = k2 + k1;
						g = g - 996;
						k2 = -1 + g;
					}
					else k2 = k2 + k1;
				}
			}
		}
	}
}
//wstawianie nowego obiektu 
void wstawE(int tab[], int klucz, string a) {
	int k = al(klucz);
	int i = k + 1;
	if (a == "al") {
		if (tab[k] == 0||tab[k]==-1) {
			tab[k]= klucz;
		}
		do {
			if (tab[i] == 0) {
				tab[i] = klucz;
			}
			i++;
		} while (i < 997);
	}
	if (a == "mp") {
			k = mp(klucz);
			if (tab[k] == 0) {
				tab[k] = klucz;
			}
			i = k + 1;
			do {
				if (tab[k] == 0) {
					tab[i] = klucz;	
				}
				i++;
			} while (i < 997);
		}
}
//wstawianie X elementów
void wstawX(int tab[],int X, string a){
	int klucz;
	cout << "Wstawianie " << X << "elementow." << endl;
	for (int i = 0; i < 997; i++) {
		klucz = rand() % 20001 + 20000;
		int k = 0;
		do {
			if (wyszukajE(tab, klucz, a) == true) { k = 1; klucz = rand() % 20001 + 20000; }
			else k = 0;
		} while (k == 1);
		 wstawE(tab, klucz, a);
	}
}

//wyświetlanie elementów od p do k - zrobione
void wyswietl(int tab[], int p, int k) {
	cout << "Wyświetlanie od " << p << " do " << k << endl;
	for (int i = p; i <= k; i++) {
		cout << tab[i] << " ";
	}
	cout << endl;
}
int main()
{
	int X, k1, k2, k3, k4;
	srand(time(NULL));
	clock_t begin, end;
	double time_spent;
	ifstream dane("inlab06.txt");
	while (!dane.eof()) {
		dane >> X >> k1 >> k2 >> k3 >> k4;
	}
	int tab[997];
	begin = clock();
	//ADRESOWANIE LINIOWE
	cout << "ADRESOWANIE LINIOWE" << endl << endl;
	string a = "al";
	//inicjacja tablicy
	cout << "Inicjacja tablicy." << endl;
	inicjacja(tab);
	//usuniecie k1
	usunE(tab, k1, a);
	//wstawienie k1
	wstawE(tab, k1, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wstaw X elementów
	wstawX(tab, X, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wstawianie k2,k3,k4
	wstawE(tab, k2, a);
	wstawE(tab, k3, a);
	wstawE(tab, k4, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wyswietlenie od 500 do 600
	wyswietl(tab, 500, 600);
	//usun k3
	usunE(tab, k3, a);
	//usun k4
	usunE(tab, k4, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wyswietlenie od 500 do 600
	wyswietl(tab, 500, 600);
	cout << endl << endl;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "czas dzialania I fazy programu: " << time_spent << endl;
	//MIESZANIE PODWÓJNE
	begin = clock();
	cout << endl << "MIESZANIE PODWOJNE" << endl;
	a = "mp";
	//inicjacja tablicy
	inicjacja(tab);
	//usuniecie k1
	usunE(tab, k1, a);
	//wstawienie k1
	wstawE(tab, k1, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wstaw X elementów
	wstawX(tab, X, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wstawianie k2,k3,k4
	wstawE(tab, k2, a);
	wstawE(tab, k3, a);
	wstawE(tab, k4, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wyswietlenie od 500 do 600
	wyswietl(tab, 500, 600);
	//usun k3
	usunE(tab, k3, a);
	//usun k4
	usunE(tab, k4, a);
	//wyswietlenie od 0 do 100
	wyswietl(tab, 0, 100);
	//wyswietlenie od 500 do 600
	wyswietl(tab, 500, 600);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "czas dzialania II fazy programu: " << time_spent << endl;
	system("pause");
	return 0;
}

