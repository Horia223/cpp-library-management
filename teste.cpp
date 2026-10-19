#include <assert.h>
#include "CarteService.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "CarteRepoFile.h"


// Teste pentru clasa Carte
void testDomain() {
	Carte c{ "Titlu", "Autor", "Gen", 2000 };
	assert(c.getTitlu() == "Titlu");
	assert(c.getAutor() == "Autor");
	assert(c.getGen() == "Gen");
	assert(c.getAn() == 2000);

	c.setTitlu("Nou");
	c.setAutor("NouaA");
	c.setGen("GenNou");
	c.setAn(2020);
	assert(c.getTitlu() == "Nou");
	assert(c.getAutor() == "NouaA");
	assert(c.getGen() == "GenNou");
	assert(c.getAn() == 2020);


}

void testOperator() {
	Carte c{ "a","b","c",2000 };
	std::stringstream s;
	s << c;
	assert(s.str() == "Titlu: a|Autor: b|Gen: c|Anul Aparitiei: 2000");

}



// Teste pentru Repository
void testRepo() {
	CarteRepo repo;
	Carte c{ "T", "A", "G", 2000 };


	repo.adauga(c);
	assert(repo.getAll().size() == 1);
	assert(repo.exista(c) == true);
	Carte cs = Carte("a", "b", "c", 1900);
	assert(repo.exista(cs) == false);

	//test cautare succes
	const auto& gasit = repo.cautaCarte("T", "A");
	assert(gasit.getAn() == 2000);

	// test cautare exceptie
	try {
		repo.cautaCarte("N", "sdsds");
		//assert(false); // Nu ajunge aici, adica nu ar trebui
	}
	catch (const RepoException) {
		assert(true);
	}

	//Test modificari
	repo.modificaTitlu(0, "T2");
	repo.modificaAutor(0, "A2");
	repo.modificaGen(0, "G2");
	repo.modificaAn(0, 2010);
	auto cModif = repo.getAll()[0];
	assert(cModif.getTitlu() == "T2");
	assert(cModif.getAn() == 2010);
	Carte c_t = repo.getCarte(0);
	assert(c_t.getTitlu() == "T2");
	assert(c_t.getAn() == 2010);
	assert(c_t.getGen() == "G2");
	assert(c_t.getAutor() == "A2");
	try {
		repo.valideaza_pozitie(1, repo.getAll().size());
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	// Test stergere
	repo.stergeDupaPozitie(0);
	assert(repo.getAll().size() == 0);


}

// teste pentru service
void testService() {
	CarteRepo repo;
	CarteValidator val;
	CarteService serv(repo, val);

	serv.adaugaCarte("T", "A", "G", 2000);
	assert(serv.getAll().size() == 1);
	try {
		serv.adaugaCarte("", "A", "G", 2000);
		assert(false);
	}
	catch (ValidareException) {
		assert(true);
	}

	// test cautare service
	auto c = serv.cautaCarte("T", "A");
	assert(c.getGen() == "G");
	Carte carte = serv.getCarte(1);
	assert(carte.getTitlu() == "T");


	serv.modificaTitlu(1, "Tm");
	serv.modificaAn(1, 2021);
	serv.modificaGen(1, "nou");
	serv.modificaAutor(1, "autor_nou");
	assert(serv.getAll()[0].getTitlu() == "Tm");
	assert(serv.getAll()[0].getAn() == 2021);
	assert(serv.getAll()[0].getGen() == "nou");
	assert(serv.getAll()[0].getAutor() == "autor_nou");

	// Test stergere
	serv.stergeCarte(1);
	assert(serv.getAll().size() == 0);

	//Test Filtrare
	serv.adaugaCarte("a", "b", "c", 1900);
	serv.adaugaCarte("a", "d", "d", 1800);
	serv.adaugaCarte("b", "da", "d", 1600);
	serv.adaugaCarte("a", "c", "c", 1500);
	serv.adaugaCarte("d", "b", "b", 1900);
	serv.adaugaCarte("c", "r", "a", 2000);

	vector<Carte> filtrate = serv.filtrare_titlu("a");
	assert(filtrate.size() == 3);
	assert(filtrate[0].getTitlu() == "a");
	assert(filtrate[1].getTitlu() == "a");
	assert(filtrate[2].getTitlu() == "a");

	vector<Carte> filtrate_an = serv.filtrare_an(1900);
	assert(filtrate_an.size() == 2);
	assert(filtrate_an[0].getAn() == 1900);
	assert(filtrate_an[1].getAn() == 1900);

	vector<Carte> sortate_titlu = serv.sorteaza(serv.comparaTiltu);
	assert(sortate_titlu[0].getTitlu() == "a");
	assert(sortate_titlu[3].getTitlu() == "b");
	assert(sortate_titlu[4].getTitlu() == "c");
	assert(sortate_titlu[5].getTitlu() == "d");

	vector<Carte> sortate_autor = serv.sorteaza(serv.comparaAutor);
	assert(sortate_autor[0].getAutor() == "b");
	assert(sortate_autor[2].getAutor() == "c");
	assert(sortate_autor[3].getAutor() == "d");
	assert(sortate_autor[4].getAutor() == "da");
	assert(sortate_autor[5].getAutor() == "r");

	vector<Carte> sortate_angen = serv.sorteaza(serv.comparaAnGen);
	assert(sortate_angen[0].getAn() == 1500);
	assert(sortate_angen[1].getAn() == 1600);
	assert(sortate_angen[2].getAn() == 1800);
	assert(sortate_angen[3].getAn() == 1900);
	assert(sortate_angen[4].getAn() == 1900);
	assert(sortate_angen[5].getAn() == 2000);




}
void testExceptiiSiValidator() {
	// Test ValidareException
	CarteValidator val;
	Carte c_gresita{ "", "", "", -1 };
	try {
		val.valideaza(c_gresita);
		assert(false);
	}
	catch (const ValidareException& ex) {
		string msg = ex.getMesaj();
		assert(msg.length() > 0);
	}


	CarteRepo repo;
	Carte c{ "Titlu", "Autor", "Gen", 2024 };
	repo.adauga(c);
	try {
		repo.adauga(c); // Duplicat
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Cartea exista deja in lista!");
	}


	try {
		repo.cautaCarte("Inexistent", "Nimeni");
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Cartea nu a fost gasita!");
	}
}




void testVectorDinamic() {
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	// test operator=
	vector<int> v2;
	v2 = v1;
	assert(v2.size() == 3);
	assert(v2[1] == 20);


	v2 = v2;
	assert(v2.size() == 3);


	v1.erase(v1.begin() + 0);
	assert(v1.size() == 2);
	assert(v1[0] == 20);
	assert(v1[1] == 30);



}

void testCos() {
	Cos cos;
	Carte c1{ "T1", "A1", "G1", 2000 };
	Carte c2{ "T2", "A2", "G2", 2010 };

	cos.adauga(c1);
	cos.adauga(c2);
	assert(cos.getAllCos().size() == 2);
	assert(cos.dimensiune() == 2);

	cos.golesteCos();
	assert(cos.getAllCos().empty());

	// test export
	cos.adauga(c1);
	cos.exportCosCsv("test_f");

	// verificam daca putem deschide fisierul
	std::ifstream in("test_f.csv");
	assert(in.is_open());
	in.close();
}






void testCosService() {
	CarteRepo repo;
	CarteValidator val;
	CarteService serv(repo, val);


	serv.adaugaCarte("Titlu1", "Autor1", "SF", 2000);
	serv.adaugaCarte("Titlu2", "Autor2", "Drama", 2010);
	serv.adaugaCarte("Titlu3", "Autor3", "SF", 2020);


	serv.cosAdauga("Titlu1");
	assert(serv.dimensiuneCos() == 1);

	try {
		serv.cosAdauga("Inexistent");
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}
	//test get all si golire
	auto inCos = serv.getAllCosService();
	assert(inCos.size() == 1);
	assert(inCos[0].getTitlu() == "Titlu1");

	serv.golesteCosService();
	assert(serv.dimensiuneCos() == 0);

	//  test generare random
	serv.cosGenereaza(2);
	assert(serv.dimensiuneCos() == 2);

	serv.golesteCosService();
	serv.cosGenereaza(10);
	assert(serv.dimensiuneCos() == 10);

	// test dto
	auto stats = serv.getGenDto();

	assert(stats.size() == 2); 
	assert(stats["SF"].getcount() == 2);
	assert(stats["Drama"].getcount() == 1);
	assert(stats["SF"].gettype() == "SF");

	// test export
	try {
		serv.exportCosCsvService("test_export");
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}




void testInsereazasiSetPoz() {
	CarteRepo repo;
	Carte c1{ "Titlu1", "Autor1", "Gen1", 2000 };
	Carte c2{ "Titlu2", "Autor2", "Gen2", 2001 };

	repo.adauga(c1);

	// Test insereaza
	repo.insereaza(0, c2); //inseram la inceput, ordinea va fi: c2,c1
	assert(repo.getAll().size() == 2);
	assert(repo.getAll()[0].getTitlu() == "Titlu2");
	assert(repo.getAll()[1].getTitlu() == "Titlu1");

	//test exceptie insereaza
	try {
		repo.insereaza(-1, c1);
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Pozitie invalida pentru inserare!");
	}

	// test setCartePePozitie (suprascriere)
	Carte c3{ "Titlu3", "Autor3", "Gen3", 2002 };
	repo.setCartePePozitie(1, c3); // Inlocuim c1 cu c3
	assert(repo.getAll()[1].getTitlu() == "Titlu3");
}


void testRepoFile() {
	//cream un fisier de test gol
	std::ofstream out("test_repo.txt");
	out.close();

	// testam scrierea si toate functiile suprascrise
	CarteRepoFile frepo("test_repo.txt");
	Carte c1{ "T1", "A1", "G1", 2000 };
	Carte c2{ "T2", "A2", "G2", 2010 };

	frepo.adauga(c1);
	frepo.insereaza(0, c2); // Vectorul e: T2, T1
	frepo.setCartePePozitie(1, Carte{ "T3", "A3", "G3", 2020 }); // Vector: T2, T3

	// testam toate modificarile sa fim siguri ca scriu in fisier
	frepo.modificaTitlu(0, "TT");
	frepo.modificaAutor(0, "AA");
	frepo.modificaGen(0, "GG");
	frepo.modificaAn(0, 1999);
	frepo.stergeDupaPozitie(1); // stergem t3, ramane daor prima carte editata

	// test citire
	CarteRepoFile frepo2("test_repo.txt");
	assert(frepo2.getAll().size() == 1);
	assert(frepo2.getAll()[0].getTitlu() == "TT");
	assert(frepo2.getAll()[0].getAn() == 1999);
}
//	teste exceptie deschidere fisier invalid
//	try {
//		CarteRepoFile fisierInvalid("z/xx/f\\\invalid\n.txt");
//		fisierInvalid.adauga(c1); 
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//}


void testUndo() {
	CarteRepo repo;
	CarteValidator val;
	CarteService serv(repo, val);

	// test excepti nu exista istoric
	try {
		serv.undo();
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Nu mai exista actiuni pentru undo!");
	}

	
	serv.adaugaCarte("T1", "A1", "G1", 2000);
	serv.adaugaCarte("T2", "A2", "G2", 2001);
	

	//undo adaugareE
	serv.undo(); // anuleaza adaugarea lui t2
	assert(serv.getAll().size() == 1);
	assert(serv.getAll()[0].getTitlu() == "T1");

	// stergere
	serv.stergeCarte(1); //stergem t1
	assert(serv.getAll().size() == 0);
	serv.undo(); // anuleaza stergerea, readuce t1 pe pozitia potribita
	assert(serv.getAll().size() == 1);
	assert(serv.getAll()[0].getTitlu() == "T1");

	// test modificare
	serv.modificaTitlu(1, "T_Nou");
	assert(serv.getAll()[0].getTitlu() == "T_Nou");
	serv.undo();
	assert(serv.getAll()[0].getTitlu() == "T1"); // s a schimbat la original

	serv.modificaAutor(1, "A_Nou");
	serv.undo();
	assert(serv.getAll()[0].getAutor() == "A1");

	serv.modificaGen(1, "G_Nou");
	serv.undo();
	assert(serv.getAll()[0].getGen() == "G1");

	serv.modificaAn(1, 9999);
	serv.undo();
	assert(serv.getAll()[0].getAn() == 2000);
}

void testToate() {
	testDomain();
	testRepo();
	testService();
	testOperator();
	testExceptiiSiValidator();
	testVectorDinamic();
	testCos();
	testCosService();
	testRepoFile();
	testUndo();
	testInsereazasiSetPoz();
}
