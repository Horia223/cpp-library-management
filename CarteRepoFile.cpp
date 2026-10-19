#include "CarteRepoFile.h"
#include "Exceptii.h"
#include <fstream>
#include <sstream>

CarteRepoFile::CarteRepoFile(const std::string& fName) : CarteRepo(), fileName{ fName } {
    loadFromFile();
}

void CarteRepoFile::loadFromFile() {
    std::ifstream in(fileName);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string titlu, autor, gen, anStr;

        std::getline(ss, titlu, ',');
        std::getline(ss, autor, ',');
        std::getline(ss, gen, ',');
        std::getline(ss, anStr, ',');

        int an = std::stoi(anStr);
        Carte c{ titlu, autor, gen, an };
        CarteRepo::adauga(c);
    }
    in.close();
}

void CarteRepoFile::writeToFile() {
    std::ofstream out(fileName);
    if (!out.is_open()) throw RepoException("Eroare deschidere fisier pentru scriere!");

    for (const auto& c : getAll()) {
        out << c.getTitlu() << "," << c.getAutor() << "," << c.getGen() << "," << c.getAn() << "\n";
    }
    out.close();
}

// Ori de cate ori se face o actiune ce schimba datele, apelam metoda de baza, apoi salvam in fisier
void CarteRepoFile::adauga(const Carte& c) { CarteRepo::adauga(c); writeToFile(); }
void CarteRepoFile::stergeDupaPozitie(int poz) { CarteRepo::stergeDupaPozitie(poz); writeToFile(); }
void CarteRepoFile::modificaTitlu(int poz, const string& t) { CarteRepo::modificaTitlu(poz, t); writeToFile(); }
void CarteRepoFile::modificaAutor(int poz, const string& a) { CarteRepo::modificaAutor(poz, a); writeToFile(); }
void CarteRepoFile::modificaGen(int poz, const string& g) { CarteRepo::modificaGen(poz, g); writeToFile(); }
void CarteRepoFile::modificaAn(int poz, int a) { CarteRepo::modificaAn(poz, a); writeToFile(); }
void CarteRepoFile::insereaza(int poz, const Carte& c) { CarteRepo::insereaza(poz, c); writeToFile(); }
void CarteRepoFile::setCartePePozitie(int poz, const Carte& c) { CarteRepo::setCartePePozitie(poz, c); writeToFile(); }