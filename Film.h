#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Film {
	string titlu, actor, gen;
	int an;

public:
	Film(const string titlu, int an, const string gen, const string actor) :titlu{ titlu }, an{ an }, gen{ gen }, actor{ actor } {}

	Film() : an{ 2000 } {}

	Film(const Film& alt):titlu{alt.titlu},gen{alt.gen},actor{alt.actor},an{alt.an}{}

	string getTitlu() const {
		return titlu;
	}

	int getAn() const {
		return an;
	}

	string getGen() const {
		return gen;
	}

	string getActor() const {
		return actor;
	}

	bool operator== (const Film &film2) const{
		return this->titlu == film2.getTitlu() && this->gen == film2.getGen() && this->an == film2.getAn();
	}

	string printFilm() const{
		return titlu + " : " + gen + " : " + std::to_string(an) + " : " + actor;
	}
};

/*Compara 2 filme dupa titlu
Returneaza true daca film1.tip < film2.tip*/
bool cmpTitlu(const Film& film1, const Film& film2);

/*Compara 2 filme dupa an
Returneaza true daca film1.an < film2.an*/
bool cmpAn(const Film& film1, const Film& film2);

/*Compara 2 filme dupa gen
Returneaza true daca film1.gen < film2.gen*/
bool cmpGen(const Film& film1, const Film& film2);

/*Compara 2 filme dupa actorul principal
Returneaza true daca film1.actor < film2.actor*/
bool cmpActor(const Film& film1, const Film& film2);

void testFilm();