
//////SDIZO I1 220A LAB03
//Justyna Dreger
//dj39254@zut.edu.pl

#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<cstring>
using namespace std;
struct Wezel {
	int klucz;
	string kl;
	Wezel *prawy, *lewy;
};
//inicjacja drzewa -zrobione
Wezel *in() {
	Wezel *korzen = new Wezel;
	korzen = NULL;
	return korzen;
}
//wstawianie elementu o podanym kluczu - zrobione
Wezel *wstawE(Wezel *korzen, int k) {
	Wezel *nowy, *biezacy, *poprzedni;
	nowy = new Wezel;
	nowy->klucz = k;
	nowy->kl = (char)k;
	nowy->prawy = NULL;
	nowy->lewy = NULL;
	if (korzen == NULL) {		//drzewo było puste
		korzen = nowy;
		return korzen;
	}
	poprzedni = new Wezel;
	biezacy = korzen;
	poprzedni = NULL;
	do{			//wyszukanie miejsca na nowy wezeł
		if (biezacy->klucz == nowy->klucz) {
			return 0;
		}
		poprzedni = biezacy;
		if (biezacy->klucz > k)
			biezacy = biezacy->lewy;
		else
			biezacy = biezacy->prawy;

	}while (biezacy);
	if (poprzedni->klucz < k)
		poprzedni->prawy = nowy;
	else poprzedni->lewy = nowy;
	return korzen;
}
	
