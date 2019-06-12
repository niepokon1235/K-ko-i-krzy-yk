#include "Plansza.h"

/*Implementacja Planszy*/
/*Algorytm pobiera rozmiar, oraz rzad wygrywajacy*/
/*Tworzy nowa macierz 2 wymiarowa oraz uzupelnia ja pustym polem*/
Plansza::Plansza(int rozmiar, int rzad)
{
	rozmiar_Planszy = rozmiar;
	rzad_Planszy = rzad;
	plansza = new Gracz *[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		plansza[i] = new Gracz[rozmiar];

		for (int j = 0; j < rozmiar; j++)
		{
			plansza[i][j] = Gracz::nikt;
		}
	}
}

/*Funkcja zamienia wartosc enum na X- pionek komputera*/
/*O - pionek gracza, oraz puste pole*/
void Plansza::wyswietlKomorke(int wiersz, int kolumna)
{
	if (plansza[wiersz][kolumna] == komputer) cout << "X";
	else if (plansza[wiersz][kolumna] == czlowiek) cout << "O";
	else if (plansza[wiersz][kolumna] == nikt) cout << " ";
}

/*Funkcja wsywietla plansze, oraz stosowne opisy*/
void Plansza::rysuj()
{
	system("cls");
	int zmienna = 0;
	int pomocnik = 0;
	cout << "Kolko i krzyzyk" << endl;
	cout << "Rozmiar planszy: " << rozmiar_Planszy << "x" << rozmiar_Planszy << "." << endl;
	cout << "Trzeba ulozyc: " << rzad_Planszy << " w rzedzie." << endl << endl;

	for (int j = 0; j < rozmiar_Planszy; j++)
	{
		cout << "    ";
		for (int i = 0; i < rozmiar_Planszy - 1; i++)
		{
			wyswietlKomorke(pomocnik,i);
			cout << " | ";
		}

		wyswietlKomorke(pomocnik, rozmiar_Planszy - 1);
		cout << " " << endl;

		if (zmienna < rozmiar_Planszy - 1)
		{
			cout << "   ---";
			for (int k = 0; k < rozmiar_Planszy - 1; k++)
			{
				cout << "|---";
			}
			cout << endl;
			zmienna += 1;
		}
		pomocnik += 1;
	}
	cout << endl;
}

/*Funkcja sprawdza pokolei wartoœæ planszy*/
/*Je¿eli w ¿adnej nie ma gracza albo komputera to wynikiem rozgrywki jest remis*/
bool Plansza::remis()
{
	for (int i = 0; i < rozmiar_Planszy; i++)
	{
		for (int j = 0; j < rozmiar_Planszy; j++)
		{
			if (plansza[i][j] == Gracz::nikt)
				return false;
		}
	}
	return true;
}

