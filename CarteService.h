#pragma once
#include "repository.h"
#include "Validator.h"
#include "cos.h"
#include "dto.h"
#include "repoAbstract.h"
#include <map>
#include <vector>
#include <memory>
#include "undo.h"
using std::map;
using std::vector;
class CarteService {
private:
	RepoAbstract& repo;
	//CarteRepo& repo;
	CarteValidator& val;
	typedef bool (*Comparator)(const Carte&, const Carte&);
	Cos cosCurent;

	std::vector<std::unique_ptr<ActiuneUndo>> undoActions;




public:
	/*
	* Constructor
	*/
	CarteService(RepoAbstract& r, CarteValidator& v) noexcept : repo{ r }, val{ v } {};

	/*
	* Adauga o Carte in vector
	* pre: * pre: titlu, autor, gen nu sunt vide, poz > 0
	* post:s a adaugat o carte cu parametrii trimisi ca atribute in vector
	* return: None
	*/
	void adaugaCarte(const string& titlu, const string& autor, const string& gen, int an);
	/*
	* Sterge o Carte in vector
	* post:elementul de pe pozitia poz-1 este sters, daca exista
	* return: None
	*/
	void stergeCarte(int poz);
	/*
	* Return: o referinta la vectorul cu toate Cartile
	*/
	const vector<Carte>& getAll() const noexcept;
	/*
	* Return carte de pe pozitia data
	*/
	const Carte& getCarte(int poz) const;
	/*
	* Cauta o carte dupa titlu si autor, o carte cu acelasi titlu si autor este dublura
	*/
	const Carte& cautaCarte(const string& titlu, const string& autor) const;
	/*
	* Modifica titltul cartii de pe pozitia poz
	*/
	void modificaTitlu(int poz, const string& titlu);
	/*
	* Modifica Autor cartii de pe pozitia poz
	*/
	void modificaAutor(int poz, const string& autor);
	/*
	* Modifica Gen cartii de pe pozitia poz
	*/
	void modificaGen(int poz, const string& gen);
	/*
	* Modifica An cartii de pe pozitia poz
	*/
	void modificaAn(int poz, int an);


	/*
	* Filtare carti dupa titlu
	*/
	vector<Carte> filtrare_titlu(const string& titlu) const;

	/*
	* Filtrare carti dupa an
	*/
	vector<Carte> filtrare_an(int an) const noexcept;
	/*
	* Sortarea generica, utilizeaza algorimtul bubblesort, si utilizam o functie de comparare, pentru a nu scrie de mai multe ori
	*/
	vector<Carte> sorteaza(Comparator maiMic)const;
	/*
	* Se compara dupa tiltu
	*/
	static bool comparaTiltu(const Carte& c1, const Carte& c2) noexcept;
	/*
	* Se compara autor
	*/
	static bool comparaAutor(const Carte& c1, const Carte& c2) noexcept;
	/*
	* Se compara An si gen
	*/
	static bool comparaAnGen(const Carte& c1, const Carte& c2) noexcept;


	//Se adauga in cos o carte dupa titlu, daca exista
	void cosAdauga(const string& titlu);

	//goleste cosul de toate cartile
	void golesteCosService() noexcept;

	//Returneaza cosul cu toate cartile
	const vector<Carte>& getAllCosService() const noexcept;

	//se face export intr un fisier .csv cu toate cartile adaugate in cos
	void exportCosCsvService(const string& numeFisier);
	
	size_t dimensiuneCos() const noexcept;

	void cosGenereaza(int nr);

	map<std::string, dto> getGenDto() const;


	void undo();
	
	void addObserverToCos(Observer* obs) {
		cosCurent.addObserver(obs);
	}

	void removeObserverFromCos(Observer* obs) {
		cosCurent.removeObserver(obs);
	}

};