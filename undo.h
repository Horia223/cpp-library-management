#pragma once
#include "carte.h"
#include "CarteRepoMap.h"

// CLASA ABSTRACTA
class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

// undo adaugare
class UndoAdauga : public ActiuneUndo {
private:
    int pozitie;
    RepoAbstract& repo;
public:
    UndoAdauga(RepoAbstract& r, int poz) : repo{ r }, pozitie{ poz } {}
    void doUndo() override {
        // daca s a adaugat, undo inseamna sa o stergem dupa pozitia ei
        repo.stergeDupaPozitie(pozitie);
    }
};

// undo stergere
class UndoSterge : public ActiuneUndo {
private:
    Carte carteStearsa;
    int pozitie;
    RepoAbstract& repo;
public:
    UndoSterge(RepoAbstract& r, const Carte& c, int poz) : repo{ r }, carteStearsa{ c }, pozitie{ poz } {}
    void doUndo() override {
        //daca s a sters, undo inseamna sa o adaugam inapoi pe pozitia initiala
        repo.insereaza(pozitie, carteStearsa);
    }
};

// undo modificare
class UndoModifica : public ActiuneUndo {
private:
    Carte carteVeche;
    int pozitie;
    RepoAbstract& repo;
public:
    UndoModifica(RepoAbstract& r, const Carte& c, int poz) : repo{ r }, carteVeche{ c }, pozitie{ poz } {}
    void doUndo() override {
        // daca s a modificat o carte, undo inseamna sa punem cartea veche pe aceeasi pozitie
        repo.setCartePePozitie(pozitie, carteVeche);
    }
};