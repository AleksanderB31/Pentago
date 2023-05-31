
#include <iostream> //PROGRAM UMOWZLIWIA GRE W KOLKO I KRZYZYK NA PLANSZY 6x6
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <string>
#include <stdio.h>
#define ODSUNIECIE_TABLICY 3
#define WYSOKOSC_TABLICY 6
#define SZEROKOSC_TABLICY 6
#define SZEROKOSC_OBRAMOWKI 24
#define LICZBA_GRACZY 2
#define GRACZ_PIERWSZY 0
#define GRACZ_DRUGI 1
#define WARUNEK_ZWYCIEZCTWA_W_KIK 5
using namespace std;
struct Tgracz {
	string imie;
	char token;
};
void wczytywanie_i_zapisywanie_imion_graczy(Tgracz gracze[]) {
	cout << "Podaj imie pierwszego gracza" << endl;
	getline(cin,gracze[GRACZ_PIERWSZY].imie);
	cout << "Podaj imie drugiego gracza" << endl;
	getline(cin,gracze[GRACZ_DRUGI].imie);
	cout << gracze[GRACZ_PIERWSZY].imie << ' ' << gracze[GRACZ_DRUGI].imie << endl;
} 
void cyfry() {
	cout << "  ";
	for (int i = 1; i <= SZEROKOSC_TABLICY; i++) {
		cout << i << "   ";
	}
}
void plansza(char tab[][SZEROKOSC_TABLICY],Tgracz gracze[]) {
	
	cout << setw(15) << "Gracz 1: " << gracze[GRACZ_PIERWSZY].imie << " | " << gracze[GRACZ_PIERWSZY].token << endl; //wypisanie naglowka
	cout << setw(ODSUNIECIE_TABLICY);
	cyfry();
	cout << endl;
	cout << setw(ODSUNIECIE_TABLICY);
	cout << char(0xC9); // znak oznaczajacy lewy gorny rog
	for (int i = 1; i < SZEROKOSC_OBRAMOWKI; i++) {
		if (i != SZEROKOSC_OBRAMOWKI/ 2) {
			cout << char(0xCD); // znak poziomy
		}
		else {
			cout << char(0xCB); // znak przerwyajacy poziom w polowie talbicy 
		}
	}
	cout << char(0xBB); // znak oznaczajacy prawy gorny rog
	int liczba = 0;
	for (int i = 0; i < WYSOKOSC_TABLICY; i++) {
		cout << setw(ODSUNIECIE_TABLICY);
		if (i > 0 && i != 3) {
			cout << char(0xBA); // znak pionowy po lewej stronie
			for (int g = 1; g < SZEROKOSC_OBRAMOWKI; g++) {
				if (g != SZEROKOSC_OBRAMOWKI/2) cout << char(0xC4); //poziome linie oddzielajace wiersze
				else cout << char(0xBA); // podwojna linia pozioma bedaca na srodku
			}
			cout << char(0xBA); //znak pionowy po prawej stronie
		}
		else if (i != 0) {
			cout << char(0xCC); // znak rozdzielajacy tablice na srodku na lewej linii
			for (int g = 1; g < SZEROKOSC_OBRAMOWKI; g++) {
				if (g != SZEROKOSC_OBRAMOWKI/2) cout << char(0xCD); // podwojna pozioma linia na ciagnaca sie przez srodek tablicy
				else cout << char(0xCE); //srodek planszy
			}
			cout << char(0xB9); //znak rozdzielajacy tablice na srodku na prawej linii
		}
		cout << setw(1);
		cout << endl;
		cout << liczba + 1 << ' ';//numer wiersza
		liczba++;
		cout << char(0xBA); //lewa linia kolumny
		for (int j = 0; j < SZEROKOSC_TABLICY; j++) {
			if (j > 0 && j != 3) {
				cout << char(0xB3);  //pionowe linie miedzy okienkami
			}
			else if (j != 0) {
				cout << char(0xBA); //srodkowa pionowa linia
			} 
				cout << ' ' << tab[i][j] << ' '; //wypisanie tablicy
		}
		cout << char(0xBA); //prawa linia kolumny
		cout << endl;
	}
	cout << setw(ODSUNIECIE_TABLICY);
	cout << char(0xC8); // znak oznaczajacy lewy dolny rog
	for (int i = 1; i < SZEROKOSC_OBRAMOWKI; i++) {
		if (i != SZEROKOSC_OBRAMOWKI / 2) {
			cout << char(0xCD); // znak przerwyajacy poziom w polowie talbicy 
		}
		else {
			cout << char(0xCA); // znak poziomy
		}
	}
	cout << char(0xBC) << endl; // znak oznaczajacy prawy dolny rog
	cout << setw(15) << "Gracz 2: " << gracze[GRACZ_DRUGI].imie << " | " << gracze[GRACZ_DRUGI].token << endl; //wypisanie stopki

}
void wybor_tokenu( Tgracz gracze[]) {
	int wybor;
	cout << "Aby wybrac znak X wybierz:1" << endl << "Aby wybrac znak O wybierz:2" << endl;
	cin >> wybor;
	if(wybor !=1 && wybor!=2){
		cout << "Aby wybrac znak X wybierz:1" << endl << "Aby wybrac znak O wybierz:2" << endl;
	while (!(cin >> wybor && (wybor==1 || wybor==2))) {
		cout << "Aby wybrac znak X wybierz:1" << endl << "Aby wybrac znak O wybierz:2" << endl;
		cin.clear();
		cin.ignore(200, '\n');
	}
	}
	if (wybor == 1) {
		gracze[GRACZ_PIERWSZY].token = 'X';
		gracze[GRACZ_DRUGI].token = 'O';
	}
	if (wybor == 2) {
		gracze[GRACZ_PIERWSZY].token = 'O';
		gracze[GRACZ_DRUGI].token = 'X';
	}
}
bool czy_ktos_przegral(char tab[][SZEROKOSC_TABLICY], int poprzedni_gracz, Tgracz gracze[]) {
	int znaki_w_linii = 0;
	int obecny_gracz;
	obecny_gracz = (++poprzedni_gracz) % 2;
	for (int i = 0; i < WYSOKOSC_TABLICY; i++) {				// sprawdzanie pionu
		for (int j = 0; j < SZEROKOSC_TABLICY; j++) {
			if (tab[i][j] == gracze[obecny_gracz].token)
				znaki_w_linii++;
			else
				znaki_w_linii = 0;
			if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
				return 0;
		}
			znaki_w_linii = 0;
	}
	for (int i = 0; i < SZEROKOSC_TABLICY; i++) {				//sprawdzanie poziomu
		for (int j = 0; j < WYSOKOSC_TABLICY; j++) {
			if (tab[j][i] == gracze[obecny_gracz].token)
				znaki_w_linii++;
			else
				znaki_w_linii = 0;
			if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
				return 0;
		}
		znaki_w_linii = 0;
	}
	for (int i = 0,  j = 0; ((i < WYSOKOSC_TABLICY)&&(j < SZEROKOSC_TABLICY)); i++, j++) { // skos lewo-prawo
		
			if (tab[i][j] == gracze[obecny_gracz].token)
				znaki_w_linii++;
			else
				znaki_w_linii = 0;
			if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
				return 0;
	}
	for (int i = 1, j = 0; ((i < WYSOKOSC_TABLICY) && (j < SZEROKOSC_TABLICY)); i++, j++) {

		if (tab[i][j] == gracze[obecny_gracz].token)
			znaki_w_linii++;
		else
			znaki_w_linii = 0;
		if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
			return 0;
	}
	for (int i = 0, j = 1; ((i < WYSOKOSC_TABLICY) && (j < SZEROKOSC_TABLICY)); i++, j++) {

		if (tab[i][j] == gracze[obecny_gracz].token)
			znaki_w_linii++;
		else
			znaki_w_linii = 0;
		if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
			return 0;
	}
	for (int i = 0, j = 5; ((i < WYSOKOSC_TABLICY) && (j >= 0)); i++, j--) {		//skos prawo-lewo

		if (tab[i][j] == gracze[obecny_gracz].token)
			znaki_w_linii++;
		else
			znaki_w_linii = 0;
		if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
			return 0;
	}
	for (int i = 0, j = 4; ((i < WYSOKOSC_TABLICY) && (j >= 0)); i++, j--) {

		if (tab[i][j] == gracze[obecny_gracz].token)
			znaki_w_linii++;
		else
			znaki_w_linii = 0;
		if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
			return 0;
	}
	for (int i = 1, j = 5; ((i < WYSOKOSC_TABLICY) && (j >= 0)); i++, j--) {

		if (tab[i][j] == gracze[obecny_gracz].token)
			znaki_w_linii++;
		else
			znaki_w_linii = 0;
		if (znaki_w_linii == WARUNEK_ZWYCIEZCTWA_W_KIK)
			return 0;
	}
}
void zamiana_tokenow(char tab[][SZEROKOSC_TABLICY], Tgracz gracze[], int gracz) {
	char nowy_token;
	cin >> nowy_token;
	if (gracze[(gracz + 1) % 2].token == nowy_token) {
		cout << "Gracze nie moga miec tych samych tokenow" << endl;
		return;
	}
	if (gracze[(gracz + 1) % 2].token == ' ') {
		cout << "Nie mozesz ustawic takiego tokenu" << endl;
		return;
	}

	for (int i = 0; i < WYSOKOSC_TABLICY; i++) {
		for (int j = 0; j < SZEROKOSC_TABLICY; j++) {
			if (tab[i][j] == gracze[gracz].token)
				tab[i][j] = nowy_token;
		}
	}
	gracze[gracz].token = nowy_token;
}
void menu_kik(char tab[][SZEROKOSC_TABLICY], Tgracz gracze[], int gracz) {
	cout << "Aby otrzymac pomoc kliknij h." << endl << "Jesli chcesz zmienic token kliknij z." << endl << "Jesli chcesz zatrzymac gre kliknij p." << endl << "Jesli chcesz wczytaj przedefiniowana plansze kliknij o." << endl << "Jesli nie potrzebujesz chcesz uzyc zadnej z opcji wprowadz dowolny znak." << endl;
	char decyzja;
	string decyzje_antyblad;
	while (decyzje_antyblad.size() != 1) {
		cin >> decyzje_antyblad;
		cin.clear();
		cin.ignore(200, '\n');
		if (decyzje_antyblad.size() != 1) {
			cout << "Wprowadz jeden znak!" << endl;
		}
	}
	decyzja = decyzje_antyblad[0];
	if (decyzja == 'h') {
		cout << "Oto spis mozliwych komend dostepnych w grze kolko i krzyk." << endl << "q,w,a,s: komendy pozwalajace na wybor cwiartki planszy, na ktorej chcesz postawic token." << endl << "Odpowiednio lewa gorna, prawa gorna, lewa dolna, prawa dolna." << endl;
		cout << "1,2,...,9 to wybor pola znajdujacego sie na poprzednio wybranej cwiartce.Sa ona ponumerowane w taki sposob," << endl << "jak klawaitura numeryczna(1:lewy dolny rog)." << endl;
	}
	if (decyzja == 'z') {
		cout << "Wprowadz nowy token" <<endl;
		zamiana_tokenow(tab, gracze, gracz);
	}
	if (decyzja == 'p') {
		string dowolny_klawisz;
		system("cls");
		cout << "Wywolales pauze, aby wrocic do gry kliknij dowolny klawisz." << endl;
		cin >> dowolny_klawisz;
		plansza(tab,gracze);
	}
	if (decyzja == 'o'){								// ustawienie tablicy predefiniowanej
		tab[0][4] = gracze[GRACZ_PIERWSZY].token;
			tab[1][1] = gracze[GRACZ_PIERWSZY].token;
			tab[1][0] = gracze[GRACZ_PIERWSZY].token;
			tab[1][2] = gracze[GRACZ_PIERWSZY].token;
			tab[1][3] = gracze[GRACZ_PIERWSZY].token;
			tab[2][1] = gracze[GRACZ_PIERWSZY].token;
			tab[3][0] = gracze[GRACZ_PIERWSZY].token;
			tab[3][1] = gracze[GRACZ_PIERWSZY].token;
			tab[4][2] = gracze[GRACZ_PIERWSZY].token;
			tab[0][1] = gracze[GRACZ_DRUGI].token;
			tab[1][2] = gracze[GRACZ_DRUGI].token;
		tab[1][4] = gracze[GRACZ_DRUGI].token;
		tab[4][0] = gracze[GRACZ_DRUGI].token;
		tab[4][4] = gracze[GRACZ_DRUGI].token;
		tab[5][1] = gracze[GRACZ_DRUGI].token;
		tab[5][4] = gracze[GRACZ_DRUGI].token;
		tab[5][5] = gracze[GRACZ_DRUGI].token;
		plansza(tab, gracze);
	}
}
int wyznaczanie_numeru_wiersza_dla_podanego_pola(int pole, char cwiartka) {
	int wiersz = 0;
	if ((cwiartka == 'a') || (cwiartka == 's'))
		wiersz += 3;
	if (pole < 4)
		return wiersz + 2;
	if (pole < 7)
		return wiersz + 1;
	return wiersz;
}
int wyznaczanie_numeru_kolumny_dla_podanego_pola(int pole, char cwiartka) {
	int kolumna = 0;
	if ((cwiartka == 's') || (cwiartka == 'w'))
		kolumna += 3;
	if (pole % 3 == 1)
		return kolumna;
	if(pole%3==2)
		return kolumna+1;
	return kolumna + 2;
}
bool nowe_robienie_ruchu(char tab[][SZEROKOSC_TABLICY], Tgracz gracze[], int gracz) {
	char cwiartka;
	string cwiartka_antyblad;
	int pole;
	cout << "Podaj cwiartke, na ktorej chcesz postawic token. Q-lewa gorna, W-prawa gorna, A-lewa dolna, S-prawa dolna" << endl;
	cin >> cwiartka_antyblad;
	if (cwiartka_antyblad != "q" && cwiartka_antyblad != "w" && cwiartka_antyblad != "a" && cwiartka_antyblad != "s") {
		cout << "Podaj cwiartke, na ktorej chcesz postawic token. Q-lewa gorna, W-prawa gorna, A-lewa dolna, S-prawa dolna" << endl;
		cin >> cwiartka_antyblad;
		while (cwiartka_antyblad.size() != 1 || (cwiartka_antyblad != "q" && cwiartka_antyblad != "w" && cwiartka_antyblad != "a" && cwiartka_antyblad != "s")) {
			cout << "Podaj cwiartke, na ktorej chcesz postawic token. Q-lewa gorna, W-prawa gorna, A-lewa dolna, S-prawa dolna" << endl;
			cin >> cwiartka_antyblad;
			cin.clear();
			cin.ignore(200, '\n');
		}
	}
	cwiartka = cwiartka_antyblad[0];
	cout << "Podaj pole, na ktorym chcesz postwaic token" << endl;
	while (!(cin >> pole && pole >0 && pole<=9)) {
		cout << "Podaj pole, na ktorym chcesz postwaic token" << endl;
		cin.clear();
		cin.ignore(200, '\n');
	}
	int numer_wiersza = wyznaczanie_numeru_wiersza_dla_podanego_pola(pole, cwiartka);
	int numer_kolumny = wyznaczanie_numeru_kolumny_dla_podanego_pola(pole, cwiartka);
	if (pole > 0 && pole <= 9) {
		if (tab[numer_wiersza][numer_kolumny] == ' ')
			tab[numer_wiersza][numer_kolumny] = gracze[gracz].token;
		else
			return 0;
		return 1;
	}
	else {
		cout << "Podaj liczbe z przedzialu od 1 do 9.";
		return 0;
	}
	
}
int main()
{
	Tgracz gracze[LICZBA_GRACZY];
	char tab[WYSOKOSC_TABLICY][SZEROKOSC_TABLICY];
	wczytywanie_i_zapisywanie_imion_graczy(gracze); 
	system("cls");
	wybor_tokenu(gracze);
	for (int i = 0; i < WYSOKOSC_TABLICY; i++)
		for (int j = 0; j < SZEROKOSC_TABLICY; j++) // wypełnienie tablicy spacjami
			tab[i][j] = ' ';
	
	int obecny_gracz = GRACZ_PIERWSZY;
	while (czy_ktos_przegral(tab, obecny_gracz, gracze)) 
	{
		system("cls");
		plansza(tab, gracze);
		menu_kik(tab,gracze, obecny_gracz);
		cout << "Ruch gracza " <<gracze[obecny_gracz].imie << endl; 
		if (nowe_robienie_ruchu(tab, gracze, obecny_gracz))
			obecny_gracz++;
		obecny_gracz %= LICZBA_GRACZY;
	}
	cout << "Wygral gracz: " << gracze[(obecny_gracz+1)%2].imie;
}