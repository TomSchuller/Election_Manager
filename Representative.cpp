/*************** FUNCTION DEFINITIONS ***************
 * This class contains the function definitions that make operations on a representative
*****************************************************/

#include "Representative.h"

Representative::Representative(Citizen* pcitizen, int district_number) : _pcitizen(pcitizen), _district_number(district_number)
{
}

Representative::Representative() : Representative(nullptr, UNDEFINED)
{
}


Representative::Representative(const Representative& other) : _pcitizen(other.get_pcitizen()), _district_number(other.get_district_number())
{
}

Representative::~Representative() {
}

bool Representative::set_pcitizen(Citizen* pcitizen) {
    _pcitizen = pcitizen;
    return true;
}
bool Representative::set_district_number(int district_number) {
    _district_number = district_number;
    return true;
}

Representative& Representative::operator=(const Representative& other) {
    if (this->_pcitizen != other.get_pcitizen()) {
        this->set_pcitizen(other.get_pcitizen());
        this->set_district_number(other.get_district_number());
    }
    return *this;
}

bool Representative::operator>(const Representative& other) const
{
    return (*this->get_pcitizen() > *other.get_pcitizen());
}

bool Representative::operator<(const Representative& other) const
{
    return (*this->get_pcitizen() < *other.get_pcitizen());
}

bool Representative::operator==(const Representative& other) const
{
    return (*this->get_pcitizen() == *other.get_pcitizen());
}