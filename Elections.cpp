/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on an election round.
*****************************************************/

#include "Elections.h"
enum class MONTHS { January = 1, February, March, April, May, June, July, August, September, October, November, December };
enum class DAYS { Start = 1, End_February = 28, End1 = 30, End2 = 31 };

Elections::Elections(int year, int month, int day) : _year(year), _month(month), _day(day)
{
    try {
        if (year < 0)
            throw invalid_argument("Error! The year must be positive number!");

        auto months = static_cast<MONTHS>(month);
        if (months < MONTHS::January || months > MONTHS::December)
            throw invalid_argument("Error! The month must be between a number 1 - 12!");

        DAYS days = static_cast<DAYS>(day);
        switch (months)
        {
        case MONTHS::February: // assumption always 28
        {
            if (days < DAYS::Start || days > DAYS::End_February)
                throw invalid_argument("Error! In this Month the day must be between a number 1 - 28!");
            break;
        }
        case MONTHS::April: case MONTHS::June: case MONTHS::September: case MONTHS::November: //30
        {
            if (days < DAYS::Start || days > DAYS::End1)
                throw invalid_argument("Error! In this Months the day must be between a number 1 - 30!");
            break;
        }
        default: // 31
        {
            if (days < DAYS::Start || days > DAYS::End2)
                throw invalid_argument("Error! In this Months the day must be between a number 1 - 31!");
            break;
        }
        }
    }
    catch (invalid_argument& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }

}

Elections::Elections(istream& in) : _districts(in)
{
    load(in);
}

Elections::~Elections()
{
}

bool Elections::set_date(int year, int month, int day)
{
    this->_year = year;
    this->_month = month;
    this->_day = day;
    return true;
}

