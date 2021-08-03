/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on a district.
*****************************************************/

#pragma once
#include "Party.h"

class District {
protected:
    string _name;
    int _serial_number;
    int _representatives_num;
    int _total_votes = 0;
    list <Citizen> _citizens;
public:
    District() noexcept;
    District(const string name, int serial_number, int representatives);
    District(const District& other) noexcept;
    virtual ~District() noexcept;

    // Getters
    const string get_name(void) const { return _name; }
    int get_serial_number(void) const noexcept { return _serial_number; }
    int get_representatives_number(void) const noexcept { return _representatives_num; }
    int get_total_votes(void) const noexcept { return _total_votes; }

    /****************************
    * get_percentage()
    * This function calculates the percentage of votes from all citizens allowed to vote in district.
    ****************************/
    float get_percentage(void) const;
    virtual DISTRICT_TYPE get_type(void) const { return DISTRICT_TYPE::UNIFIED; }
    const list <Citizen>& get_citizens(void) const { return _citizens; }

    // Setters
    bool set_name(const string name);
    bool set_serial_number(int serial_number) noexcept;
    bool set_representatives(int representatives) noexcept;
    bool set_total_votes(int total_votes) noexcept;
    /****************************
    * add_citizen()
    * This function adds a citizen to this district according to if this citizen can vote or not
    ****************************/
    Citizen* add_citizen(const Citizen& citizen);
    /****************************
    * get_party_votes()
    * This function calculates and returns a desired party total votes in this district
    ****************************/
    int get_party_votes(int party_number) const;
    /****************************
    * get_party_reps()
    * This function calculates and returns a desired party total representatives won in this district
    ****************************/
    int get_party_reps(int party_number) const;
    /****************************
    * get_party_percentage()
    * This function calculates and returns a desired party total votes percentage in this district
    ****************************/
    float get_party_percentage(int party_num) const;
    /****************************
    * find_by_id()
    * This function finds and returns a citizen by their ID number
    ****************************/
    Citizen* find_by_id(int id);

    // Operators
    District& operator=(const District& other);
    bool operator>(const District& other) const;
    bool operator<(const District& other) const;
    bool operator==(const District& other) const;


    friend ostream& operator<<(ostream& os, const District& district) {
        // If name is not empty then print it.
        if (district.get_name()[0] != '\0') os << "Name: " << district.get_name() << ", ";

        os << "District number: " << district.get_serial_number() << ", Number of representatives: " << district.get_representatives_number();
        if (district.get_type() == DISTRICT_TYPE::UNIFIED) {
            os << ", DISTRICT_TYPE: UNIFIED" << endl;
        }
        else {
            os << ", DISTRICT_TYPE: DIVIDED" << endl;
        }
        return os;
    }

    // File operations
    virtual void save(ostream& out) const;
    virtual void load(istream& in);

};