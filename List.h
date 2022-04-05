#pragma once

template <typename T> class List;
template <typename T> class Nod;


template <typename T> class Nod {
private:
	T el;	//element
	Nod<T> *precedent, *urmator;

public:
	friend class List<T>;
	Nod(T element) :precedent{ nullptr }, urmator{ nullptr }, el{ element } {}
};

template <typename T> class List {
private:
	Nod<T> *prim, *ultim;
	int dim;
	Nod<T>* pozitie(int ind) const;

public:
	List() :prim(nullptr), ultim(nullptr), dim{ 0 } {}
	
	List(const List<T>& ot);


	int size() const{
		return dim;
	}
	
	//adauga la sfarsit
	void push_back(T elem);

	T operator[](int ind) const;

	void remove(int ind);

	void operator=(const List<T>& ot);

	T modify(int ind, T newElem) {
		Nod<T>* poz = pozitie(ind);
		poz->el = newElem;
		return newElem;
	}

	~List();
};

void testList();