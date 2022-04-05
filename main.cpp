#include <iostream>
#include "UI.h"
#include "List.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

void start() {
	FilmRepo repo;
	FilmValidator validator;
	FilmService service{ repo, validator };
	Console consola{ service };
	consola.start();
}

int main()
{
	testList();
	testFilm();
	testValidator();
	testService();
	testRepo();
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}