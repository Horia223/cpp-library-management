#pragma once
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Carte
{
private:
	string titlu;
	string autor;
	string gen;
	int an = 0;

public:
	/*
	* Constructor Default
	*/
	Carte() = default;

	/*
	Contructor de copiere
	*/
	Carte(const Carte& ot) : titlu{ ot.titlu }, autor{ ot.autor }, gen{ ot.gen }, an{ ot.an } { std::cout << "Copie :(" << std::endl; };
	/*
	Constructor
	*/
	Carte(const string& t, const string& a, const string& g, int an_param) : titlu{ t }, autor{ a }, gen{ g }, an{ an_param } {};
	/*
	Returneaza Titlul
	*/
	const string& getTitlu() const noexcept;
	/*
	Returneaza Autorul
	*/
	const string& getAutor() const noexcept;
	/*
	Returneaza Genul
	*/
	const string& getGen() const noexcept;
	/*
	Returneaza Anul
	*/
	int getAn() const noexcept;
	/*
	* Modifica Titlul
	*/
	void setTitlu(const string& titlu_nou);
	/*
	* Modifica Autor
	*/
	void setAutor(const string& autor_nou);
	/*
	* Modifica Gen
	*/
	void setGen(const string& gen_nou);
	/*
	* Modifica An
	*/
	void setAn(int an_nou) noexcept;
	//string printCarte();
	friend ostream& operator<<(ostream& os, const Carte& c); //operator<<(cout, c1)

	~Carte() = default;
};
