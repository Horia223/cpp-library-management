#include "carte.h"

const string& Carte::getTitlu() const noexcept {
	return this->titlu;
}

const string& Carte::getAutor() const noexcept {
	return this->autor;
}

const string& Carte::getGen() const noexcept {
	return this->gen;
}

int Carte::getAn() const noexcept {
	return this->an;
}
void Carte::setTitlu(const string& t) {
	this->titlu = t;
}
void Carte::setAutor(const string& a) {
	this->autor = a;
}
void Carte::setGen(const string& g) {
	this->gen = g;
}
void Carte::setAn(int a) noexcept {
	this->an = a;
}

ostream& operator<<(ostream& os, const Carte& c) {
	os << "Titlu: " << c.getTitlu() << "|" << "Autor: " << c.getAutor() << "|" << "Gen: " << c.getGen() << "|" << "Anul Aparitiei: " << c.getAn();
	return os;

}

