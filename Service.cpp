#include "Service.h"
#include <assert.h>

const Film FilmService::adaugaFilm(string titlu, string gen, int an, string actor) {
	Film filmDeAdaugat{ titlu, an, gen, actor };
	validator.valideaza(filmDeAdaugat);
	repo.adaugare(filmDeAdaugat);
	return filmDeAdaugat;
}

const Film FilmService::modificaFilm(string titlu, string gen, int an, string titluNou, int anNou, string genNou, string actorNou){
	Film filmNou{ titluNou, anNou, genNou, actorNou };
	validator.valideaza(filmNou);

	Film filmDeModificat = repo.cautare(titlu, gen, an);
	int ind = repo.gasesteIndex(filmDeModificat);

	return repo.modificare(ind, filmNou);
}

const Film FilmService::stergeFilm(string titlu, string gen, int an) {
	Film filmCautat = repo.cautare(titlu, gen, an);
	
	repo.stergere(filmCautat);

	return filmCautat;
}

const Film FilmService::cautaFilm(string titlu, string gen, int an) {
	return repo.cautare(titlu, gen, an);
}

const List<Film> FilmService::filtrare(std::function<bool(const Film&)> fct){
	List<Film> lstFil;
	const List<Film>& filme = repo.getAll();

	for (int i = 0; i < filme.size(); ++i)
		if (fct(filme[i]))
			lstFil.push_back(filme[i]);

	return lstFil;
}

void testService() {
	FilmRepo filmRepo;
	FilmValidator filmVal;
	FilmService filmServ{ filmRepo, filmVal };

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

	filmServ.adaugaFilm("benny", "rap", 2000, "benny");
	filmServ.adaugaFilm("tyson", "rap", 2000, "tyson");
	List<Film> filt = filmServ.filtrare([](const Film& film1) {return film1.getAn() == 2000; });
	assert(filt[0].getAn() == 2000);
}