/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on a representative
*****************************************************/

#pragma once
#include "Citizen.h"

class Representative {
private:
    Citizen* _pcitizen; // pointer to citizen
    int _district_number;
public:
    Representative();
    Representative(Citizen* pcitizen, int district_number);
    Representative(const Representative& other);
    ~Representative();

    int get_id(void) const { return _pcitizen->get_id(); }
    Citizen* get_pcitizen(void) const { return _pcitizen; }
    int get_district_number(void) const { return _district_number; }

    bool set_pcitizen(Citizen* pcitizen);
    bool set_district_number(int district_number);

    Representative& operator=(const Representative& other);
    bool operator>(const Representative& other) const;
    bool operator<(const Representative& other) const;
    bool operator==(const Representative& other) const;

    friend ostream& operator<<(ostream& os, const Representative& representative) {
        os << *(representative._pcitizen);
        return os;
    }
};