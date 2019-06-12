#include <iostream>
#include <iomanip>

using namespace std;

enum Gracz
{
	komputer = 'X',
	czlowiek = 'O',
	nikt = '0'
};

struct Ruch
{
	int wiersz;
	int kolumna;
};

class Plansza
{

	Gracz ** plansza;
	int rozmiar_Planszy;
	int rzad_Planszy;

public:
	Plansza(int rozmiar, int rzad);
	
	void wyswietlKomorke(int wiersz, int kolumna);
	void rysuj();
	bool remis();
	bool wygrana(Gracz gracz);
	int maxSzukaj(int poziom);
	int minSzukaj(int poziom);
	Ruch minimax();
	void rozgrywka();
	~Plansza();
};