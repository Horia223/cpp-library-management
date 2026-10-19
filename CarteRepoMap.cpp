#include "CarteRepoMap.h"

void CarteRepoMap::adauga(const Carte& c) {
    aruncaExceptieProbabilitate(); 
    if (exista(c)) throw RepoException("Cartea exista deja in lista");

    int indx = static_cast<int>(dictionar.size());
    dictionar[indx] = c;
}

void CarteRepoMap::stergeDupaPozitie(int poz) {
    aruncaExceptieProbabilitate();
    if (poz < 0 || poz >= dictionar.size()) throw RepoException("Pozitie invalida");

    
    for (int i = poz; i < dictionar.size() - 1; i++) {
        dictionar[i] = dictionar[i + 1];
    }
    dictionar.erase(static_cast<int>(dictionar.size()) - 1); 
}

void CarteRepoMap::insereaza(int poz, const Carte& c) {
    aruncaExceptieProbabilitate();
    if (poz < 0 || poz > dictionar.size()) throw RepoException("Pozitie invalida");

   
    for (int i = static_cast<int>(dictionar.size()); i > poz; i--) {
        dictionar[i] = dictionar[i - 1];
    }
    dictionar[poz] = c;
}

void CarteRepoMap::setCartePePozitie(int poz, const Carte& c) {
    aruncaExceptieProbabilitate();
    if (poz < 0 || poz >= dictionar.size()) throw RepoException("Pozitie invalida");
    dictionar[poz] = c;
}

const Carte& CarteRepoMap::getCarte(int poz) const {
    aruncaExceptieProbabilitate();
    if (poz < 0 || poz >= dictionar.size()) throw RepoException("Pozitie invalida");
    return dictionar.at(poz);
}

const std::vector<Carte>& CarteRepoMap::getAll() const {
    aruncaExceptieProbabilitate();
    cacheVector.clear();
    for (const auto& pereche : dictionar) {
        cacheVector.push_back(pereche.second); // transferam din map in vectorul temporar
    }
    return cacheVector;
}

const Carte& CarteRepoMap::cautaCarte(const std::string& titlu, const std::string& autor) const {
    aruncaExceptieProbabilitate();
    for (const auto& pereche : dictionar) {
        if (pereche.second.getTitlu() == titlu && pereche.second.getAutor() == autor) {
            return pereche.second;
        }
    }
    throw RepoException("Cartea nu a fost gasita");
}

bool CarteRepoMap::exista(const Carte& c) const {
    
    for (const auto& pereche : dictionar) {
        if (pereche.second.getTitlu() == c.getTitlu() && pereche.second.getAutor() == c.getAutor()) return true;
    }
    return false;
}

void CarteRepoMap::modificaTitlu(int poz, const std::string& titlu) { aruncaExceptieProbabilitate(); dictionar[poz].setTitlu(titlu); }
void CarteRepoMap::modificaAutor(int poz, const std::string& autor) { aruncaExceptieProbabilitate(); dictionar[poz].setAutor(autor); }
void CarteRepoMap::modificaGen(int poz, const std::string& gen) { aruncaExceptieProbabilitate(); dictionar[poz].setGen(gen); }
void CarteRepoMap::modificaAn(int poz, int an) { aruncaExceptieProbabilitate(); dictionar[poz].setAn(an); }