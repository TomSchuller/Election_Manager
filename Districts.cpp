 /*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on districts.
*****************************************************/
#include "Districts.h"

Districts::Districts(int length) : _arr(length)
{
}


Districts::Districts(istream& in) : _arr()
{
    load(in);
}

Districts::~Districts() {
    for (int i = 0; i < _arr.size(); ++i)
    {
        delete _arr[i];
    }
}

int Districts::getLength(void) const {
    return _arr.size();
}

bool Districts::setLength(int newLen) {
     _arr.setLength(newLen);
     return true;
}


void Districts::add_district(const string name, int representatives_count, int type) {
    District* pdistrict = nullptr; 
    try {
        if (static_cast<DISTRICT_TYPE>(type) == DISTRICT_TYPE::UNIFIED) pdistrict = new District(name, _arr.size(), representatives_count); 
        else if (static_cast<DISTRICT_TYPE>(type) == DISTRICT_TYPE::DIVIDED) pdistrict = new Divided_District(name, _arr.size(), representatives_count);
        else throw invalid_argument("Error! You've entered an invalid type!  0 - Unified    1 - Divided"); 
        
        district_exists(*pdistrict); 
        _arr.push_back(pdistrict);
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

District* Districts::find_district_by_serial_number(int district_num) {
    // Go through array and find district
    for (int i = 0; i < _arr.size(); i++) {
        if (_arr[i]->get_serial_number() == district_num)
            return _arr[i];
    }
    throw invalid_argument("Error! District doesn't exist!");
}

void Districts::district_exists(const District& other) {
    // Go through array and find district. Throw exception if found.
    for (int i = 0; i < _arr.size(); i++) {
        if (*_arr[i] == other) throw  invalid_argument("Error! District has been added already!");
    }
}

void Districts::save(ostream& out) const
{
    int len = _arr.size();
    out.write(rcastc(&len), sizeof(len));
    for (int i = 0; i < len; i++) {
        if (!out.good()) {
            throw runtime_error("ERROR! Couldn't save to file!");
        }
        _arr[i]->save(out);
    }
}

void Districts::load(istream& in)
{
    int len;
    DISTRICT_TYPE type;
    in.read(rcast(&len), sizeof(len));
    if (!in.good()) {
        throw runtime_error("ERROR! Couldn't read from file!");
    }
    setLength(len);

    for (int i = 0; i < len; i++) {

        in.read(rcast(&type), sizeof(len));
        if (type == DISTRICT_TYPE::UNIFIED) {
            _arr[i] = new District();
        }
        else {
            _arr[i] = new Divided_District();
        }
        _arr[i]->load(in);

        if (!in.good()) {
            throw runtime_error("ERROR! Couldn't read from file!");
        }
    }
}