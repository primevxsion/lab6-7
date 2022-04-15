#include "List.h"

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

	filme.remove(1);
	filme.remove(filme.size() - 1);

	Iterator<Film> it{filme};
	assert(it.element() == filme[0]);
	
	Iterator<Film> it2{ filme, filme.size() };
}