/*Funkcja pobiera gracza - komputer lub u¿ytkownik*/
/*Sprawdza rzêdy macierzy i zwraca true je¿eli jeden z graczy wygra³*/
bool Plansza::wygrana(Gracz gracz)
{
	/*Liczniki u¿ywane do porównania sytuacji na planszy z wymaganym rzêdem*/
	int pomocx = 0;
	int pomocy = 0;

	/*Sprawdza poziom oraz pion*/
	/*Pomocnik zmienia siê po sprawdzeniu poziomu i pionu*/
	for (int pomocnik = 0; pomocnik < rozmiar_Planszy; pomocnik++)
	{
		/*Wprowadzone na wypadek gdyby rzad by³ mniejszy ni¿ rozmiar planszy*/
		for (int j = 0; j < (rozmiar_Planszy - rzad_Planszy + 1); j++)
		{
			int i = j;
			for (i; i < rzad_Planszy; i++)
			{
				if (plansza[pomocnik][i] == gracz) pomocx += 1;
				if (plansza[i][pomocnik] == gracz) pomocy += 1;

				if (pomocx == rzad_Planszy || pomocy == rzad_Planszy)
				{
					return true;
				}
			}
			/*Zeruje je¿eli nie znajdzie rzedu w linii*/
			pomocx = 0;
			pomocy = 0;
		}
	}

	/*Liczniki przekatnych*/
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;
	int p5 = 0;
	int p6 = 0;

	int i, j, l, m;
	/*Sprawdza pierwsza przek¹tna \ mniejsza od gory i mniejsza od dolu*/
	/*pomocnik w celu zachowania wzglêdnie sta³ej wartoœci na i, taki punkt odniesienia j równie¿*/
	for (int pomocnik = 0; pomocnik < (rozmiar_Planszy - rzad_Planszy + 1); pomocnik++)
	{
		/*j w celu */
		j = rozmiar_Planszy - rzad_Planszy;
		i = pomocnik;
		for (i; i < (rzad_Planszy + pomocnik); i++)
		{
			if (plansza[i][i] == gracz) p1 += 1;
			if (plansza[i][j] == gracz) p2 += 1;
			if (plansza[j][i] == gracz) p3 += 1;

			if (p3 == rzad_Planszy || p2 == rzad_Planszy || p1 == rzad_Planszy)
			{
				return true;
			}
			j += 1;
		}
		p1 = 0;
		p2 = 0;
		p3 = 0;
		/*Sprawdzenie duzej przekatnej /*/
		for (int k = rozmiar_Planszy - 1 - pomocnik; k >= 0; k--)
		{
			l = rozmiar_Planszy - 1 - k;
			if (plansza[l][k] == gracz) p4 += 1;

			if (p4 == rzad_Planszy)
			{
				return true;
			}

			if (k == rozmiar_Planszy - rzad_Planszy)
			{
				p4 = 0;
			}
		}
		/*Sprawdzenie mniejszych przekatnych przy /*/
		for (int k = rozmiar_Planszy - 2; k >= 0; k--)
		{
			m = rozmiar_Planszy - 2 - k;
			if (plansza[m][k] == gracz) p5 += 1;
			if (plansza[m + 1][k + 1] == gracz) p6 += 1;

			if (p5 == rzad_Planszy || p6 == rzad_Planszy)
			{
				return true;
			}
		}
		p5 = 0;
		p6 = 0;
	}
	return false;
}

/*Algorytm minimax zwraca wspolrzedne nastepnego ruchu komputera*/
Ruch Plansza::minimax()
{
	/*Wartosc s³u¿y jako infinity do porównywania*/
	int wartosc = 1000;
	Ruch ruch;

	/*Wszystkie elementy tablicy, jezeli element jest pusty to podstaw komputer*/
	for (int i = 0; i < rozmiar_Planszy; i++)
	{
		for (int j = 0; j < rozmiar_Planszy; j++)
		{
			if (plansza[i][j] == Gracz::nikt)
			{
				plansza[i][j] = Gracz::komputer;

				/*podstawia najwieksza wartosc*/
				int pomocnik = maxSzukaj(0);

				if (pomocnik < wartosc)
				{
					wartosc = pomocnik;
					ruch.wiersz = i;
					ruch.kolumna = j;
				}
				/*Zamienia znowu komputer na pusty*/
				plansza[i][j] = Gracz::nikt;
			}
		}
	}
	/*Zwraca ruch*/
	return ruch;
}

