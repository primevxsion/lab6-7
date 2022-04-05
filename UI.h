#pragma once
#include "Service.h"

class Console {
private:
	FilmService& service;

public:
	Console(FilmService& srv) : service{srv}{}
	Console(const Console& ot) = delete;
	void menu() const;
	void uiFiltrare() const;
	void uiAdauga() const;
	void uiModifca() const;
	void uiSterge() const;
	void uiCauta() const;
	void afisare() const;
	void start() const;
};