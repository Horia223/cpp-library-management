#include <fstream>  //fisiere
#include "cos.h"
#include "Exceptii.h"

void Cos::exportCosCsv(const string& numeFisier) const {
	string numeFinal = numeFisier + ".csv";
	std::ofstream out(numeFinal);

	if (!out.is_open()) {
		throw RepoException("Eroare la deschiderea fisierului export");
	}

	out << "Titlu,Autor,Gen,Anul\n";

	for (const auto& c : this->cos) {
		out << c.getTitlu() << ",";
		out << c.getAutor() << ",";
		out << c.getGen() << ",";
		out << c.getAn() << std::endl;
	}
	out.close();
}