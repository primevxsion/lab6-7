#pragma once
#include "Repository.h"
#include "Validators.h"
#include "List.h"
#include <string.h>
#include <functional>
#include "Cos.h"

class FilmService {
private:
	FilmRepo& repo;
	FilmValidator& validator;
	Cos& cos;

public:
	FilmService(FilmRepo& repo, FilmValidator& validator, Cos& cos) : repo{ repo }, validator{ validator }, cos{cos}{}

	//stergem constructorul de copiere
	FilmService(const FilmService& ot) = delete;

	const Film adaugaFilm(string titlu, string gen, int an, string actor);

	const Film modificaFilm(string titlu, string gen, int an, string titluNou, int anNou, string genNou, string actorNou);

	const Film stergeFilm(string titlu, string gen, int an);

	const Film cautaFilm(string titlu, string gen, int an);

	const vector<Film> filtrare(std::function<bool(const Film&)> fct);

	const vector<Film> sortare(std::function<bool(const Film& film1, const Film& film2)> comp);

	const vector<Film>& getAll() {
		return repo.getAll();
	}

	vector<Film>& getCos() {
		return cos.getCos();
	}

	int numaraFilme(std::function<bool(const Film& film)> cond);

	void adaugaCos(const Film& film) {
		cos.adauga(film);
	}

	void genereazaCos(int nrF);

	void golesteCos();

	void exportaCos(string numeFisier);
};

void testService();