#include "film.h"
#include <assert.h>

bool cmpTitlu(const Film& film1, const Film& film2) {
	return film1.getTitlu() < film2.getTitlu();
}

bool cmpAn(const Film& film1, const Film& film2) {
	return film1.getAn() < film2.getAn();
}

bool cmpGen(const Film& film1, const Film& film2) {
	return film1.getGen() < film2.getGen();
}

bool cmpActor(const Film& film1, const Film& film2) {
	return film1.getActor() < film2.getActor();
}

void testFilm() {
	Film film1{ "benny", 1990, "istorie", "benny" };
	Film film2{ "tyson", 1920, "comedie", "tyson" };
	assert(film1.printFilm() != "");
	assert(cmpGen(film2, film1));
	assert(cmpAn(film2, film1));
	assert(cmpActor(film1, film2));
	assert(cmpTitlu(film1, film2));
}