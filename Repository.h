#pragma once
#include "Film.h"
#include "List.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <ostream>
#include <random>

using std::vector;
using std::string;

class Repo {
public:
	Repo() = default;

	//distrugem constructorul de copiere
	Repo(const Repo& alt) = delete;

	/*
	* Adauga filmul dat in repo
	* Arunca exceptie daca exista deja un film cu acelasi titlu, gen si an al aparitiei
	*/
	virtual void adaugare(const Film& film) = 0;

	/*
	* Modifica filmul dat in noul film
	* Arunca exceptie daca nu exista filmul dat
	*/
	virtual const Film modificare(int ind, Film filmNou) = 0;

	/*
	* Cauta filmul dupa titlu, gen si anul aparitiei
	* Arunca exceptie daca nu se gaseste
	*/
	virtual const Film cautare(string titlu, string gen, int an) const = 0;

	/*
	* Returneaza indicele filmului cautat in lista de filme
	* Returneaza -1 daca filmul nu se gaseste
	*/
	virtual int gasesteIndex(const Film& filmCautat) = 0;

	/*
	* Sterge filmul cautat din lista
	* Returneaza filmul cautat daca in gaseste
	*/
	virtual const Film stergere(const Film filmDeSters) = 0;

	//returneaza o lista cu toate filmele
	virtual const vector<Film>& getAll() noexcept = 0;
};

class FilmRepo : public Repo{
	vector<Film> filme;
	friend class Cos;

public:
	FilmRepo() = default;

	//distrugem constructorul de copiere
	FilmRepo(const FilmRepo& alt) = delete;

	/*
	* Adauga filmul dat in repo
	* Arunca exceptie daca exista deja un film cu acelasi titlu, gen si an al aparitiei
	*/
	void adaugare(const Film& film) override;

	/*
	* Modifica filmul dat in noul film
	* Arunca exceptie daca nu exista filmul dat
	*/
	const Film modificare(int ind, Film filmNou) override;

	/*
	* Cauta filmul dupa titlu, gen si anul aparitiei
	* Arunca exceptie daca nu se gaseste
	*/
	const Film cautare(string titlu, string gen, int an) const override;

	/*
	* Returneaza indicele filmului cautat in lista de filme
	* Returneaza -1 daca filmul nu se gaseste
	*/
	int gasesteIndex(const Film& filmCautat) override;

	/*
	* Sterge filmul cautat din lista
	* Returneaza filmul cautat daca in gaseste
	*/
	const Film stergere(const Film filmDeSters) override;

	//returneaza o lista cu toate filmele
	const vector<Film>& getAll() noexcept override;
};

class ProbRepo : public Repo{
	std::unordered_map<int, Film> filme;
	vector<Film> filmeV;
	double prob;
	friend class Cos;
	void pass() const;

public:
	ProbRepo() {
		std::mt19937 gen(123);
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		prob = dis(gen);
	};

	void setProb(double f);

	//distrugem constructorul de copiere
	ProbRepo(const FilmRepo& alt) = delete;

	/*
	* Adauga filmul dat in repo
	* Arunca exceptie daca exista deja un film cu acelasi titlu, gen si an al aparitiei
	*/
	void adaugare(const Film& film) override;

	/*
	* Modifica filmul dat in noul film
	* Arunca exceptie daca nu exista filmul dat
	*/
	const Film modificare(int ind, Film filmNou) override;

	/*
	* Cauta filmul dupa titlu, gen si anul aparitiei
	* Arunca exceptie daca nu se gaseste
	*/
	const Film cautare(string titlu, string gen, int an) const override;

	/*
	* Returneaza indicele filmului cautat in lista de filme
	* Returneaza -1 daca filmul nu se gaseste
	*/
	int gasesteIndex(const Film& filmCautat) override;

	/*
	* Sterge filmul cautat din lista
	* Returneaza filmul cautat daca in gaseste
	*/
	const Film stergere(const Film filmDeSters) override;

	//returneaza o lista cu toate filmele
	const vector<Film>& getAll() noexcept override;
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
void testProb();