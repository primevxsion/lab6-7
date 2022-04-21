#include "Cos.h"
#include <vector>
#include <algorithm>
#include <exception>
#include <random>
#include <fstream>

void Cos::goleste() {
	cosFilme.clear();
}

void Cos::adauga(const Film& film) {
	cosFilme.push_back(film);
}

void Cos::genereaza(int nrFilme, Repo& repo) {
	vector<Film> filme = repo.getAll();	//cos e friend class pentru FilmRepo
	int size = (int) filme.size();
	
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, size - 1);
	vector<bool> folosit(size);
	int rndInd{ 0 };

	while (cosFilme.size() < nrFilme) {
		do {
			rndInd = dist(mt); //numar aleator intre [0,size-1]
		} 
		while (folosit[rndInd]); //generam noi indici pana cand gasim unul nefolosit
		
		folosit[rndInd] = true;

		cosFilme.push_back(filme[rndInd]);
	}
}

void Cos::exportaCos(string numeFisier) {
	std::ofstream fout(numeFisier);
	for (auto& film : cosFilme)
		fout << film.getTitlu() << ":" << film.getGen() << ":" << film.getAn() << ":" << film.getActor() << std::endl;
	fout.close();
}

void testeCos() {
	Cos cos{};
	Film film1{ "Parasite", 2019, "thriller", "Song Kang" };
	Film film2{ "Roma", 2018, "history", "Cuaron" };
	Film film3{ "The Lion King", 2019, "animation", "Donald Glover" };
	FilmRepo repo;
	repo.adaugare(film1);
	repo.adaugare(film2);
	repo.adaugare(film3);

	cos.genereaza(2, repo);
	assert(cos.getCos().size() == 2);
	cos.goleste();

	cos.adauga(film1);
	cos.adauga(film2);
	cos.adauga(film3);

	cos.exportaCos("fisier.txt");
}