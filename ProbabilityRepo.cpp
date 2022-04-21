#include "Repository.h"

void ProbRepo::pass() const{
	/*std::mt19937 gen(123);
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	double f = dis(gen);*/
	double r = ((double)rand() / (RAND_MAX));
	if (r > prob)
		throw(RepoException("Nu se poate executa functia. Mai incearca o data!"));
}

void ProbRepo::adaugare(const Film& film) {
	pass();
	if (gasesteIndex(film) != -1)
		throw RepoException("Filmul exista deja in lista!");

	int index = (int)filme.size();
	filme[index] = film;	
}

const vector<Film>& ProbRepo::getAll() noexcept {
	pass();
	for (auto &v : filme) {
		filmeV.push_back(v.second);
	}
	
	return filmeV;
}

const Film ProbRepo::cautare(string titlu, string gen, int an) const {
	pass();
	auto it = find_if(filme.begin(), filme.end(), [=](const std::pair<int, Film> film) {return film.second.getTitlu() == titlu && film.second.getAn() == an && film.second.getGen() == gen; });

	if (it == filme.end())
		throw RepoException("Filmul cautat nu exista.");

	return  (*it).second;
}

const Film ProbRepo::modificare(int ind, Film filmNou) {
	pass();
	filme[ind] = filmNou;
	return filmNou;
	//return filme.modify(ind, filmNou); //LDI
}

int ProbRepo::gasesteIndex(const Film& filmCautat) {
	pass();
	for (int i = 0; i < filme.size(); ++i) {
		if (filme[i] == filmCautat)
			return i;
	}

	return -1;
}

const Film ProbRepo::stergere(const Film filmDeSters) {
	pass();
	int i = gasesteIndex(filmDeSters);
	for(int j = i; j < filme.size() - 1; ++j){
		filme[j] = filme[j + 1];
	}

	filme.erase((int)filme.size() - 1);
	return filmDeSters;
	//filme.remove(index);
}

void ProbRepo::setProb(double f) {
	prob = f;
}

void testProb() {
	ProbRepo repoTest;
	repoTest.setProb(0);
	try {
		repoTest.adaugare(Film("benny", 1920, "comedie", "benny"));
	}
	catch (RepoException& r) {
		r.getErrorMessages();
	}
	repoTest.setProb(1);

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
	Film film2{ "Roma", 2018, "history", "Cuaron" };
	Film film3{ "The Lion King", 2019, "animation", "Donald Glover" };
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