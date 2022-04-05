#pragma once
#include "Film.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class ValidationException {
	vector<string> errorMsg;

public:
	ValidationException(vector <string> errorMessages) :errorMsg{ errorMessages } {}

	string getErrorMessages() {
		string fullMsg = "\n";
		for (const string s : errorMsg) {
			fullMsg += s + "\n";
		}
		return fullMsg;
	}
};

class FilmValidator {
public:
	void valideaza(const Film& film);
};

void testValidator();