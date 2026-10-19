#pragma once
#include "repository.h"
#include <string>

class CarteRepoFile : public CarteRepo {
private:
    std::string fileName;
    void loadFromFile();
    void writeToFile();

public:
    CarteRepoFile(const std::string& fName);

    void adauga(const Carte& c) override;
    void stergeDupaPozitie(int poz) override;
    void modificaTitlu(int poz, const string& titlu) override;
    void modificaAutor(int poz, const string& autor) override;
    void modificaGen(int poz, const string& gen) override;
    void modificaAn(int poz, int an) override;

    // Metodele ajutătoare pentru undo pe care tocmai le-am creat
    void insereaza(int poz, const Carte& c) override;
    void setCartePePozitie(int poz, const Carte& c) override;
};