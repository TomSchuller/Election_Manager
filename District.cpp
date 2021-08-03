/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on a district.
*****************************************************/
#include "District.h"


District::District() noexcept : _name(), _serial_number(UNDEFINED), _representatives_num(0)
{
}

District::District(const string name, int serial_number, int representatives) : _name(name), _serial_number(serial_number), _representatives_num(representatives)
{
    if (representatives < 0) throw invalid_argument("Error! You've entered an invalid number of representatives!    Must be an integer above 0!");
}

District::District(const District& other) noexcept : _name(other.get_name()), _serial_number(other.get_serial_number()), _representatives_num(other.get_representatives_number())
{
}

District::~District() noexcept
{
}

float District::get_percentage(void) const
{
    if (_citizens.size() == 0) throw runtime_error("Division by zero");
    return ((static_cast<float>(_total_votes) / static_cast<float>(_citizens.size())) * 100);
}

bool District::set_name(const string name) {
    _name = name;
    return true;
}

bool District::set_serial_number(int serial_number) noexcept {
    this->_serial_number = serial_number;
    return true;
}

bool District::set_representatives(int representatives)  noexcept {
    this->_representatives_num = representatives;
    return true;
}

bool District::set_total_votes(int total_votes)  noexcept {
    this->_total_votes = total_votes;
    return true;
}

Citizen* District::add_citizen(const Citizen& citizen) { 
    try {
        _citizens.push_back(citizen);
        return &(_citizens.back());
    }
    catch (exception& ex) {
        throw;
    }
}

District& District::operator=(const District& other) {
    if (!(*this == other)) {
        this->set_name(other.get_name());
        this->set_serial_number(other.get_serial_number());
        this->set_representatives(other.get_representatives_number());
        this->set_total_votes(other.get_total_votes());

        // Resize citizens array to new size.
        _citizens = other.get_citizens();
    }
    return *this;
}

bool District::operator>(const District& other) const
{
    return (_name.compare(other.get_name()) > 0);
}

bool District::operator<(const District& other) const
{
    return (_name.compare(other.get_name()) < 0);
}

bool District::operator==(const District& other) const
{
    return (_name.compare(other.get_name()) == 0);
}

int District::get_party_votes(int party_number) const {
    int votes = 0;
    // Get number of citizens who voted for he desired party
    try {
        list<Citizen>::const_iterator itr = _citizens.begin();
        while (itr != _citizens.end()) {
            if (itr->get_party_vote() == party_number) {
                votes++;
            }
            ++itr;
        }
        return votes;
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
}

int District::get_party_reps(int party_number) const {
    // Get total votes for the party and calculate the representatives won
    try {
        int votes = get_party_votes(party_number);
        if (_total_votes == 0)  throw runtime_error("Division by zero");
        float total = (((static_cast<float>(votes) / static_cast<float>(_total_votes)) * static_cast<float>(_representatives_num)) + ROUND);
        if ((int)total > _representatives_num) return _representatives_num;
        return (int)total;
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (runtime_error& ex) {
        throw;
    }

}

float District::get_party_percentage(int party_num) const
{
    try {
        int party_votes = get_party_votes(party_num);
        if (_total_votes == 0)  throw runtime_error("Division by zero");
        // Return percentage of votes for this party from district's total votes
        return (static_cast<float>(party_votes) / static_cast<float>(_total_votes)) * 100;
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (runtime_error& ex) {
        throw;
    }
}

void District::save(ostream& out) const
{
    DISTRICT_TYPE type = this->get_type();
    int length = _name.size();
    int citizen_length = _citizens.size();

    out.write(rcastc(&type), sizeof(type));
    out.write(rcastc(&length), sizeof(length));
    out.write(_name.c_str(), length);
    out.write(rcastc(&_serial_number), sizeof(_serial_number));
    out.write(rcastc(&_representatives_num), sizeof(_representatives_num));
    out.write(rcastc(&_total_votes), sizeof(_total_votes));
    out.write(rcastc(&(citizen_length)), sizeof(citizen_length));
    list<Citizen>::const_iterator itr = _citizens.begin();
    while (itr != _citizens.end()) {
        itr->save(out);
        ++itr;
    }
    if (!out.good()) {
        throw runtime_error("ERROR! Couldn't write to file!");
    }
}

void District::load(istream& in)
{
    int length, citizen_len;
    in.read(rcast(&length), sizeof(int));
    if (!in.good()) {
        throw runtime_error("ERROR! Couldn't read from file!");
    }
    _name.resize(length);
    in.read(&_name[0], length);
    in.read(rcast(&_serial_number), sizeof(_serial_number));
    in.read(rcast(&_representatives_num), sizeof(_representatives_num));
    in.read(rcast(&_total_votes), sizeof(_total_votes));
    in.read(rcast(&citizen_len), sizeof(citizen_len));
    int i = 0;
    Citizen c;
    try {
        while (i < citizen_len) {
            c.load(in);
            _citizens.push_back(c);
            ++i;
        }
    }
    catch (bad_alloc& ex) {
        throw;
    }
}

Citizen* District::find_by_id(int id) {
    list<Citizen>::iterator curr = _citizens.begin();
    list<Citizen>::iterator end = _citizens.end();
    // Go through list
    for (; curr != end; ++curr) {
        if (curr->get_id() == id)
            return &(*curr);        
    }
    return nullptr; // else didn't find
}