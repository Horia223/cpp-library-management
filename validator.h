#pragma once
#include "Exceptii.h"
#include "carte.h"
class CarteValidator {
public:
	void valideaza(const Carte& c) const {
		vector<std::string> erori;
		if (c.getTitlu().length() == 0) erori.push_back("Titlul nu poate fi vid!");
		if (c.getAutor().length() == 0) erori.push_back("Autorul nu poate fi vid!");
		if (c.getGen().length() == 0) erori.push_back("Genul nu poate fi vid!");
		if (c.getAn() < 0) erori.push_back("Anul nu poate fi negativ!");

		if (erori.size() > 0) {
			throw ValidareException(erori); // Aruncăm excepția dacă sunt erori
		}
	}

};