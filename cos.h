#pragma once
#include "carte.h"
#include <vector>
#include <algorithm>
#include <random>

using std::vector;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Cos
{
private:
    vector<Carte> cos;
    vector<Observer*> observatori;

    void notify() {
        for (auto obs : observatori) {
            obs->update();
        }
    }

public:
    Cos() = default;

    void addObserver(Observer* obs) {
        observatori.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        auto it = std::find(observatori.begin(), observatori.end(), obs);
        if (it != observatori.end()) {
            observatori.erase(it);
        }
    }

    void golesteCos() noexcept {
        cos.clear();
        notify();
    }

    void adauga(const Carte& c) {
        cos.push_back(c);
        notify();
    }

    const vector<Carte>& getAllCos() const noexcept {
        return cos;
    }

    void exportCosCsv(const string& numeFisier) const;

    size_t dimensiune() const noexcept {
        return cos.size();
    }

    void genereazaRandom(const vector<Carte>& toate, int nr) {
        cos.clear();
        if (toate.size() == 0) return;
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<size_t> dist(0, toate.size() - 1);
        for (int i = 0; i < nr; i++) {
            cos.push_back(toate.at(dist(mt)));
        }
        notify();
    }
};