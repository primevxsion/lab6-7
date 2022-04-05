#include "List.h"
#include "Film.h"
#include <assert.h>
#include <exception>

template <typename T> void List<T>::push_back(T elem) {
	Nod<T>* nodNou = new Nod<T>{ elem };

	if (dim == 0) {
		prim = nodNou;
		ultim = nodNou;
	}	//daca se adauga chiar primul element
	else {
		ultim->urmator = nodNou;
		nodNou->precedent = ultim;
		ultim = nodNou;
	}

	dim++;
}

template <typename T> List<T>::List(const List<T>& ot) {
	dim = 0;
	Nod<T>* curent = ot.prim;
	int i = 0;
	while (i < ot.dim) {
		push_back(curent->el);
		curent = curent->urmator;
		i++;
	}
}

template <typename T> T List<T>::operator[](int ind) const{
	if (ind < dim) {
		Nod<T>* it = prim;
		while (ind) {
			it = it->urmator;
			ind--;
		}
		return it->el;
	}
	throw std::exception();
}

template <typename T> List<T>::~List() {
	if (dim > 0)
		while (prim != nullptr) {
			Nod<T>* curent = prim;
			prim = prim->urmator;
			delete curent;
		}
}

template <typename T> Nod<T>* List<T>::pozitie(int ind) const{
	if (ind >= dim || ind < 0)
		throw std::exception();

	Nod<T>* curent = prim;
	int i = 0;
	while (i < ind) {
		i++;
		curent = curent->urmator;
	}

	return curent;
}

template <typename T> void List<T>::remove(int ind) {
	Nod<T>* PNod = pozitie(ind);

	if (PNod == prim) {
		prim = prim->urmator;
	}
	else if (PNod == ultim) {
		ultim = ultim->precedent;
		ultim->urmator = nullptr;
	}
	else {
		PNod->precedent->urmator = PNod->urmator;
		PNod->urmator->precedent = PNod->precedent;
	}

	delete PNod;
	dim--;
}

template <typename T> void List<T>::operator=(const List<T>& ot) {
	dim = 0;
	Nod<T>* curent = ot.prim;
	int i = 0;
	while (i < ot.dim) {
		push_back(curent->el);
		curent = curent->urmator;
		i++;
	}
	//return *this;
}

void testList() {
	List<Film> filme;
	filme.push_back(Film{ "tyson", 1920, "rap", "tyson" });
	assert(filme.size() == 1);
	assert(filme[0].getActor() == "tyson");
	filme.push_back(Film{ "benny", 1999, "comedie", "benny" });
	assert(filme[1].getAn() == 1999);
	filme.remove(0);
	assert(filme.size() == 1);
	assert(filme[0].getAn() == 1999);
	try {
		cout << filme[100].getAn();
	}
	catch (std::exception&) {
		assert(true);
	}

	Film film1{ "Parasite", 2019, "thriller", "Song Kang" };
	Film film2{ "Roma", 2018, "history", "Cuaron" };
	Film film3{ "The Lion King", 2019, "animation", "Donald Glover" };
	filme.push_back(film1);
	filme.push_back(film2);
	filme.push_back(film3);

	List<Film> cop = filme;
	cop.modify(0, Film{ "500 ounces", 2020, "rap", "Westside" });
	assert(filme[0].getTitlu() == "benny" && cop[0].getTitlu() == "500 ounces");
	try {
		cop.remove(-1);
	}
	catch (std::exception&) {
		assert(true);
	}	
	
}