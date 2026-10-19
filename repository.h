#pragma once
#include "carte.h"
#include <vector>
#include "RepoAbstract.h"
using std::vector;
//#include "vector.h"


class CarteRepo: public RepoAbstract
{
private:
	vector<Carte> Carti;
public:
	/*
	* Cauta o carte dupa titlu si autor
	* return: returneaza cartea daca este gasita
	* raises: RepoException
	*/
	virtual const Carte& cautaCarte(const string& titlu, const string& autor) const;
	/*
	*Verifica daca exista cartea c in vector
	* return: true: daca exista cartea c in vector
	*		  false: daca nu exista cartea in vecetor
	*/
	virtual bool exista(const Carte& c) const;
	/*
	* Adauga cartea c in vector, si verifica daca se adauga o carte de doua ori
	*/
	virtual void adauga(const Carte& c);
	/*
	* Modifica titlul cartii de pe pozitia poz
	*/
	virtual void modificaTitlu(int poz, const string& titlu);
	/*
	* Modifica autorul cartii de pe pozitia poz
	*/
	virtual void modificaAutor(int poz, const string& autor);
	/*
	* Modifica genul cartii de pe pozitia poz
	*/
	virtual void modificaGen(int poz, const string& gen);
	/*
	* Modifica Anul cartii de pe pozitia poz
	*/
	virtual void modificaAn(int poz, int an);
	/*
	* Sterge dupa pozitie cartea
	*/
	virtual void stergeDupaPozitie(int poz);
	/*
	* Returnez vectorul prin referinta cu carti
	*/
	virtual const vector<Carte>& getAll() const noexcept;
	/*
	* Returneaza o carte dupa pozitie din vector
	*/
	virtual const Carte& getCarte(int poz) const;
	/*
	* Valideza pozitia si da raise RepoException
	*/
	virtual void valideaza_pozitie(const int poz, size_t marime) const;

	virtual ~CarteRepo() = default;

	// Undo
	virtual void insereaza(int poz, const Carte& c);
	virtual void setCartePePozitie(int poz, const Carte& c);
};