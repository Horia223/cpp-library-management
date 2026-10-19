#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;


// Excepție pentru Repository pt element inexistent sau dublura
class RepoException {
private:
	string mesaj;
public:
	RepoException(const string& m) : mesaj{ m } {}
	string getMesaj() const { return mesaj; }
};

// Excepție pentru Validarea datelor
class ValidareException {
private:
	vector<string> mesaje;
public:
	ValidareException(const vector<string>& erori) : mesaje{ erori } {}
	string getMesaj() const {


		string Msg = "";
		for (const string& e : mesaje) {
			Msg += e + "\n";
		}
		return Msg;
	}

};