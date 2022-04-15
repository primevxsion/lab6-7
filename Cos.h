#pragma once
#include <vector>
#include "Film.h"
#include <string>
#include "Repository.h"
using std::vector;
using std::string;

class Cos {
private:
	vector<Film> cosFilme;

public:

	//Goleste cosul
	void goleste();

	//Adauga un film in cos
	void adauga(const Film& film);

	//Genereaza un cos cu nrFilme filme alese in mod aleatoriu
	void genereaza(int nrFilme, FilmRepo& repo);

	//Returneaza lista de filme din cos
	vector<Film>& getCos() {
		return cosFilme;
	}

	//Salveaza cosul in fisierul dat ca parametru
	void exportaCos(string numeFisier);
};

//Clasa pentru exceptii pentru cos
class CosException {
	vector<string> errorMsg;

public:
	CosException(vector <string> errorMessages) :errorMsg{ errorMessages } {}

	CosException(string error) {
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

void testeCos();