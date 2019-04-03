//SDIZO I1 220A LAB01
//Justyna Dreger
//dj39254@zut.edu.pl
#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
using namespace std;
struct str {
	int a;
	char c;
	float b;
};
//tworzenie struktur i dodawanie wartoúci danym
str** los(int N) {
	str **wsk = new str*[N];
	int j;
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		wsk[i] = new str;
		wsk[i]->a = (rand()%10000)-1000;
		if (i != 0) {	
			j = 0;
			do {
				if (wsk[i]->a == wsk[j]->a) {
					wsk[i]->a = (rand() % 10001) - 1000;
					j=0;
				}
				else j++;
			} while (j < i);
		}
		wsk[i]->b = 1000+i+1;
		wsk[i]->c = (rand()%23)+66;
	}
	return wsk;
}
//kasowanie wskaünika na struktury
void kas(str**wsk, int N) {
	for (int i = 0; i < N; i++) {
		delete[] wsk[i];
	}
	delete[]wsk;
}
//sortowanie bπbelkowe ze wzglÍdu na element a
void sort(str**wsk, int N) {
	str **temp=new str*[1];
	temp[0] = new str;
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < N - i-1; j++) {
			if (wsk[j]->a > wsk[j+1]->a) {
				temp[0]= wsk[j];
				wsk[j] = wsk[j+1];
				wsk[j+1] = temp[0];
			}
	}
	}
delete[] temp[0];
delete[]temp;
}
//zliczanie iloúci wystπpienia danego znaku
int znak(str**wsk, int N,char zn) {
	int licz = 0;
	for (int i = 0; i < N; i++) {
		if (zn == wsk[i]->c) licz++;
	}
	return licz;
}
int main()
{
	int N;
	char X;
	srand(time(NULL));
	clock_t begin, end;
	double time_spent;
	begin = clock();
	ifstream dane("inlab01.txt");
	while (!dane.eof()) {
		dane >> N;
		dane >> X;
	}
	str **wsk = los(N);
	sort(wsk, N);
	if (N > 20) N = 20;
	for (int i = 0; i < N; i++) {
		cout << wsk[i]->a << endl;
		cout << wsk[i]->b << endl;
		cout << wsk[i]->c << endl;
	}
	cout << "Liczba wyszukanych znakow: " << znak(wsk, N, X) << endl;
	kas(wsk, N);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "czas dzialania programu: " << time_spent << endl;
	system("pause");
	return 0;
}

