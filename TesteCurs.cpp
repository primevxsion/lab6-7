#include "Film.h"
#include "List.h"
#include <crtdbg.h>
#include <vector>
#include <string>
#define _CRTDBG_MAP_ALLOC

template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	int totalAn = 0;
	for (auto el : v) {
		totalAn += el.getAn();
	}
	Film p{ "total", totalAn, "tt", "tt" };
	v.push_back(p);
	return v;
}

template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addFilms(v, 100);
	assert(v.size() == 100);
	assert(v[50].getTitlu() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2[50].getTitlu() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3[50].getTitlu() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4[50].getTitlu() == "50_type");
}

template <typename MyVector>
void addFilms(MyVector& v, int cate) {
	for (int i = 0; i < cate; i++) {
		//Film p{ std::to_string(i) + "_type",std::to_string(i) + "_spec",i + 10.0 };
		Film p{ std::to_string(i) + "_type", i + 10, std::to_string(i) + "_spec", "tt" };
		v.push_back(p);
	}
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addFilms(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}

void testCurs() {

	testAll<List<Film>>();

	_CrtDumpMemoryLeaks();
}