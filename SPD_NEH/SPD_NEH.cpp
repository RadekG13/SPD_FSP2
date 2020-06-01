#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;


int liczba;
int maszyny;
vector<vector<int>> tab;


void Wczytaj(string Nazwapliku) {
	string linia;
	fstream plik;

	plik.open(Nazwapliku, ios::in);
	if (plik.good() == true)
	{
		plik >> linia;
		plik >> liczba;
		plik >> maszyny;
		string pomoc1, pomoc2;

		for (int i = 0; i < liczba; i++)
		{
			int tmp;

			vector<int> v1;
			v1.push_back(i); // Wrzucamy jaka to kolejnosc
			for (int j = 0; j < maszyny; j++)
			{
				plik >> pomoc1 >> tmp;
				v1.push_back(tmp);

			}
			tab.push_back(v1);

		}
		plik.close();
	}
}

int cmax(vector<vector<int>> tabela)
{
	int Cstart = 0;
	int Cend = 0;
	vector<vector<int>> StartL(tabela.size(),vector<int>(tabela[0].size()));
	vector<vector<int>> EndL(tabela.size(), vector<int>(tabela[0].size()));
	for (int i = 0; i < tabela.size(); i++)
	{
		for (int j = 0; j < tabela[0].size(); j++)
		{
			if (i == 0)
			{
				Cstart = Cend;
				Cend = Cstart + tabela[i][j];
			}
			else
			{
				if (j == 0)
					Cstart = EndL[i - 1][j];
				else
					Cstart = max(EndL[i - 1][j], Cend);
				Cend = Cstart + tabela[i][j];
			}
			StartL[i][j] = Cstart;
			EndL[i][j] = Cend;
			//cout << Cend << endl;
		}
	}
	return EndL[tabela.size() - 1][tabela[0].size() - 1];
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int Annealing(vector<vector<int>> tabela) {
	double T = 1000;
	int i, j, cmax_tmp, cmax_start;
	double r, error, diff;
	int L = liczba;
	int x = T / 1000;
	int a = 0.95;
	int Tend = 0;
	cmax_start = cmax(tabela);
	while (T > Tend) {
		for (int k = 1; k < L; k++) {
			i = rand() % liczba;
			j = rand() % liczba;
			
			swap(tabela[i], tabela[j]);
			cmax_tmp = cmax(tabela);
			if (cmax_tmp > cmax_start) {
				r = fRand(0, 1);
				diff = cmax_start - cmax_tmp;
				double podziel = diff / T;
				error = exp(podziel);
				//cout << error << endl;
				if (r >= error) swap(tabela[i], tabela[j]);

			}
		
		}
		
		T = a*T;
	}

	return cmax_tmp;
}

int Annealing_2(vector<vector<int>> tabela) {
	double T = 1000;
	int i, j, cmax_tmp, cmax_start;
	double r, error, diff;
	int L = liczba;
	int x = T / 1000;
	int a = 0.9;
	int Tend = 0;
	cmax_start = cmax(tabela);
	while (T > Tend) {
		for (int k = 1; k < L; k++) {
			i = rand() % liczba;
			j = rand() % liczba;

			swap(tabela[i], tabela[j]);
			cmax_tmp = cmax(tabela);
			if (cmax_tmp > cmax_start) {
				r = fRand(0, 1);
				diff = cmax_start - cmax_tmp;
				double podziel = diff / T;
				error = exp(podziel);
				//cout << error << endl;
				if (r >= error) swap(tabela[i], tabela[j]);

			}

		}

		T = T - x;
	}

	return cmax_tmp;
}
int Annealing_3(vector<vector<int>> tabela) {
	double T = 100;
	int i, j, cmax_tmp, cmax_start;
	double r, error, diff;
	int L = sqrt(liczba);
	int x = T / 100;
	int a = 0.9;
	int Tend = 0;
	cmax_start = cmax(tabela);
	while (T > Tend) {
		for (int k = 1; k < L; k++) {
			i = rand() % liczba;
			j = rand() % liczba;

			swap(tabela[i], tabela[j]);
			cmax_tmp = cmax(tabela);
			if (cmax_tmp > cmax_start) {
				r = fRand(0, 1);
				diff = cmax_start - cmax_tmp;
				double podziel = diff / T;
				error = exp(podziel);
				//cout << error << endl;
				if (r >= error) swap(tabela[i], tabela[j]);

			}

		}

		T = T - x;
	}

	return cmax_tmp;
}
int NEH(vector<vector<int>> tabela)
{
	int wynik1 = 0;
	int wynik2 = 0;
	int zmiana;
	do {
		zmiana = 0;
		for (int i = 0; i < tabela.size() - 1; i++)
		{
			wynik1 = 0;
			wynik2 = 0;
			for (int j = 0; j < maszyny; j++)
			{
				wynik1 += tabela[i][j];
				wynik2 += tabela[i + 1][j];
			}
			if (wynik1 < wynik2)
			{
				swap(tabela[i], tabela[i + 1]);
				zmiana = 1;
			}
		}
	} while (zmiana != 0);
	

	vector<vector<int>> Pi(maszyny);
	vector<vector<int>> Pi2;
	int k = 0;

	while (tabela.size() != 0)
	{
		vector<int> j;
		j = tabela[0];
		

		for (int i = 0; i < j.size(); i++)
		{
			Pi[i].push_back(j[i]);
		}
		Pi2 = Pi;


		for (int l = 0; l < k; l++)
		{

			if (k > 0)
			{
				for (int i = 0; i < j.size(); i++)
				{
					
					swap(Pi2[i][k - l], Pi2[i][k - l - 1]);

				}
				
			}
			if (cmax(Pi2) <= cmax(Pi))
				Pi = Pi2;
		}



		k = k + 1;
		tabela.erase(tabela.begin());
	}
	
	return cmax(Pi);
}


int main()
{
	
		Wczytaj("ta085.txt");
		for (int i = 0; i < tab.size(); i++)
			tab[i].erase(tab[i].begin());	//usuwamy liczbe porzadkowa zadan

		auto start = std::chrono::system_clock::now();
		int wynik2 = Annealing_2(tab);
		cout << "Wyzarzanie liniowe:" << wynik2 << endl;
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> cz = end - start;
		cout << "Czas wykonywania wyrzazania liniowego " << cz.count() << endl;

		auto start4 = std::chrono::system_clock::now();
		int wynik4 = Annealing_3(tab);
		cout << "Wyzarzanie liniowe II wer:" << wynik4 << endl;
		auto end4 = std::chrono::system_clock::now();
		std::chrono::duration<double> cz4 = end4 - start4;
		cout << "Czas wykonywania wyrzazania liniowego II wer " << cz4.count() << endl;
		auto start2 = std::chrono::system_clock::now();

		int wynik3 = Annealing(tab);
		cout << "Wyzarzanie geometryczne:" << wynik3 << endl;
		auto end2 = std::chrono::system_clock::now();
		std::chrono::duration<double> cz2 = end2 - start2;
		cout << "Czas wykonywania wyrzazania geometrycznego " << cz2.count() << endl;
		
		auto start3 = std::chrono::system_clock::now();
		int wynik = NEH(tab);//cmax(Pi);
		auto end3 = std::chrono::system_clock::now();
		std::chrono::duration<double> cz3 = end3 - start3;
		cout << "Czas wykonywania neha" << cz3.count() << endl;
		cout <<"NEH:" << wynik << endl;
	
}

