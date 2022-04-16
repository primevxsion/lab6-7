#include "Service.h"
#include "List.h"
#include <assert.h>
#include <algorithm>

const Film FilmService::adaugaFilm(string titlu, string gen, int an, string actor) {
	Film filmDeAdaugat{ titlu, an, gen, actor };
	validator.valideaza(filmDeAdaugat);
	repo.adaugare(filmDeAdaugat);

	actiuniUndo.push_back(std::make_unique<UndoAdauga>(repo, filmDeAdaugat));

	return filmDeAdaugat;
}

const Film FilmService::modificaFilm(string titlu, string gen, int an, string titluNou, int anNou, string genNou, string actorNou){
	Film filmNou{ titluNou, anNou, genNou, actorNou };
	validator.valideaza(filmNou);

	Film filmDeModificat = repo.cautare(titlu, gen, an);
	int ind = repo.gasesteIndex(filmDeModificat);

	actiuniUndo.push_back(std::make_unique<UndoModifica>(repo, filmDeModificat, ind));

	return repo.modificare(ind, filmNou);
}

const Film FilmService::stergeFilm(string titlu, string gen, int an) {
	Film filmCautat = repo.cautare(titlu, gen, an);
	
	repo.stergere(filmCautat);

	actiuniUndo.push_back(std::make_unique<UndoSterge>(repo, filmCautat));

	return filmCautat;
}

const Film FilmService::cautaFilm(string titlu, string gen, int an) {
	return repo.cautare(titlu, gen, an);
}

const vector<Film> FilmService::filtrare(std::function<bool(const Film&)> fct){
	const vector<Film>& filme = repo.getAll();
	vector<Film> lstFil;	//lista care va contine Filmele filtrate

	std::copy_if(filme.begin(), filme.end(), std::back_inserter(lstFil), fct);
	
	return lstFil;
}

const vector<Film> FilmService::sortare(std::function<bool(const Film& film1, const Film& film2)> comp) {
	vector<Film> sortedLst = repo.getAll();	//initializam lista care trebuie sortata cu lista curenta
	std::sort(sortedLst.begin(), sortedLst.end(), comp);
	//sortedLst.sort(comp);
	return sortedLst;
}

void FilmService::genereazaCos(int nrF) {
	vector<Film>& cosFilme = getCos();

	if (!cosFilme.empty())
		throw CosException("Exista deja filme in cos.");

	if (nrF > repo.getAll().size())
		throw CosException("Nu sunt destule filme pentru generare.");

	cos.genereaza(nrF, repo);
}

void FilmService::golesteCos() {
	vector<Film>& cosFilme = getCos();
	
	if (cosFilme.empty())
		throw CosException("Cosul este deja gol");
	
	cos.goleste();
}

void FilmService::exportaCos(string numeFisier) {
	cos.exportaCos(numeFisier);
}

int FilmService::numaraFilme(std::function<bool(const Film& film)> cond) {
	const vector<Film>& filme = getAll();
	return (int)std::count_if(filme.begin(), filme.end(), cond);
}

void FilmService::undo() {
	if (actiuniUndo.empty())
		throw RepoException("Nu mai exista operatii!");

	actiuniUndo.back()->doUndo();
	actiuniUndo.pop_back();
}

void testService() {
	FilmRepo filmRepo;
	FilmValidator filmVal;
	Cos cos;
	FilmService filmServ{ filmRepo, filmVal, cos };

	filmServ.adaugaFilm("lucha", "comedie", 2019, "westside");
	try {
		filmServ.adaugaFilm("lucha", "comedie", 2019, "westside");
	}
	catch (RepoException&) {}

	filmServ.cautaFilm("lucha", "comedie", 2019);
	filmServ.modificaFilm("lucha", "comedie", 2019, "lucha bros", 2020, "comedie", "westside");
	assert(filmServ.cautaFilm("lucha bros", "comedie", 2020).getAn() == 2020);
	filmServ.stergeFilm("lucha bros", "comedie", 2020);
	assert(filmServ.getAll().size() == 0);

	filmServ.adaugaFilm("500", "comedie", 2020, "tyson");
	filmServ.adaugaFilm("tyson", "rap", 2000, "tyson");
	filmServ.adaugaFilm("benny", "rap", 2000, "benny");
	vector<Film> filt;
	filt = filmServ.filtrare([](const Film& film1) {return film1.getAn() == 2000; });
	assert(filt[0].getAn() == 2000);
	assert(filt.size() == 2);

	vector<Film> lstSort = filmServ.sortare(cmpGen);
	assert(lstSort[0].getAn() == 2020);
	assert(lstSort[0].getGen() == "comedie");

	filmServ.genereazaCos(2);
	filmServ.golesteCos();
	filmServ.exportaCos("fisier.txt");

	assert(filmServ.numaraFilme([](const Film& film) {return film.getAn() == 2000; }) == 2);

	filmServ.adaugaCos(Film{ "conway", 1999, "rap", "conway" });
	try {
		filmServ.genereazaCos(2);
	}
	catch (CosException& e) {
		e.getErrorMessages();
	}
	filmServ.golesteCos();

	try {
		filmServ.golesteCos();
	}
	catch (CosException&) {}

	try {
		filmServ.genereazaCos(100);
	}
	catch (CosException&) {}
}