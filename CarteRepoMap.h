#pragma once
#include "RepoAbstract.h"
#include "Exceptii.h"
#include <map>
#include <vector>
#include <ctime>
#include <random> 

class CarteRepoMap : public RepoAbstract {
private:
    double probabilitate;
    std::map<int, Carte> dictionar;

    mutable std::vector<Carte> cacheVector;

    void aruncaExceptieProbabilitate() const {
       
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_real_distribution<double> dist(0.0, 1.0); // Genereaza intre 0.0 si 1.0

        double random = dist(mt);

        if (random < probabilitate) {
            throw RepoException("Exceptie Map");
        }
    }

public:
    
    CarteRepoMap(double p) : probabilitate{ p } {}

    void adauga(const Carte& c) override;
    void stergeDupaPozitie(int poz) override;
    void insereaza(int poz, const Carte& c) override;
    void setCartePePozitie(int poz, const Carte& c) override;
    const Carte& getCarte(int poz) const override;
    const std::vector<Carte>& getAll() const override;

    const Carte& cautaCarte(const std::string& titlu, const std::string& autor) const override;
    bool exista(const Carte& c) const override;

    void modificaTitlu(int poz, const std::string& titlu) override;
    void modificaAutor(int poz, const std::string& autor) override;
    void modificaGen(int poz, const std::string& gen) override;
    void modificaAn(int poz, int an) override;
};