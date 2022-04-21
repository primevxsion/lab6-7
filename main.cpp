#include <iostream>
#include "UI.h"
#include "List.h"
#include <crtdbg.h>
#include "TesteCurs.h"
#include "Cos.h"
#define _CRTDBG_MAP_ALLOC

void start() {
	ProbRepo repo;
	repo.setProb(1);
	FilmValidator validator;
	Cos cos;
	FilmService service{ repo, validator, cos};
	Console consola{ service };
	consola.start();
}

int main()
{
	testCurs();
	testeCos();
	testeUndo();
	testList();
	testProb();
	testFilm();
	testValidator();
	testService();
	testRepo();
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}