#include "Validators.h"
#include "Film.h"
#include <assert.h>
#include <string>

using std::string;

void FilmValidator::valideaza(const Film& film) {
	vector<string> errors;
	if (film.getTitlu().length() == 0)
		errors.push_back("Titlul trebuie sa fie nevid.");
	if (film.getGen().length() == 0)
		errors.push_back("Genul trebuie sa fie nevid.");
	if (film.getAn() >= 2022 || film.getAn() <= 1900)
		errors.push_back("Anul lansarii trebuie sa fie intre 1900 si 2022.");
	if (film.getActor().length() == 0)
		errors.push_back("Numele actorului trebuie sa fie nevid.");
	
	if (errors.size() > 0)
		throw ValidationException(errors);
}

void testValidator() {
	Film film1{ "westside", 2019, "istorie", "westside" };
	FilmValidator validator;
	validator.valideaza(film1);

	try {
		validator.valideaza(Film{ "", 2012, "comedie", "westside" });
	}
	catch (ValidationException&) {}

	try {
		validator.valideaza(Film{ "mic check", 1700, "istorie", "freddie" });
	}
	catch (ValidationException&) {}

	try {
		validator.valideaza(Film{ "mcdonalds", -11, "documentar", "roc" });
	}
	catch (ValidationException& v) {
		string msg = "\n";
		msg += "Anul lansarii trebuie sa fie intre 1900 si 2022.";
		msg += "\n";
		assert(v.getErrorMessages() == msg);
	}

	try {
		validator.valideaza(Film{ "george bondo", 1920, "", "" });
	}
	catch (ValidationException&) {}




}