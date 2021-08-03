/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on a citizen.
*****************************************************/

#include "Citizen.h"


Citizen::Citizen(const string name, int id, int year) : _name(name), _id(id), _year(year)
{
	if (id > 999999999 || id < 100000000) throw invalid_argument("ERROR! Please input a 9 digit number for the ID!");
}

Citizen::Citizen() noexcept : _name(), _id(UNDEFINED), _year(0)
{
}

Citizen::Citizen(const Citizen& other) noexcept : _name(other.get_name()), _id(other.get_id()), _year(other.get_year()), _party_vote(other.get_party_vote())
{
}

Citizen::~Citizen() noexcept
{
}

bool Citizen::set_name(const string name)
{
	_name = name;
	return true;
}

bool Citizen::set_id(int id) noexcept {
	this->_id = id;
	return true;
}

bool Citizen::set_year(int year) noexcept {
	this->_year = year;
	return true;
}

bool Citizen::set_party_vote(int party_vote) noexcept {
	this->_party_vote = party_vote;
	return true;
}

const Citizen& Citizen::operator=(const Citizen& other) {
	if (this != &other) {
		this->set_name(other.get_name());
		this->set_id(other.get_id());
		this->set_year(other.get_year());
		this->set_party_vote(other.get_party_vote());
	}
	return *this;
}

bool Citizen::operator>(const Citizen& other) const noexcept
{
	return (this->get_id() > other.get_id());
}

bool Citizen::operator<(const Citizen& other) const noexcept
{
	return (this->get_id() < other.get_id());
}

bool Citizen::operator==(const Citizen& other) const noexcept
{
	return (this->get_id() == other.get_id());
}

void Citizen::save(ostream& out) const
{
	int length = _name.size();
	out.write(rcastc(&length), sizeof(length));
	out.write(_name.c_str(), _name.size());
	out.write(rcastc(&_id), sizeof(int));
	out.write(rcastc(&_year), sizeof(_year));
	out.write(rcastc(&_party_vote), sizeof(_party_vote));
	if (!out.good()) {
		throw runtime_error("ERROR! Couldn't write to file!");
	}
}

void Citizen::load(istream& in)
{
	int length;
	in.read(rcast(&length), sizeof(int));
	if (!in.good()) {
		throw runtime_error("ERROR! Couldn't read from file!");
	}
	_name.resize(length);
	in.read(&_name[0], length);
	in.read(rcast(&_id), sizeof(_id));
	in.read(rcast(&_year), sizeof(_year));
	in.read(rcast(&_party_vote), sizeof(_party_vote));
}