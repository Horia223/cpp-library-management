#include "repository.h"
#include "Exceptii.h"
#include <algorithm>

void CarteRepo::valideaza_pozitie(const int poz, size_t marime)  const {
	if (poz < 0 || poz >= marime) {
		throw RepoException("Pozitie invalida!");
	}
}


const vector<Carte>& CarteRepo::getAll() const noexcept {
	return this->Carti;

}
const Carte& CarteRepo::getCarte(int poz) const {
	this->valideaza_pozitie(poz, this->Carti.size());
	return this->Carti[poz];
}

bool CarteRepo::exista(const Carte& c) const {
	auto it = std::find_if(Carti.begin(), Carti.end(),
		[c](const Carte& carte_din_lista) {
			return carte_din_lista.getTitlu() == c.getTitlu() && carte_din_lista.getAutor() == c.getAutor();
		});
	return it != Carti.end();
}

const Carte& CarteRepo::cautaCarte(const string& titlu, const string& autor)const {
	auto it = std::find_if(Carti.begin(), Carti.end(),
		[titlu, autor](const Carte& c) {
			return c.getTitlu() == titlu && c.getAutor() == autor;
		});
		if (it != Carti.end()) {
			return *it;
	}
	throw RepoException("Cartea nu a fost gasita!");
}


void CarteRepo::adauga(const Carte& c) {
	if (exista(c)) {
		throw RepoException("Cartea exista deja in lista!");
	}
	this->Carti.push_back(c);

}

void CarteRepo::stergeDupaPozitie(int poz) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti.erase(Carti.begin() + poz); //Carti.begin() + poz
}

void CarteRepo::modificaTitlu(int poz, const string& titlu) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti[poz].setTitlu(titlu);


}

void CarteRepo::modificaAutor(int poz, const string& autor) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti[poz].setAutor(autor);


}

void CarteRepo::modificaGen(int poz, const string& gen) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti[poz].setGen(gen);


}

void CarteRepo::modificaAn(int poz, int an) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti[poz].setAn(an);
}


void CarteRepo::insereaza(int poz, const Carte& c) {
	if (poz < 0 || poz > this->Carti.size()) {
		throw RepoException("Pozitie invalida pentru inserare!");
	}
	this->Carti.insert(this->Carti.begin() + poz, c);
}



void CarteRepo::setCartePePozitie(int poz, const Carte& c) {
	valideaza_pozitie(poz, this->Carti.size());
	this->Carti[poz] = c;
}
