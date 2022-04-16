#include "Repository.h"
#include <assert.h>
#include <algorithm>

void FilmRepo::adaugare(const Film& film) {
	if (gasesteIndex(film) != -1)
		throw RepoException("Filmul exista deja in lista!");

	filme.push_back(film);
}

const vector<Film>& FilmRepo::getAll() const noexcept {
	return filme;
}

const Film FilmRepo::cautare(string titlu, string gen, int an) const {
	auto it = find_if(filme.begin(), filme.end(), [=](const Film& film) {return film.getTitlu() == titlu && film.getAn() == an && film.getGen() == gen; });
	
	if(it == filme.end())
		throw RepoException("Filmul cautat nu exista.");

	return *it;
}

const Film FilmRepo::modificare(int ind, Film filmNou) {
	filme[ind] = filmNou;
	return filmNou;
	//return filme.modify(ind, filmNou); //LDI
}

int FilmRepo::gasesteIndex(const Film& filmCautat) {
	auto it = std::find_if(filme.begin(), filme.end(), [&](const Film& film) {return film == filmCautat; });
	if (it == filme.end())
		return -1;
	
	return (int) (it - filme.begin());
}

const Film FilmRepo::stergere(const Film filmDeSters) {
	int index = gasesteIndex(filmDeSters);
	//filme.remove(index);
	filme.erase(filme.begin() + index);
	return filmDeSters;
}

void testRepo() {
	FilmRepo repoTest;

	repoTest.adaugare(Film("benny", 1920, "comedie", "benny"));
	assert(repoTest.gasesteIndex(Film("benny", 1920, "comedie", "benny")) == 0);
	repoTest.modificare(0, Film("tyson", 1999, "documentary", "tyson"));
	assert(repoTest.gasesteIndex(Film{ "tyson", 1999, "documentary", "tyson" }) == 0);
	try {
		repoTest.adaugare(Film{ "tyson", 1999, "documentary", "tyson" });
	}
	catch (RepoException& r) {
		r.getErrorMessages();
		assert(true);
	}
	repoTest.stergere(Film{ "tyson", 1999, "documentary", "tyson" });
	Film film1{ "Parasite", 2019, "thriller", "Song Kang" };
	Film film2{ "Roma", 2018, "history", "Cuaron"};
	Film film3{ "The Lion King", 2019, "animation", "Donald Glover"};
	repoTest.adaugare(film1);
	repoTest.adaugare(film2);
	repoTest.adaugare(film3);
	repoTest.stergere(film2);
	assert(repoTest.cautare("The Lion King", "animation", 2019) == film3);
	repoTest.stergere(film3);
	repoTest.stergere(film1);
	repoTest.adaugare(film1);
	try {
		repoTest.adaugare(film1);
	}
	catch (RepoException& r) {
		r.getErrorMessages();
		assert(true);
	}
	try {
		repoTest.cautare("nas", "istorie", 1992);
	}
	catch (RepoException&) {}
	vector<Film> lista = repoTest.getAll();

}