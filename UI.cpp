#include "UI.h"
#include "List.h"
#include <iostream>
#include <exception>
#include <Windows.h>
using namespace std;

void Console::menu() const {
	cout << "Comenzi disponibile:" << endl;
	cout << "0. Iesire" << endl;
	cout << "1. Adauga" << endl;
	cout << "2. Modifica" << endl;
	cout << "3. Sterge" << endl;
	cout << "4. Afiseaza" << endl;
	cout << "5. Cauta" << endl;
	cout << "6. Filtreaza" << endl;
	cout << "7. Sorteaza" << endl;
	cout << "8. Numara" << endl;
	cout << "9. Undo" << endl;
	cout << endl;
	afisareCos();
}

void Console::afisareCos() const {
	auto& cos = service.getCos();

	if (!cos.empty()) {
		cout << "Filme in cosul de cumparaturi:" << endl;
		for (auto& element : cos)
			cout << element.printFilm() << endl;
		cout << endl;
	}
	else
		cout << "Cosul de cumparaturi este gol." << endl;

	cout << "Comenzi disponibile pentru cosul de cumparaturi:" << endl;
	cout << "10. Adauga" << endl;
	cout << "11. Goleste" << endl;
	cout << "12. Genereaza cos" << endl;
	cout << "13. Exporta" << endl;
	cout << endl;
}

void Console::uiAdauga() const {
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

void Console::uiModifca() const {
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

void Console::uiCauta() const {
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

void Console::uiSterge() const {
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

//sortare filme după titlu, actor principal, an_gen
void Console::uiSortare() const {
	string optiune;
	vector<Film> listaSortare;

	cout << "\nCriterii de sortare disponibile: titlu, actor, an_gen\nIntroduceti criteriul: ";
	cin >> optiune;

	if (optiune == "titlu")
		listaSortare = service.sortare(cmpTitlu);
	else if (optiune == "actor")
		listaSortare = service.sortare(cmpActor);
	else if (optiune == "an_gen")
		listaSortare = service.sortare([](const Film& film1, const Film& film2) {return film1.getAn() < film2.getAn() || film1.getAn() == film2.getAn() && film1.getGen() <= film2.getGen(); });
	else {
		cout << "\nCriteriul introdus nu este disponibil\n.";
		return;
	}
	
	if (listaSortare.size() != 0) {
		cout << "\nLista sortata de filme este:\n";
		for (auto& film : listaSortare)
			cout << film.printFilm() << endl;
	}
	else cout << "\nNu exista filme care se incadreaza in filtrul dat.\n";
}

void Console::uiFiltrare() const {
	string optiune;
	vector<Film> listaFiltrare;

	cout << "\nCriterii de filtrare disponibile: titlu, an\nIntroduceti criteriul: ";
	cin >> optiune;
	if (optiune == "titlu") {
		string titlu;
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
		for(auto& film : listaFiltrare)
			cout << film.printFilm() << endl;
	}
	else cout << "\nNu exista filme care se incadreaza in filtrul dat.\n";
}

void Console::start() const {
	bool continua = true;
	int cmd;

	while (continua) {
		menu();
		cout << "Introduceti numarul comenzii: ";
		cin >> cmd;
		system("cls");
		switch (cmd) {
		case 0:
			continua = false;
			break;
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
			uiSortare();
			break;
		case 8:
			uiNumara();
			break;
		case 9:
			try {
				service.undo();
			}
			catch (RepoException& r) {
				cout << r.getErrorMessages();
			}
			break;
		case 10:
			uiAdaugaCos();
			break;
		case 11:
			uiGoleste();
			break;
		case 12:
			uiGenereaza();
			break;
		case 13:
			uiExporta();
			break;
		default:
			cout << "Comanda introdusa nu exista.";
			break;
		}
		cout << endl;
	}
}

void Console::uiAdaugaCos() const {
	string gen, actor, titlu;
	int an{ 0 };
	cout << endl;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti anul: ";
	cin >> an;
	cout << "Introduceti genul: ";
	getline(cin >> ws, gen);

	try {
		Film filmAdaugat = service.cautaFilm(titlu, gen, an);
		service.adaugaCos(filmAdaugat);
	}
	catch (CosException& c) {
		cout << c.getErrorMessages();
	}
}

void Console::uiGenereaza() const {
	int nrF{ 0 };
	cout << "Introduceti numarul de filme de adaugat in cos: ";
	cin >> nrF;
	try {
		service.genereazaCos(nrF);
	}
	catch (CosException& c) {
		cout << c.getErrorMessages();
	}
}

void Console::uiNumara() const {
	string optiune;
	int nr{ 0 };

	cout << "\nCriterii de filtrare disponibile: gen, an\nIntroduceti criteriul: ";
	cin >> optiune;
	if (optiune == "gen") {
		string gen;
		cout << "Introduceti genul: ";
		getline(cin >> ws, gen);
		nr = service.numaraFilme([=](const Film& film) {return film.getGen() == gen; });
	}
	else if (optiune == "an") {
		cout << "Introduceti anul: ";
		int an{ 0 };
		cin >> an;
		nr = service.numaraFilme([=](const Film& film) {return film.getAn() == an; });
	}
	else {
		cout << "\nCriteriul introdus nu este disponibil\n.";
		return;
	}

	if (nr == 1)
		cout << "Exista un film care indeplineste criteriul dat.";
	else cout << "Sunt " << nr << " filme care indeplinesc criteriul dat.";
	cout << endl;
}

void Console::uiExporta() const {
	string numeFisier;
	cout << "Introduceti numele fisierului: ";

	getline(cin >> ws, numeFisier);
	try {
		service.exportaCos(numeFisier);
	}
	catch (CosException& c) {
		cout << c.getErrorMessages();
	}
}

void Console::uiGoleste() const {
	try {
		service.golesteCos();
	}
	catch (CosException& c) {
		cout << c.getErrorMessages();
	}

}

void Console::afisare() const {
	const vector<Film>& filme = service.getAll();
	cout << endl;
	if (filme.size() != 0) {
		cout << "Lista de filme este: \n";
		for (auto& film : filme)
			cout << film.printFilm() << endl;
	}
	else
		cout << "Momentan nu exista filme disponibile.\n";
}
