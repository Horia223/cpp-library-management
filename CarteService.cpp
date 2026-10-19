#include "CarteService.h"
#include <algorithm>
#include <random>

void CarteService::adaugaCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c = Carte(titlu, autor, gen, an);
	this->val.valideaza(c);
	this->repo.adauga(c);

    //undo
	size_t poz = this->repo.getAll().size() - 1;
	undoActions.push_back(std::make_unique<UndoAdauga>(this->repo, static_cast<int>(poz)));
}



void CarteService::stergeCarte(int poz) {
	int pozReala = poz - 1;
	Carte carteStearsa = this->repo.getCarte(pozReala);

	this->repo.stergeDupaPozitie(pozReala);

	undoActions.push_back(std::make_unique<UndoSterge>(this->repo, carteStearsa, pozReala));
}



const  vector<Carte>& CarteService::getAll() const noexcept {
	return this->repo.getAll();

}

const Carte& CarteService::getCarte(int poz) const {
	poz--;
	return this->repo.getCarte(poz);
}



const Carte& CarteService::cautaCarte(const string& titlu, const string& autor) const {
	return repo.cautaCarte(titlu, autor);
}






void CarteService::modificaTitlu(int poz, const string& titlu) {
	poz--;
	Carte carteVeche = this->repo.getCarte(poz);

	this->repo.modificaTitlu(poz, titlu);

	undoActions.push_back(std::make_unique<UndoModifica>(this->repo, carteVeche, poz));


}

void CarteService::modificaAutor(int poz, const string& autor) {
	poz--;
	Carte carteVeche = this->repo.getCarte(poz);

	this->repo.modificaAutor(poz, autor);

	undoActions.push_back(std::make_unique<UndoModifica>(this->repo, carteVeche, poz));




}

void CarteService::modificaGen(int poz, const string& gen) {
	poz--;
	Carte carteVeche = this->repo.getCarte(poz);

	this->repo.modificaGen(poz, gen);

	undoActions.push_back(std::make_unique<UndoModifica>(this->repo, carteVeche, poz));


}

void CarteService::modificaAn(int poz, int an) {
	poz--;
	Carte carteVeche = this->repo.getCarte(poz);

	this->repo.modificaAn(poz, an);

	undoActions.push_back(std::make_unique<UndoModifica>(this->repo, carteVeche, poz));
}


vector<Carte> CarteService::filtrare_titlu(const string& titlu) const {
	vector<Carte> rez;
	const auto& toate = this->repo.getAll();
	
	std::copy_if(
		toate.begin(),
		toate.end(),
		std::back_inserter(rez), //unde baga cartile gasita/destinatia
		[titlu](const Carte& c) {
			return c.getTitlu() == titlu;
		}
	);
	return rez;
}


vector<Carte> CarteService::filtrare_an(int an) const noexcept {
	vector<Carte> rez;
	const auto& toate = this->repo.getAll();
	std::copy_if(

		toate.begin(),
		toate.end(),
		std::back_inserter(rez),
		[an](const Carte& c) noexcept {
			return c.getAn() == an;
		}
	);
	return rez;


}


//tip de functie comparator
typedef bool (*Comparator)(const Carte&, const Carte&);

vector<Carte> CarteService::sorteaza(Comparator maiMic) const {//facem doar intr un mod, crescator
	vector<Carte> listaSortata = repo.getAll(); // copie la lista, pentru a sorta fara a sa stricam ordinea din repo

	if (maiMic == nullptr) return listaSortata; //daca s a dat o functie de comparare vida, nu facem nimic

	std::sort(listaSortata.begin(), listaSortata.end(), maiMic);
	return listaSortata;
}

bool CarteService::comparaTiltu(const Carte& c1, const Carte& c2) noexcept {
	return c1.getTitlu() < c2.getTitlu();
}

bool CarteService::comparaAutor(const Carte& c1, const Carte& c2) noexcept {
	return c1.getAutor() < c2.getAutor();
}

bool CarteService::comparaAnGen(const Carte& c1, const Carte& c2) noexcept {
	if (c1.getAn() < c2.getAn()) {
		return true;
	}
	if (c1.getAn() == c2.getAn()) {
		return c1.getGen() < c2.getGen();
	}
	return false;
}

//===============COS=======================

void CarteService::cosAdauga(const string& titlu) {
	const auto& toate = this->repo.getAll();
	auto it = std::find_if(toate.begin(), toate.end(), [titlu](const Carte& c) {
		return c.getTitlu() == titlu;
	});

	if (it != toate.end()) {
		cosCurent.adauga(*it);
	}
	else {
		throw RepoException("Nu exista nicio carte cu acest titlu");
	}
}

void CarteService::golesteCosService() noexcept {
	this->cosCurent.golesteCos();
}

const vector<Carte>& CarteService::getAllCosService() const noexcept {
	return this->cosCurent.getAllCos();
}

void CarteService::exportCosCsvService(const string& numeFisier) {
	this->cosCurent.exportCosCsv(numeFisier);
}

size_t CarteService::dimensiuneCos() const noexcept {
	return this->cosCurent.dimensiune();
}

void CarteService::cosGenereaza(const int nr) {

	const auto& toate = repo.getAll();
	if (toate.size() == 0) return;
	static std::mt19937 mt{ std::random_device{}() };

	std::uniform_int_distribution<size_t> dist(0, toate.size() - 1);

	for (int i = 0; i < nr; i++) {
		const size_t rndIdx = dist(mt); // numarul nou
		this->cosCurent.adauga(toate.at(rndIdx));
	}

}

map<string, dto> CarteService::getGenDto() const {
	map<string, dto> dictionar;
	const auto& toate = repo.getAll();

	for (const auto& c : toate) {
		string genCurent = c.getGen();

		// verificam daca genul exista deja
		if (dictionar.find(genCurent) == dictionar.end()) {
			// daca nu exista adaugam unul cu count 1
			dictionar[genCurent] = dto(genCurent, 1);
		}
		else {
			// daca exista incrementam count
			int count = dictionar[genCurent].getcount();
			dictionar[genCurent] = dto(genCurent, count + 1);
		}
	}
	return dictionar;
}

//========Undo


void CarteService::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista actiuni pentru undo!");
	}

    // execute the last undo action and remove it
	undoActions.back()->doUndo();
	undoActions.pop_back();
}


