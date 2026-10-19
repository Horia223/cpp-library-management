#pragma once
#include <string>
#include <map>
//#include <iostream>
using std::string;
//using std::ostream;


class dto {

private:
	string type;
	int count;

public:

	dto() noexcept : type{ "" }, count{ 0 } {}

	dto(string& t, int c) : type{ t }, count{ c } {}


	const string& gettype() const noexcept;
	int getcount() const noexcept;
};