//wstawianie X elementów do drzewa - zrobione
Wezel *wstawX(Wezel *korzen, int X) {
	Wezel *biezacy,*tmp;
	biezacy = korzen;
	int klucz;
	for (int i = 0; i < X; i++) {
	klucz= rand() % 20001 - 10000;
	tmp = wstawE(biezacy, klucz);
	while (tmp == 0) {
		klucz = rand() % 99901 + 99;
		tmp = wstawE(biezacy,klucz);
	}
	biezacy = tmp;
	}
	return biezacy;
}
//wyszukanie elementu o danym kluczu - zrobione
bool wyszukajE(Wezel *korzen, int k) {
	Wezel *biezacy;
	if (korzen == NULL) return false;
	if (korzen->klucz == k) return true;
	biezacy = korzen;
	while (biezacy) {
		if (k == biezacy->klucz) return true;
		else {
			if (k < biezacy->klucz) {
				biezacy = biezacy->prawy;
			}
			else biezacy=biezacy->lewy;
		}
	}
return false;
}
//usuniecie elementu o podanym kluczu-zrobione
Wezel *usunE(Wezel *korzen, int k) {
	Wezel *rodzic, *temp, *prerodzic, *potomek, *newpotomek;
	rodzic = NULL;
	temp = korzen;
	do {
		//znalezienie miejsca
		while (temp && k != temp->klucz) {
			rodzic = temp;
			if (temp->klucz > k) temp = temp->lewy;
			else temp = temp->prawy;
		}
		int a = 0;;
		//nie znaleziono wezla o danym kluczu
		if (temp == NULL)	cout << "Nie istnieje wezel o takim kluczu. " << k << endl << endl;
		else {
			if (temp->prawy == NULL && temp->lewy == NULL) a = 1;//usuwany wezel jest lisciem

			if (temp->prawy == NULL) a = 2;//usuwany wezel ma tylko lewego potomka

			if (temp->lewy == NULL) a = 3; //usuwany wezel ma tylko prawego potomka
			switch (a) {
			case 1:
			{
				if (rodzic == NULL) //usuwany wezel jest korzeniem
				{
					korzen = NULL;
					delete temp;
				}
				if (rodzic->prawy == temp) rodzic->prawy = NULL;
				else rodzic->lewy = NULL;
				delete temp;
				return korzen;
			}
			break;
			case 2:
			{
				if (rodzic == NULL) //usuwany wezel nie jest korzeniem
				{
					korzen = temp->lewy;
				}
				else {
					if (rodzic->lewy == temp) rodzic->lewy = temp->lewy;
					else rodzic->prawy = temp->lewy;
				}
				delete temp;
				return korzen;
				break;
			}
			case 3: {
				if (rodzic != NULL) //usuwany wezel nie jest korzeniem
				{
					if (rodzic->prawy == temp) rodzic->prawy = temp->prawy;
					else rodzic->lewy = temp->prawy;
				}
				else korzen = temp->prawy;
				delete temp;
				return korzen;
			}
					break;
			}
			prerodzic = temp; //odwolujemy sie do nastepnika
			potomek = temp->prawy;
			do  //wyszukanie nastepnika
			{
				prerodzic = potomek;
				potomek = potomek->lewy;
			} while (potomek->lewy != NULL);
			if (potomek == temp->lewy) //nastepnik jest lewym potomkiem
			{
				if (rodzic != NULL) //usuwany wezel nie jest korzeniem
				{
					if (rodzic->lewy == temp) rodzic->prawy = potomek;
					else rodzic->lewy = potomek;
				}
				else
				{
					potomek->prawy = temp->prawy;
					korzen = potomek;
				}
				newpotomek = potomek->lewy; //nastepnik jest prawnukiem
				if (prerodzic->lewy == potomek) prerodzic->lewy = newpotomek;
				else prerodzic->prawy = newpotomek;
				potomek->lewy = temp->lewy;
				if (rodzic == NULL)
				{
					potomek->prawy = temp->prawy;
					korzen = potomek;
				}
				else
				{
					if (rodzic->prawy != temp) rodzic->lewy = potomek;
					else rodzic->prawy = potomek;
				}
			}
			delete temp;
			return korzen;
		}
	} while (1 < 0);
}
//przejscie drzewa w trybie inorder - zrobione
float inorder(Wezel *korzen) {
	float i = 0;
	do {
		if (korzen != NULL) {

			i =inorder(korzen->lewy)+i;
			cout << korzen->klucz << " ";
			i++;
			i =inorder(korzen->prawy)+i;
		}
	} while (i<0);
	return i;
}
//przejscie drzewa w tybie preorder - zrobione
float preorder(Wezel *korzen) {
	float i=0;
	do {
		if (korzen != NULL) {
			cout << korzen->klucz << " ";
			i++;
			i = preorder(korzen->lewy)+i;
			i = preorder(korzen->prawy)+i;
		}
	} while (i < 0);
	return i;
}
//przejscie drzewa w trybie postorder - zrobione
float postorder(Wezel *korzen) {
	float i = 0;
	do {
		if (korzen != NULL) {
			i = i + postorder(korzen->lewy);
			i = i + postorder(korzen->prawy);
			i++;
			cout << korzen->klucz << " ";
		}
	} while (i < 0);
	return i;
}
int main()
{
	int X, k1, k2, k3, k4;
	srand(time(NULL));
	clock_t begin, end;
	double time_spent;
	begin = clock();
	ifstream dane("inlab03.txt");
	while (!dane.eof()) {				//pobranie danych
		dane >> X >> k1 >> k2 >> k3 >> k4;
	}
	Wezel *w;
	cout << "Inicjacja drzewa." << endl;
	w = in();		//inicjacja pustego drzewa
	cout << "Usuwanie elementu " << k1 << endl;
	w = usunE(w,k1);//usuwanie elementu o kluczu k1
	cout << "Wstawianie elementu "<< k1 << endl;
	w = wstawE(w, k1);	//wstawianie elementu o kluczu k1
	cout << "Wstawianie elementow " << X << endl;
	w = wstawX(w, X);	//wstawianie X elementów
	cout << "Wyswietlenie inorder :" <<inorder(w);		//wyswietlenie w trybie inorder
	cout << endl << "Wyswietlenie preorder. Odwiedzono wezlow : " <<preorder(w);	//wyswietlenie w trybie preorder
	cout << endl<<"Wstawianie elementu " << k2<< endl;
	w = wstawE(w, k2);	//wstawianie elementu o kluczu k2
	cout<<"Wyswietlenie inorder. Odwiedzono wezlo:"<<inorder(w);
	cout << endl<<"Wstawianie elementu " << k3 << endl;
	w = wstawE(w, k3);	//wstawianie elementu k3
	cout << "Wstawianie elementu " << k4 << endl;
	w = wstawE(w, k4);	//wstawianie elementu k4
	cout << "Usuwanie elementu " << k1 << endl;
	w = usunE(w, k1);
	cout << "Wyswietlenie wpreorder, Odwiedzono wezlow : " <<preorder(w);
	if (wyszukajE(w, k1) == true)			//wyszukania wezla o kluczu k1
		cout << endl<<"Znaleziono wezel o kluczu " << k1 << endl;
	else
		cout <<endl<< "Nieznaleziono wezla o kluczu " << k1 << endl;
	cout << "Usuwanie elementu " << k2<< endl;
	w = usunE(w, k2);
	cout << "Wyswietlenie inporder. Odwiedzono  wezlow : " <<inorder(w);
	cout << endl<<"Usuwanie elementu " << k3 << endl;
	w = usunE(w, k3);
	cout << "Usuwanie elementu " << k4 << endl;
	w = usunE(w, k4);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "czas dzialania programu: " << time_spent << endl;
	system("pause");
    return 0;
}

