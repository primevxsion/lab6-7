#pragma once
#include "Film.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Film filmAdaugat;
	FilmRepo& repo;

public:
	UndoAdauga(FilmRepo& repo, Film& film) : repo{ repo }, filmAdaugat{ film } {}

	void doUndo() override {
		repo.stergere(filmAdaugat);
	}
};

class UndoSterge : public ActiuneUndo {
	Film filmSters;
	FilmRepo& repo;

public:
	UndoSterge(FilmRepo& repo, Film& film) : repo{ repo }, filmSters{ film } {}

	void doUndo() override {
		repo.adaugare(filmSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Film filmModificat;
	int indice;
	FilmRepo& repo;

public:
	UndoModifica(FilmRepo& repo, Film& film, int indice) : repo{ repo }, filmModificat{ film }, indice{ indice } {}

	void doUndo() override {
		repo.modificare(indice, filmModificat);
	}
};