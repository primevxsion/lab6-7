#include "UI.h"
#include <iostream>
#include <exception>
using namespace std;

void Console::menu() const{
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga" << endl;
	cout << "2. Modifica" << endl;
	cout << "3. Sterge" << endl;
	cout << "4. Afiseaza" << endl;
	cout << "5. Cauta" << endl;
	cout << "6. Filtreaza" << endl;
	cout << "7. Sorteaza" << endl;
	cout << "8. Iesire" << endl;
}

void Console::uiAdauga() const{
	string gen, actor, titlu;
	int an{0};
	cout << endl;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti anul: ";
	cin >> an;
	cout << "Introduceti genul: ";
	getline(cin >> ws, gen);
	cout << "Introduceti actorul principal: ";
	getline(cin >> ws, actor);

	try {
		Film filmAdaugat = service.adaugaFilm(titlu, gen, an, actor);
		cout << "\nA fost adaugat filmul: " << filmAdaugat.printFilm() << endl;
	}
	catch (ValidationException& v) {
		cout << v.getErrorMessages();
	}
	catch (RepoException& r) {
		cout << r.getErrorMessages();
	}
	catch (std::exception&) {
		cout << "Exceptie UI Adaugare";
	}
}

void Console::uiModifca() const{
	string gen, titlu;
	string titluNou, genNou, actorNou;
	int an{ 0 }, anNou{ 0 };
	
	cout << endl;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti anul: ";
	cin >> an;
	cout << "Introduceti genul: ";
	getline(cin >> ws, gen);

	cout << "Introduceti noul titlu: ";
	getline(cin >> ws, titluNou);
	cout << "Introduceti noul an: ";
	cin >> anNou;
	cout << "Introduceti noul gen: ";
	getline(cin >> ws, genNou);
	cout << "Introduceti noul actor principal: ";
	getline(cin >> ws, actorNou);

	try {
		Film filmModificat = service.modificaFilm(titlu, gen, an, titluNou, anNou, genNou, actorNou);
		cout << "\nFilmul modificat este: " << filmModificat.printFilm() << endl;
	}
	catch (RepoException& r) {
		cout << r.getErrorMessages();
	}
	catch (ValidationException& v) {
		cout << v.getErrorMessages();
	}
	catch (std::exception&) {
		cout << "Exceptie UI Modificare";
	}

}

void Console::uiCauta() const{
	string titlu, gen, actor;
	int an{ 0 };

	cout << endl;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti anul: ";
	cin >> an;
	cout << "Introduceti genul: ";
	getline(cin >> ws, gen);

	try {
		Film filmCautat = service.cautaFilm(titlu, gen, an);
		cout << "\nFilmul cautat este: " << filmCautat.printFilm() << endl;
	}
	catch (RepoException& r) {
		cout << r.getErrorMessages();
	}
	catch (std::exception&) {
		cout << "Exceptie UI Cautare";
	}

}

void Console::uiSterge() const{
	string gen, titlu, actor;
	int an{ 0 };

	cout << endl;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti anul: ";
	cin >> an;
	cout << "Introduceti genul: ";
	getline(cin >> ws, gen);
	
	try {
		Film filmDeSters = service.stergeFilm(titlu, gen, an);
		cout << "\nFilmul sters este: " << filmDeSters.printFilm() << endl;
	}
	catch (RepoException& r) {
		cout << r.getErrorMessages();
	}
	catch (std::exception&) {
		cout << "Exceptie UI Sterge";
	}
}

void Console::uiFiltrare() const{
	string optiune, titlu;
	List<Film> listaFiltrare;

	cout << "\nCriterii de filtrare disponibile: titlu, an\nIntroduceti criteriul: ";
	cin >> optiune;
	if (optiune == "titlu") {
		cout << "Introduceti titlul: ";
		getline(cin >> ws, titlu);
		listaFiltrare = service.filtrare([=](const Film& film) {return film.getTitlu() == titlu; });
	}
	else if (optiune == "an") {
		cout << "Introduceti anul: ";
		int an{ 0 };
		cin >> an;
		listaFiltrare = service.filtrare([=](const Film& film) {return film.getAn() == an; });
	}
	else {
		cout << "\nCriteriul introdus nu este disponibil\n.";
		return;
	}

	if (listaFiltrare.size() != 0) {
		cout << "\nLista de filme este:\n";
		for (int i = 0; i < listaFiltrare.size(); ++i)
			cout << listaFiltrare[i].printFilm() << endl;
	}
	else cout << "\nNu exista filme care se incadreaza in filtrul dat.\n";
}

void Console::start() const{
	bool continua = true;
	int cmd;

	while (continua) {
		menu();
		cout << "Introduceti numarul comenzii: ";
		cin >> cmd;
		switch (cmd) {
		case 1:
			uiAdauga();
			break;
		case 2:
			uiModifca();
			break;
		case 3:
			uiSterge();
			break;
		case 4:
			afisare();
			break;
		case 5:
			uiCauta();
			break;
		case 6:
			uiFiltrare();
			break;
		case 7:
			break;
		case 8:
			continua = false;
			break;
		default:
			cout << "Comanda introdusa nu exista.";
			break;
		}
		cout << '\n';
	}
}

void Console::afisare() const{
	const List<Film>& filme = service.getAll();
	cout << endl;
	if (filme.size() != 0) {
		cout << "Lista de filme este: \n";
		for (int i = 0; i < filme.size(); ++i)
			cout << filme[i].printFilm() << endl;
	}
	else
		cout << "Momentan nu exista filme disponibile.\n";
}
