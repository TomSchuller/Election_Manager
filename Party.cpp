/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on a party
*****************************************************/

#include "Party.h"

Party::Party() :_name(), _id(UNDEFINED)
{
}

Party::Party(const string name, const Citizen& candidate, int serial_number) : _name(name), _candidate(candidate), _id(serial_number)
{
}

Party::Party(const Party& other) : _name(other.get_name()), _id(other.get_id()), _candidate(other.get_candidate()), _total_votes(other.get_total_votes()), _total_representatives(other.get_total_representatives()), _representatives(other.get_representatives())
{
}

Party::~Party()
{
}

bool Party::set_name(const string name) {
    _name = name;
    return true;
}

bool Party::set_candidate(const Citizen& candidate) {
    this->_candidate = candidate;
    return true;
}

bool Party::set_serial_number(int serial_number) {
    this->_id = serial_number;
    return true;
}

bool Party::set_total_votes(int total_votes) {
    _total_votes = total_votes;
    return true;
}

bool Party::set_total_representatives(int representatives) {
    _total_representatives = representatives;
    return true;
}

bool Party::add_representative(Representative& representative)
{
    try {
        _representatives.push_back(representative);
    }
    catch (bad_alloc& ex) {
        throw;
    }
    return true;
}

Party& Party::operator=(const Party& other) {
    if (this->_id != other.get_id()) {
        this->set_name(other.get_name());
        this->set_serial_number(other.get_id());
        this->set_candidate(other.get_candidate());
        this->set_total_votes(other.get_total_votes());
        this->set_total_representatives(other.get_total_representatives());

        _representatives = other.get_representatives();
    }
    return *this;
}

bool Party::operator>(const Party& other) const
{
    return (this->get_total_representatives() > other.get_total_representatives());
}

bool Party::operator<(const Party& other) const
{
    return (this->get_total_representatives() < other.get_total_representatives());
}

bool Party::operator==(const Party& other) const
{
    return (this->get_total_representatives() == other.get_total_representatives());
}


void Party::save(ostream& out) const
{
    int length = _name.size();
    try {
        out.write(rcastc(&length), sizeof(length));
        out.write(_name.c_str(), length);
        out.write(rcastc(&_id), sizeof(_id));
        out.write(rcastc(&_total_votes), sizeof(_total_votes));
        out.write(rcastc(&_total_representatives), sizeof(_total_representatives));
        _candidate.save(out);
        if (!out.good()) {
            throw runtime_error("ERROR! Couldn't write to file!");
        }    
    }
    catch (runtime_error& ex) {
        throw;
    }
     catch (exception& ex) {
        throw;
    }

}

void Party::load(istream& in)
{
    int length;
    try {
        in.read(rcast(&length), sizeof(length));
        if (!in.good()) {
            throw runtime_error("ERROR! Couldn't read from file!");
        }   
        _name.resize(length);
        in.read(&_name[0], length);
        in.read(rcast(&_id), sizeof(_id));
        in.read(rcast(&_total_votes), sizeof(_total_votes));
        in.read(rcast(&_total_representatives), sizeof(_total_representatives));
        _candidate.load(in);
    }
    catch (runtime_error& ex) {
        throw;
    }
     catch (exception& ex) {
        throw;
    }
}