void Elections::add_district(const string name, int representatives_count, int type) {
    try {
        _districts.add_district(name, representatives_count, type);
    }
    catch (invalid_argument& ex) {
        throw;
    }
    catch (bad_alloc& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::add_citizen(const string name, int citizen_id, int year, int district_number) {
    // if created citizen was successfull
    try {
        Citizen citizen(name, citizen_id, year);
        is_valid_age(year);

        District* pdistrict = find_district(district_number);
        if (pdistrict == nullptr) {
            throw invalid_argument("Error! The district doesn't exist!");
        }

        // If citizen is in district return false
        for (int i = 0; i < _districts.getLength(); i++) {
            list<Citizen>::const_iterator itr = get_district_array().get(i).get_citizens().begin();
            while (itr != get_district_array().get(i).get_citizens().end()) {
                if (itr->get_id() == citizen_id) {
                    throw invalid_argument("Error! The citizen has been added already!");
                }
                ++itr;
            }
        }
        _voters_notebook[citizen_id] = _districts.find_district_by_serial_number(district_number)->add_citizen(citizen);
    }

    catch (runtime_error& ex) {
        throw;
    }
    catch (invalid_argument& ex) {
        throw;
    }
    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::add_party(const string name, int candidate_id) {
    // If added party was successfull
    try {
        Citizen* pcitizen = _voters_notebook[candidate_id];
        if (pcitizen != nullptr) {
            if (find_party(name) == nullptr) {
                _parties.push_back({ name, *pcitizen, _parties.size() });
            }
            else throw invalid_argument("Error! The party has been added already!");
        }
        else throw invalid_argument("Error! The candidate doesn't exist!");
    }

    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::add_representative(int representative_id, int party_num, int district_num)
// If added representatives was successfull
{
    try {
        District* pdistrict = find_district(district_num);
        if (pdistrict == nullptr) {
            throw invalid_argument("Error! The district doesn't exist!");
        }

        Citizen* pcitizen = _voters_notebook[representative_id];
        if (pcitizen == nullptr) {
            throw invalid_argument("Error! The citizen doesn't exist!");
        }

        Party* pparty = find_party(party_num);
        if (pparty == nullptr) {
            throw invalid_argument("Error! The party doesn't exist!");
        }

        if (find_representative(representative_id) != nullptr) {
            throw invalid_argument("Error! a representative with the same id already exist!");
        }

        Representative rep(pcitizen, district_num);
        // Add representative to party
        Party& party = *pparty;
        party.add_representative(rep);
    }

    catch (invalid_argument& ex) { // find district
        throw;
    }
    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::is_valid_age(int birth_year) {
    if ((_year - birth_year) < 18)
        throw invalid_argument("Error! a representative with the same id already exist!");
}

District* Elections::find_district(int district_num)
{
    try {
        // find by district array
        return _districts.find_district_by_serial_number(district_num); // return null if it didnt find
    }
    catch (invalid_argument& ex){
        throw;
    }
}

Party* Elections::find_party(int party_num)
{
    // find by party array
    try {
        for (auto& _party : _parties) {
            if (_party.get_id() == party_num)
                return &_party;
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (...) {
    }
    return nullptr;
}

Party* Elections::find_party(const string name) {
    int len = _parties.size();
    int serial_num;
    try {
        for (int i = 0; i < len; i++) {
            if (_parties.at(i).get_name().compare(name) == 0) {
                serial_num = _parties.at(i).get_id();
                return find_party(serial_num);
            }
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (...) {
    }
    return nullptr;

}

Representative* Elections::find_representative(int citizen_id) {
    int party_len = _parties.size();
    list <Representative>::const_iterator itr;
    Representative* rep = nullptr;
    try {
        for (int i = 0; i < party_len; i++) {
            for (itr = find_party(i)->get_representatives().begin(); itr != find_party(i)->get_representatives().end(); ++itr) {
                if (itr->get_id() == citizen_id) {
                    *rep = *itr;
                    return rep;
                }
            }
        }
    }
    catch (out_of_range& ex) {
        throw;
    }
    catch (...) {
    }
    return rep;
}

void Elections::cast_vote(int citizen_id, int party_number) {
    int dist_total_votes, party_total_votes;
    int district_number = find_district_by_citizen(citizen_id);
    try {
        if (_voters_notebook[citizen_id]->get_party_vote() != UNDEFINED) {
            throw invalid_argument("Error! You've already casted your vote!");
        }

        if (find_party(party_number) == nullptr) {
            throw invalid_argument("Error! Party doesn't exist!");
        }
        // Add vote to citizen
        _voters_notebook[citizen_id]->set_party_vote(party_number);
        // Add total votes to district
        dist_total_votes = find_district(district_number)->get_total_votes();
        find_district(district_number)->set_total_votes(dist_total_votes + 1);
        // Add total votes to party
        party_total_votes = find_party(party_number)->get_total_votes();
        find_party(party_number)->set_total_votes(party_total_votes + 1);
    }

    catch (invalid_argument& ex) { // find district
        throw;
    }
    catch (exception& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

int Elections::find_district_by_citizen(int citizen_id) {
    // Find district by citizen. Go through all districts.
    int district_length = _districts.getLength();
    try {
        for (int i = 0; i < district_length; i++) {
            auto itr = get_district_array().get(i).get_citizens().begin();
            while (itr != get_district_array().get(i).get_citizens().end()) {
                if (itr->get_id() == citizen_id) {
                    return get_district_array().get(i).get_serial_number();
                }
                ++itr;
            }
        }
        return UNDEFINED;
    }
    catch (out_of_range &ex) {
        throw;
    }
    catch (...) {
    }
}

bool Elections::results_ready(void) {
    int dist_len = _districts.getLength();
    int party_len = _parties.size();
    int citizen_len = _voters_notebook.size();
    // If no party/district/valid voter has been added
    if (party_len == 0 || dist_len == 0 || citizen_len == 0)  throw logic_error("Error! Please enter more data before displaying results!");
    // If no representatives/votes in district
    for (int i = 0; i < dist_len; i++) {
        if (_districts.get(i).get_total_votes() == 0) throw logic_error("Error! There is a district with no votes! GO VOTE NOW!");
    }
    return set_results();
}

bool Elections::set_results(void)
{
    // set total districts and total representatives for all parties
    set_parties_total_reps();
    return true;
}

void Elections::save(ostream& out) const
{
    // save type of election
    out.write(rcastc(&_type), sizeof(_type));

    // save district of election
    _districts.save(out);

    out.write(rcastc(&_day), sizeof(_day));
    out.write(rcastc(&_month), sizeof(_month));
    out.write(rcastc(&_year), sizeof(_year));

    save_parties(out);
    save_representatives(out);
}

void Elections::load(istream& in)
{
    in.read(rcast(&_day), sizeof(_day));
    in.read(rcast(&_month), sizeof(_month));
    in.read(rcast(&_year), sizeof(_year));

    load_parties(in);
    load_voters_notebook();
    load_representatives(in);
}

Party* Elections::get_district_winner(int district_number) {
    int party_len = get_party_array().size();
    int party_num, party_reps, max_reps = UNDEFINED, max_party = UNDEFINED;

    // Go through all parties and find the party that won the most representatives in the district
    try {
        for (int i = 0; i < party_len; i++) {
            party_num = get_party_array().at(i).get_id();
            party_reps = find_district(district_number)->get_party_reps(party_num);
            if (party_reps > max_reps) {
                max_reps = party_reps;
                max_party = party_num;
            }

        }
        return find_party(max_party);
    }
    catch (exception& ex) {
        throw;
    }
}

void Elections::set_parties_total_reps(void) {
    int party_len = get_party_array().size();
    int dist_len = get_district_array().getLength();
    int party_num, dist_num, temp_party_total_reps = 0;
    // Go through all parties
    try {
        for (int i = 0; i < party_len; i++) {
            party_num = get_party_array().at(i).get_id();
            // Go through all districts
            for (int j = 0; j < dist_len; j++) {
                dist_num = get_district_array().get(j).get_serial_number();
                // If unified - winner gets all district reps
                if (get_district_array().get(j).get_type() == DISTRICT_TYPE::UNIFIED) {
                    if (get_district_winner(dist_num)->get_id() == party_num) {
                        temp_party_total_reps += get_district_array().get(j).get_representatives_number();
                    }
                }
                // If divided get only what the party won
                else if (get_district_array().get(j).get_type() == DISTRICT_TYPE::DIVIDED) {
                    temp_party_total_reps += get_district_array().get(j).get_party_reps(party_num);
                }
            }
            // Set total representatives and reset counter
            find_party(party_num)->set_total_representatives(temp_party_total_reps);
            temp_party_total_reps = 0;
        }
    }
    catch (exception& ex) {
        throw;
    }
}

void Elections::save_parties(ostream& out) const
{
    try {
        auto piter = _parties.cbegin();
        auto pend = _parties.cend();
        int len = _parties.size();

        out.write(rcastc(&len), sizeof(int));
        for (; piter != pend; ++piter)
        {
            if (!out.good()) {
                throw runtime_error("ERROR! Couldn't write to file!");
            }
            piter->save(out);
        }
    }
    catch (runtime_error& ex) {
        throw;
    }
}

void Elections::load_parties(istream& in) {
    try {
        int len;
        in.read(rcast(&len), sizeof(len));
        if (!in.good()) {
            throw runtime_error("ERROR! Couldn't read from file!");
        }
        _parties.setLength(len); 

        for (int i = 0; i < len; ++i) {
            if (!in.good()) {
                throw runtime_error("ERROR! Couldn't read from file!");
            }
            _parties[i].load(in);
        }
    }
    catch (bad_alloc& ex) {
        std::cout << "Allocation failed: " << ex.what() << endl;
    }
    catch (runtime_error& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::load_voters_notebook() {
    int dist_len = _districts.getLength();

    for (int i = 0; i < dist_len; i++) {
        int district_num = _districts.get(i).get_serial_number();
        District* d = find_district(district_num);
        auto iter = d->get_citizens().begin();
        for (size_t j = 0; j < d->get_citizens().size(); ++j, ++iter) {
            int num = iter->get_id();
            Citizen* c = d->find_by_id(num);
            _voters_notebook[num] = c;
        }
    }
}

void Elections::save_representatives(ostream& out) const
{
    try
    {
        int num_reps, id, dnum, pnum;
        for (int i = 0; i < _parties.size(); ++i)
        {
            num_reps = _parties.at(i).get_representatives().size();
            out.write(rcastc(&num_reps), sizeof(int)); // number of reps per party
            if (!out.good()) {
                throw runtime_error("ERROR! Couldn't write to file!");
            }
            list <Representative>::const_iterator itr;
            for (itr = _parties.at(i).get_representatives().begin(); itr != _parties.at(i).get_representatives().end(); ++itr)
            {
                id = itr->get_id();
                dnum = itr->get_district_number();
                pnum = _parties.at(i).get_id();
                out.write(rcastc(&id), sizeof(int));
                out.write(rcastc(&dnum), sizeof(int));
                out.write(rcastc(&pnum), sizeof(int));
                if (!out.good()) {
                    throw runtime_error("ERROR! Couldn't write to file!");
                }
            }
        }
    }
    catch (bad_alloc& ex) {
        std::cout << "Allocation failed: " << ex.what() << endl;
    }
    catch (runtime_error& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}

void Elections::load_representatives(istream& in) {
    // load reps to parties & district
    int num_reps; //number of representative per party
    int id, dnum, pnum;
    try {
        for (int i = 0; i < _parties.size(); ++i)
        {
            in.read(rcast(&num_reps), sizeof(num_reps));
            if (!in.good()) {
                throw runtime_error("ERROR! Couldn't read from file!");
            }
            for (int j = 0; j < num_reps; ++j)
            {
                in.read(rcast(&id), sizeof(int));
                in.read(rcast(&dnum), sizeof(int));
                in.read(rcast(&pnum), sizeof(int));
                if (!in.good()) {
                    throw runtime_error("ERROR! Couldn't read from file!");
                }
                add_representative(id, pnum, dnum);
            }
        }
    }
    catch (bad_alloc& ex) {
        std::cout << "Allocation failed: " << ex.what() << endl;
    }
    catch (runtime_error& ex) {
        throw;
    }
    catch (...) {
        throw;
    }
}