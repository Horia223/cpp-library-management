#pragma once
#include "carte.h"
#include <vector>
#include <string>

//clasa pur abstracta
class RepoAbstract {
public:
	virtual const Carte& cautaCarte(const std::string& titlu, const std::string& autor) const = 0;
	virtual bool exista(const Carte& c) const = 0;
	virtual void adauga(const Carte& c) = 0;
	virtual void modificaTitlu(int poz, const std::string& titlu) = 0;
	virtual void modificaAutor(int poz, const std::string& autor) = 0;
	virtual void modificaGen(int poz, const std::string& gen) = 0;
	virtual void modificaAn(int poz, int an) = 0;
	virtual void stergeDupaPozitie(int poz) = 0;



	virtual const std::vector<Carte>& getAll() const = 0;
	virtual const Carte& getCarte(int poz) const = 0;

	virtual void insereaza(int poz, const Carte& c) = 0;
	virtual void setCartePePozitie(int poz, const Carte& c) = 0;

	virtual ~RepoAbstract() = default; //constructor virtual
};