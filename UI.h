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
	void uiSortare() const;
	void afisare() const;
	void start() const;
	void afisareCos() const;
	void uiAdaugaCos() const;
	void uiGenereaza() const;
	void uiGoleste() const;
	void uiExporta() const;
	void uiNumara() const;
};