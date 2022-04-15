#pragma once
#include <functional>
#include "Film.h"
#include <assert.h>
#include <exception>

template <typename T> class List;
template <typename T> class Nod;

template <typename T> class Iterator {
public:
	friend class List<T>;

	Nod<T>* curent;
	List<T>& lst;

	Iterator<T>(List<T>& lst) :lst{ lst }, curent{ lst.prim } {}

	Iterator<T>(List<T>& lst, int poz) : lst{ lst } {
		curent = lst.prim;
		while (poz) {
			poz--;
			curent = curent->urmator;
		}
	}

	T& operator*() {
		return curent->el;
	}

	void operator++() {
		curent = curent->urmator;
	}
	
	T element() {
		return curent->el;
	}

	bool operator==(const Iterator<T>& ot) {
		return curent == ot.curent;
	}

	bool operator!=(const Iterator<T>& ot) {
		return curent != ot.curent;
	}
};

template <typename T> class Nod {
private:
	T el;	//element
	Nod<T> *precedent, *urmator;

public:
	friend class List<T>;
	friend class Iterator<T>;
	Nod(T element) :precedent{ nullptr }, urmator{ nullptr }, el{ element } {}
};

template <typename T> class List {
private:
	Nod<T> *prim, *ultim;
	int dim;
	Nod<T>* pozitie(int ind) const;

public:
	friend class Iterator<T>;

	List() :prim(nullptr), ultim(nullptr), dim{ 0 } {}
	
	List(const List<T>& ot);

	Iterator<T> begin() {
		return Iterator<T>{*this};
	}

	Iterator<T> end() {
		return Iterator<T>{*this, dim};
	}

	int size() const{
		return dim;
	}
	
	void sort(std::function<bool(const T& el1, const T& el2)>);

	//adauga la sfarsit
	void push_back(T elem);

	T operator[](int ind) const;

	void remove(int ind);

	List<T>& operator=(const List<T>& ot);

	T modify(int ind, T newElem) {
		Nod<T>* poz = pozitie(ind);
		poz->el = newElem;
		return newElem;
	}

	~List();
};

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

template <typename T> List<T>& List<T>::operator=(const List<T>& ot) {
	if (dim > 0)
		while (prim != nullptr) {
			Nod<T>* curent = prim;
			prim = prim->urmator;
			delete curent;
		}
	dim = 0;
	Nod<T>* curent = ot.prim;
	int i = 0;
	while (i < ot.dim) {
		push_back(curent->el);
		curent = curent->urmator;
		i++;
	}
	return *this;
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

template <typename T> T List<T>::operator[](int ind) const {
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

template <typename T> Nod<T>* List<T>::pozitie(int ind) const {
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

template <typename T> void List<T>::sort(std::function<bool(const T& el1, const T& el2)> cmp) {
	bool sortat = false;
	while (!sortat) {
		sortat = true;
		Nod<T>* p = prim;
		while (p != ultim) {
			if (!cmp(p->el, p->urmator->el)) {
				sortat = false;
				T aux = p->el;
				p->el = p->urmator->el;
				p->urmator->el = aux;
			}
			p = p->urmator;
		}
	}
}

void testList();