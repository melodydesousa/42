#include "Data.hpp"

Data::Data() : i(0), test("ok") {
    return;
}

Data::Data(Data const &cpy) : i(cpy.i), test(cpy.test){
    *this = cpy;
    return;
}

Data& Data::operator=(Data const &assign) {
    (void)assign;
    return *this;
}

Data::~Data() {
    return;
}

uintptr_t Data::serialize(Data* ptr) {
	return(reinterpret_cast<uintptr_t>(ptr));
}

Data* Data::deserialize(uintptr_t raw) {
	return(reinterpret_cast<Data*>(raw));
}
