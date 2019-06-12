#include <iostream>
#include "Plansza.h"

using namespace std;

int main()
{
	int rozmiar, rzad;
	cout << "Podaj rozmiar planszy: ";
	cin >> rozmiar;
	system("cls");
	cout << "Podaj rzad planszy: ";
	cin >> rzad;

	if (rozmiar < rzad)
	{
		system("cls");
		cout << "Podales bledna dana, rzad nie moze byc wiekszy niz rozmiar" << endl;
		cout << "Podaj rzad planszy: ";
		cin >> rzad;
	}

	Plansza item(rozmiar,rzad);
	item.rozgrywka();

	system("pause");
	return 0;
}