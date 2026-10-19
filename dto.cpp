#include "dto.h"
#include <string>
using std::string;

const string& dto::gettype() const noexcept{
	return this->type;
}

int dto::getcount() const noexcept {
	return this->count;
}


