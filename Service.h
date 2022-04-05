#pragma once
#include "Repository.h"
#include "Validators.h"
#include "List.h"
#include <string.h>
#include <functional>

class FilmService {
private:
	FilmRepo& repo;
	FilmValidator& validator;

public:
	FilmService(FilmRepo& repo, FilmValidator& validator) : repo{ repo }, validator{ validator }{}

	//stergem constructorul de copiere
	FilmService(const FilmService& ot) = delete;

	const Film adaugaFilm(string titlu, string gen, int an, string actor);

	const Film modificaFilm(string titlu, string gen, int an, string titluNou, int anNou, string genNou, string actorNou);

	const Film stergeFilm(string titlu, string gen, int an);

	const Film cautaFilm(string titlu, string gen, int an);

	const List<Film> filtrare(std::function<bool(const Film&)> fct);

	const List<Film>& getAll() {
		return repo.getAll();
	}
};

void testService();