/*Algorytm s³u¿y do znajdywania najwieszkej z najwieksza szansa wygranej wartosci*/
int Plansza::maxSzukaj(int poziom)
{
	/*Sprawdza sytuacje na planszy, czy wygrywa komputer, czlowiek remis i podstawia wartosci*/
	/*Maksymalizuje gracza i minimalizuje komputer*/
	if (wygrana(Gracz::czlowiek)) { return 10; }
	else if (wygrana(Gracz::komputer)) { return -10; }
	else if (remis()) { return 0; }

	/*Wartoœæ do porównania*/
	int wartosc = 0;

	for (int i = 0; i < rozmiar_Planszy; i++)
	{
		for (int j = 0; j < rozmiar_Planszy; j++)
		{
			/*Sprawdza czy puste*/
			if (plansza[i][j] == Gracz::nikt)
			{
				/*Podstawia czlowieka*/
				/*maksymalizuje wartosci*/
				plansza[i][j] = Gracz::czlowiek;
				if (wartosc > minSzukaj(poziom + 1) - poziom) wartosc = wartosc;
				else wartosc = minSzukaj(poziom + 1) - poziom;
				/*Na koncu wraca do stanu pustego*/
				plansza[i][j] = Gracz::nikt;
			}
		}
	}
	/*Zwraca maksymalna wartosc*/
	return wartosc;
}

/*Algorytm s³u¿y do znajdowania najmniejszej szansy wartosci*/
int Plansza::minSzukaj(int poziom)
{
	/*Sprawdza sytuacje na planszy, czy wygrywa komputer, czlowiek remis i podstawia wartosci*/
	/*Maksymalizuje gracza i minimalizuje komputer*/
	if (wygrana(Gracz::czlowiek)) { return 10; }
	else if (wygrana(Gracz::komputer)) { return -10; }
	else if (remis()) { return 0; }

	/*Wartosc do porownania sluzy jako infinity*/
	int wartosc = 1000;

	for (int i = 0; i < rozmiar_Planszy; i++)
	{
		for (int j = 0; j < rozmiar_Planszy; j++)
		{
			/*Jezeli element pusty*/
			if (plansza[i][j] == Gracz::nikt)
			{
				/*Podklada komputer szuka najmniejszej wartosci*/
				plansza[i][j] = Gracz::komputer;
				if (wartosc > maxSzukaj(poziom + 1) + poziom) wartosc = maxSzukaj(poziom + 1) + 1;
				else wartosc = wartosc;
				/*Wraca do element do wartosci pusty*/
				plansza[i][j] = Gracz::nikt;
			}
		}
	}
	/*Zwraca najmniejsza wartosc*/
	return wartosc;
}

/*Algorytm s³u¿y do przeprowadzenia ruchów, wyœwietla */
void Plansza::rozgrywka()
{
	int numer_Ruchu;
	int wiersz, kolumna;

	system("cls");
	cout << endl;
	cout << "   Kto zaczyna?   " << endl;
	cout << "   0 gracz   " << endl;
	cout << "   1 komputer   " << endl;
	cin >> numer_Ruchu;

	rysuj();
	while (1)
	{
		if ((numer_Ruchu % 2) == 0)
		{
			cout << "Twoj ruch" << endl;;
			cout << "Podaj wiersz i kolumne: ";
			cin >> wiersz >> kolumna;

			if ((wiersz - 1 < rozmiar_Planszy) && (kolumna - 1 < rozmiar_Planszy) && plansza[wiersz - 1][kolumna - 1] == Gracz::nikt)
			{
				plansza[wiersz - 1][kolumna - 1] = Gracz::czlowiek;
				numer_Ruchu += 1;

				if (wygrana(Gracz::czlowiek))
				{
					rysuj();
					cout << "Wygrales" << endl;
					break;
				}
			}
			else
			{
				cout << "Bledny ruch" << endl;
				numer_Ruchu -= 2;
			}
		}

		else if ((numer_Ruchu % 2) == 1)
		{
			
			Ruch komputer = minimax();
			plansza[komputer.wiersz][komputer.kolumna] = Gracz::komputer;
			numer_Ruchu += 1;

			if (wygrana(Gracz::komputer))
			{
				rysuj();
				cout << "Wygral komputer" << endl;
				break;
			}
		}

		if (remis())
		{
			rysuj();
			cout << "Remis" << endl;
			break;
		}
		rysuj();
	}
}

Plansza::~Plansza()
{
	for (int i = 0; i < rozmiar_Planszy; i++) delete[] plansza[i];
	delete[] plansza;
}