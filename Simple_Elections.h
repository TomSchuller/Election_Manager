/*************** FUNCTION DECLARATIONS ***************
 * This class contains the function declarations that make operations on a simple election round
*****************************************************/

#pragma once
#include "Elections.h"

class Simple_Elections : public Elections
{
public:
	Simple_Elections(int year, int month, int day, int representatives_count);
	Simple_Elections(const Simple_Elections& other) = delete;
	Simple_Elections(istream& in);

	~Simple_Elections();

	virtual ELECTION_TYPE get_type(void) const override { return ELECTION_TYPE::SIMPLE;  }

	virtual void add_citizen(const string name, int citizen_id, int year, int district_num) override { Elections::add_citizen(name, citizen_id, year, DISTRICT); }
	virtual void add_representative(int representative_id, int party_num, int district_num) override { return Elections::add_representative(representative_id, party_num, DISTRICT); }

	virtual District* find_district(int district_num) override { return _districts.find_district_by_serial_number(DISTRICT); }

	Simple_Elections& operator=(const Simple_Elections& other) = delete;

	virtual void save(ostream& out) const override;
	virtual void load(istream& in) override;
};