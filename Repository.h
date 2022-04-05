#pragma once
#include "Film.h"
#include "List.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;

class FilmRepo {
	List<Film> filme;

public:
	FilmRepo() = default;

	//distrugem constructorul de copiere
	FilmRepo(const FilmRepo& alt) = delete;

	/*
	* Adauga filmul dat in repo
	* Arunca exceptie daca exista deja un film cu acelasi titlu, gen si an al aparitiei
	*/
	void adaugare(const Film& film);

	/*
	* Modifica filmul dat in noul film
	* Arunca exceptie daca nu exista filmul dat
	*/
	const Film modificare(int ind, Film filmNou);

	/*
	* Cauta filmul dupa titlu, gen si anul aparitiei
	* Arunca exceptie daca nu se gaseste
	*/
	const Film cautare(string titlu, string gen, int an) const;

	/*
	* Returneaza indicele filmului cautat in lista de filme
	* Returneaza -1 daca filmul nu se gaseste
	*/
	int gasesteIndex(const Film& filmCautat);

	/*
	* Sterge filmul cautat din lista
	* Returneaza filmul cautat daca in gaseste
	*/
	const Film stergere(const Film filmDeSters);

	//returneaza o lista cu toate filmele
	const List<Film>& getAll() const noexcept;
};

class RepoException {
	vector<string> errorMsg;

public:
	RepoException(vector <string> errorMessages) :errorMsg{errorMessages} {}

	RepoException(string error) {
		vector<string> errors;
		errors.push_back(error);
		errorMsg = errors;
	}

	string getErrorMessages() {
		string fullMsg = "\n";
		for (const string s : errorMsg)
			fullMsg += s + '\n';
		return fullMsg;
	}
};

void testRepo();